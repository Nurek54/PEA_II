#ifndef TSPSIMULATION_H
#define TSPSIMULATION_H

#include <string>

class TSPSimulation {
public:
    TSPSimulation(int numMatrices, int matrixSize, int maxCost, char** algorithms, int algorithmCount);
    ~TSPSimulation();
    void runSimulation();

private:
    int numMatrices;
    int matrixSize;
    int maxCost;
    char** algorithms;
    int algorithmCount;

    void generateRandomMatrix(int** matrix);
};

#endif // TSPSIMULATION_H
