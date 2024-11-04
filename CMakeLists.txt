cmake_minimum_required(VERSION 3.27)
project(PEA_I)

set(CMAKE_CXX_STANDARD 17)

add_executable(PEA_I main.cpp
        TSPInstance.cpp
        TSPInstance.h
        SaveToCSV.cpp
        SaveToCSV.h
        TSPUtilities.cpp
        TSPUtilities.h
        TSPSimulation.cpp
        TSPSimulation.h
        BranchAndBoundBFS.cpp
        BranchAndBoundBFS.h
        BranchAndBoundBFS.h
        BranchAndBoundDFS.cpp
        BranchAndBoundDFS.h
        BranchAndBoundBestFirst.cpp
        BranchAndBoundBestFirst.h
        ConfigReader.cpp
        ConfigReader.h)