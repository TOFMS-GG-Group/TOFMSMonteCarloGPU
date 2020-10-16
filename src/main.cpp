#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif

#define MAX_SOURCE_SIZE (0x100000)

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

float** multiDimensionalVectorToArray(std::vector<std::vector<float>> &vals, int N, int M)
{
    float** temp;

    temp = new float*[N];

    for(unsigned i=0; (i < N); i++)
    {
        temp[i] = new float[M];

        for(unsigned j=0; (j < M); j++)
        {
            temp[i][j] = vals[i][j];
        }
    }

    return temp;
}

float* vectorToArray(std::vector<float> &vals, int N) {
    float* temp;

    temp = new float[N];

    for (unsigned i = 0; i < N; i++)
    {
        temp[i] = vals[i];
    }

    return temp;
}

float findAverageArray(float array[], int size)
{
    // avg = a.mean(axis)
    // scl = avg.dtype.type(a.size/avg.size)

    float sum;

    for (int i = 0; i < size; i++)
    {
        sum += array[i];
    }

    return sum / size;
}

float* calculateSIS(float** data, int size)
{
    std::vector<float> sisArray;

    for (int i = 1; i < size; i++)
    {
        for (int j = 0; j < (int) data[i][1]; j++)
        {
            if (data[i][0] >= 0.0f)
            {
                sisArray.push_back(data[i][0]);
            }
        }
    }

    return vectorToArray(sisArray, sisArray.size());
}

// TODO findAverageArray not working.
float calculateSISValue(float* data, int size)
{
//    SIS_Value = np.average(SIS_Array)


    return findAverageArray(data, size);
}

void calculateSISNorm()
{
//    SIS_Array_Norm = np.true_divide(SIS_Array, SIS_Value)
}

// TODO This code should run with OpenCL in the future.
void calculateMonteCarlo(float countRate[])
{

}

int main(int argc, char* args[])
{
    printf("Reading from SIS CSV file...\n");

    // TODO Load this from the command line arguments.
    std::string fileName = "/Users/tylerjaacks/Desktop/TestData/ISUSummedData.csv";

    // TODO Make this is one operation i.e .CSV -> float** or float[][].
    std::vector<std::vector<float>> data = readSISCSVToVector(fileName);
    int size = data.size();
    float** dataArray = multiDimensionalVectorToArray(data, data.size(), 2);

    printf("Done Reading from SIS.\n");

    printf("Calculating SIS Values...\n");

    float* sis = calculateSIS(dataArray, size);

    for (int i = 0; i < size; i++)
    {
        printf("&f", sis[i]);
    }

    float sisValue = calculateSISValue(sis, size);

    printf("sisValue: %f", sisValue);
}