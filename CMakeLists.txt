cmake_minimum_required(VERSION 3.27)
project(PEA_I)

set(CMAKE_CXX_STANDARD 17)

add_executable(PEA_I main.cpp
        TSPInstance.cpp
        TSPInstance.h
        BruteForceTSP.cpp
        BruteForceTSP.h
        NearestNeighborTSP.cpp
        NearestNeighborTSP.h
        RandomTSP.cpp
        RandomTSP.h
        SaveToCSV.cpp
        SaveToCSV.h
        TSPUtilities.cpp
        TSPUtilities.h
        TSPSimulation.cpp
        TSPSimulation.h)
