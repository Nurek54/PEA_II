#ifndef TSPSIMULATION_H
#define TSPSIMULATION_H

class TSPSimulation {
public:
    TSPSimulation(int numMatrices, int matrixSize, int maxCost);
    void runSimulation();

private:
    int numMatrices;
    int matrixSize;
    int maxCost;

    int** generateRandomMatrix();
};

#endif // TSPSIMULATION_H
