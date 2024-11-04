#ifndef TSPSIMULATION_H
#define TSPSIMULATION_H

#include <vector>

using namespace std;

class TSPSimulation {
public:
    TSPSimulation(int numMatrices, int matrixSize, int maxCost);
    void runSimulation();

private:
    int numMatrices;
    int matrixSize;
    int maxCost;

    vector<vector<int>> generateRandomMatrix();
};

#endif
