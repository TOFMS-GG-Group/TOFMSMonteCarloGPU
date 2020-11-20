#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <chrono>

#include "utils.h"

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#define MAX_SOURCE_SIZE (0x100000)

#define NUM_IONS 10000
#define FILE_NAME "/Users/tylerjaacks/Documents/Projects/Class Projects/TestData/ISUSummedData.csv"

void initializeOpenCL()
{
    cl_mem d_A;
}

std::vector<std::vector<float>> readSISCSVToVector(std::string fileName)
{
    std::ifstream file(fileName);

    std::string line, val;
    std::vector<std::vector<float>> array;

    while (std::getline (file, line)) {
        std::vector<float> v;
        std::stringstream s (line);
        while (getline (s, val, ','))
            v.push_back (std::atof(val.c_str()));
        array.push_back (v);
    }

    return array;
}

std::vector<float> calculateSIS(std::vector<std::vector<float>> data)
{
    std::vector<float> sisArray;

    for (int i = 1; i < data.size(); i++)
    {
        for (int j = 0; j < (int) data[i][1]; j++)
        {
            if (data[i][0] >= 0.0f)
            {
                sisArray.push_back(data[i][0]);
            }
        }
    }

    return sisArray;
}

float calculateSISValue(std::vector<float> data, int size)
{
    float sum = 0;

    for (int i = 0; i < size; i++)
    {
        sum += data[i];
    }

    return sum / size;
}

std::vector<float> calculateSISNorm(std::vector<float> sisArray, float sisValue)
{
    return vectorDivision(sisArray, sisValue);
}

std::vector<std::vector<int>> calculateMonteCarlo(std::vector<std::vector<int>> cmpdArray, std::vector<float> sisNormalized)
{
    auto newVector = std::vector<std::vector<int>>();
    auto count = 0;

    for (auto& it : cmpdArray)
    {
        auto tmpVector = std::vector<int>();

        for (int i = 0; i < it.size(); i++)
        {
            std::cout << "Monte Carlo Simulation: " << count << std::endl;

            auto poissonChoice = randomChoice(sisNormalized, it[i]);
            auto sum = vectorSum(poissonChoice);

            tmpVector.push_back(sum);
            count++;
        }

        newVector.push_back(tmpVector);
    }

    return newVector;
}

int main(int argc, char* args[])
{
    printf("Reading from SIS CSV file...\n");

    // TODO Load these from the command line arguments.
    int numIons = NUM_IONS;
    std::string fileName = FILE_NAME;

    std::vector<std::vector<float>> data = readSISCSVToVector(fileName);

    printf("Calculating SIS Array...\n");

    std::vector<float> sis = calculateSIS(data);

    printf("Calculating SIS Values...\n");

    float sisValue = calculateSISValue(sis, sis.size());

    printf("Calculating SIS Norm...\n");

    std::chrono::time_point<std::chrono::steady_clock> start1 = std::chrono::steady_clock::now();

    auto sisArrayNorm = calculateSISNorm(sis, sisValue);

    std::chrono::time_point<std::chrono::steady_clock> end1 = std::chrono::steady_clock::now();
    std::chrono::milliseconds diff1 = duration_cast<std::chrono::milliseconds>(end1 - start1);

    std::cout << "It took " << diff1.count() / 60000.0f << "s" << " to run the Monte Carlo simulation." << std::endl;

    auto sqRtCtRateArray = linspace(0.5, 5, 50);
    auto ctRateArray = vectorSquared(sqRtCtRateArray);

    // TODO I think this is wrong.
    std::vector<std::vector<int>> cmpdArray = poissonDistFromVector(ctRateArray, NUM_IONS);

    transpose(cmpdArray);

    std::chrono::time_point<std::chrono::steady_clock> start2 = std::chrono::steady_clock::now();

    std::vector<std::vector<int>> tmp = calculateMonteCarlo(cmpdArray, sisArrayNorm);

    std::chrono::time_point<std::chrono::steady_clock> end2 = std::chrono::steady_clock::now();
    std::chrono::milliseconds diff2 = duration_cast<std::chrono::milliseconds>(end2 - start2);

    std::cout << "It took " << diff2.count() / 60000.0f << "s" << " to run the Monte Carlo simulation." << std::endl;

    printf("Initializing OpenCL...\n");

    initializeOpenCL();
}