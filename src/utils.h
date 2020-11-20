//
// Created by Tyler Jaacks on 10/29/20.
//

#ifndef TOFMSSMONTECARLOGPU_UTILS_H
#define TOFMSSMONTECARLOGPU_UTILS_H

#include <vector>
#include <iostream>
#include <chrono>
#include <random>

float** multiDimensionalVectorToArray(std::vector<std::vector<float>> &vals, int N, int M);
float* vectorToArray(std::vector<float> &vals, int N);
std::vector<float> vectorDivision(std::vector<float> vector, float divsor);
std::vector<float> linspace(float start_in, float end_in, float num_in);
std::vector<float> vectorSquared(std::vector<float> vector);
std::vector<std::vector<int>> poissonDistFromVector(std::vector<float> ctRateArray, int numIons);
void transpose(std::vector<std::vector<int>> &b);
float randomChoice(std::vector<float> vector);
float randomChoice(int param1);
std::vector<float> randomChoice(std::vector<float> vector, int size);
std::vector<float> randomChoice(int param1, int size);
float vectorSum(std::vector<float> data);
float vectorMean(std::vector<float> vector);

#endif //TOFMSSMONTECARLOGPU_UTILS_H