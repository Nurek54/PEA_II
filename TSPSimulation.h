#ifndef TSPSIMULATION_H
#define TSPSIMULATION_H

#include <vector>
#include <string>

class TSPSimulation {
public:
    TSPSimulation(int numMatrices, int matrixSize, int maxCost, const std::vector<std::string>& algorithms);
    void runSimulation();

private:
    int numMatrices;
    int matrixSize;
    int maxCost;
    std::vector<std::string> algorithms;

    void generateRandomMatrix(int** matrix);
};

#endif // TSPSIMULATION_H
