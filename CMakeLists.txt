cmake_minimum_required(VERSION 3.16)
project(TOFMSSMonteCarloGPU)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXE_LINKER_FLAGS -opencl)

add_executable(TOFMSSMonteCarloGPU
        src/main.cpp src/monte_carlo_simulation.cl src/utils.cpp src/utils.h src/GaussJordanMatrixInversion.cl)
