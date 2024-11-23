#ifndef TSPSIMULATION_H
#define TSPSIMULATION_H

#include <string>

class TSPSimulation {
public:
    TSPSimulation(int numMatrices, int matrixSize, int maxCost, char** algorithms, int algorithmCount, const std::string& matrixType);
    ~TSPSimulation();
    void runSimulation();

private:
    int numMatrices;         // Liczba macierzy do wygenerowania
    int matrixSize;          // Rozmiar macierzy
    int maxCost;             // Maksymalny koszt w macierzy
    char** algorithms;       // Lista algorytmów
    int algorithmCount;      // Liczba algorytmów
    std::string matrixType;  // Typ generowanej macierzy (random/symmetric)

    void generateRandomMatrix(int** matrix);  // Generowanie losowej macierzy
    void generateSymmetricMatrix(int** matrix); // Generowanie symetrycznej macierzy
};

#endif // TSPSIMULATION_H
