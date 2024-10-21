#ifndef TSPSIMULATION_H
#define TSPSIMULATION_H

#include <vector>
#include <string>
#include "TSPInstance.h"

using namespace std;

class TSPSimulation {
public:
    // Konstruktor
    TSPSimulation(int numMatrices, int matrixSize, int maxCost);

    // Funkcja do uruchamiania symulacji
    void runSimulation();

private:
    int numMatrices;
    int matrixSize;
    int maxCost;

    // Funkcja do generowania losowej macierzy
    vector<vector<int>> generateRandomMatrix();
};

#endif // TSPSIMULATION_H
