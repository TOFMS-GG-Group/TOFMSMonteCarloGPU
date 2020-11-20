//
// Created by Tyler Jaacks on 10/29/20.
//

#include "utils.h"

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

float* vectorToArray(std::vector<float> &vals, int N)
{
    float* temp;

    temp = new float[N];

    for (unsigned i = 0; i < N; i++)
    {
        temp[i] = vals[i];
    }

    return temp;
}

std::vector<float> vectorDivision(std::vector<float> vector, float divsor)
{
    std::vector<float> new_vector;

    for (int i = 0; i < vector.size(); i++)
    {
        new_vector.push_back(vector[i] / divsor);
    }

    return new_vector;
}

std::vector<float> linspace(float start_in, float end_in, float num_in)
{

    std::vector<float> linspaced;

    double start = static_cast<float>(start_in);
    double end = static_cast<float>(end_in);
    double num = static_cast<float>(num_in);

    if (num == 0) { return linspaced; }
    if (num == 1)
    {
        linspaced.push_back(start);
        return linspaced;
    }

    float delta = (end - start) / (num - 1);

    for(int i=0; i < num-1; ++i)
    {
        linspaced.push_back(start + delta * i);
    }
    linspaced.push_back(end);

    return linspaced;
}

std::vector<float> vectorSquared(std::vector<float> vector)
{
    std::vector<float> squaredVector;

    for (int i = 0; i < vector.size(); i++)
    {
        squaredVector.push_back(vector[i] * vector[i]);
    }

    return squaredVector;
}

std::vector<std::vector<int>> poissonDistFromVector(std::vector<float> ctRateArray, int numIons)
{
    std::mt19937 mrand(std::time(0));

    std::vector<std::vector<int>> finalResult;

    for (int i = 0; i < numIons; i++)
    {
        std::vector<int> results;

        for (int j = 0; j < ctRateArray.size(); j++)
        {
            std::poisson_distribution<int> distribution(ctRateArray[j]);
            results.push_back(distribution(mrand));
        }

        finalResult.push_back(results);
    }

    return finalResult;
}

void transpose(std::vector<std::vector<int>> &b)
{
    if (b.size() == 0)
        return;

    std::vector<std::vector<int> > trans_vec(b[0].size(), std::vector<int>());

    for (int i = 0; i < b.size(); i++)
    {
        for (int j = 0; j < b[i].size(); j++)
        {
            trans_vec[j].push_back(b[i][j]);
        }
    }

    b = trans_vec;
}

float randomChoice(std::vector<float> vector)
{
    int randomNumber = rand() % vector.size();

    return vector[randomNumber];
}

float randomChoice(int param1)
{
    return rand() % param1;
}

std::vector<float> randomChoice(std::vector<float> vector, int size)
{
    std::vector<float> result;

    for (int i = 0; i < size; i++)
    {
        result.push_back(randomChoice(vector));
    }

    return result;
}

float vectorSum(std::vector<float> data)
{
    float sum = 0;

    for (float f : data)
    {
        sum += f;
    }

    return sum;
}

std::vector<float> randomChoice(int param1, int size)
{
    std::vector<float> result;

    for (int i = 0; i < size; i++)
    {
        result.push_back(randomChoice(param1));
    }

    return result;
}

float vectorMean(std::vector<float> vector)
{
    return vectorSum(vector) / vector.size();
}