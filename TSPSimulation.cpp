#include "TSPSimulation.h"
#include "BruteForceTSP.h"
#include "NearestNeighborTSP.h"
#include "RandomTSP.h"
#include <iostream>
#include <cstdlib>  // Do funkcji rand() i srand()
#include <ctime>    // Do inicjalizacji ziarna rand()

// Konstruktor klasy TSPSimulation
TSPSimulation::TSPSimulation(int numMatrices, int matrixSize, int maxCost)
        : numMatrices(numMatrices), matrixSize(matrixSize), maxCost(maxCost) {
    srand(time(nullptr));  // Inicjalizacja ziarna dla rand()
}

// Funkcja do generowania losowej macierzy z użyciem rand()
std::vector<std::vector<int>> TSPSimulation::generateRandomMatrix() {
    std::vector<std::vector<int>> matrix(matrixSize, std::vector<int>(matrixSize));

    // Wypełnianie macierzy losowymi wartościami
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            if (i != j) {
                matrix[i][j] = rand() % maxCost + 1;  // Losowanie wartości z przedziału [1, maxCost]
            } else {
                matrix[i][j] = 0;  // Koszt do samego siebie wynosi 0
            }
        }
    }

    return matrix;
}

// Funkcja uruchamiajaca symulacje
void TSPSimulation::runSimulation() {
    for (int i = 0; i < numMatrices; ++i) {
        std::cout << "Symulacja nr " << (i + 1) << " z " << numMatrices << std::endl;

        // Generowanie nowej losowej macierzy
        std::vector<std::vector<int>> matrix = generateRandomMatrix();

        // Tworzenie instancji TSP na podstawie wygenerowanej macierzy
        TSPInstance instance(matrix);

        // Uruchom algorytmy na tej samej macierzy
        std::cout << "Brute Force:\n";
        tsp_bruteforce(instance);

        std::cout << "Nearest Neighbor:\n";
        tsp_nearest_neighbor(instance);

        std::cout << "Random Algorithm:\n";
        tsp_random(instance);

        std::cout << "---------------------------------\n";
    }
    std::cout << "\nSymulacja zakonczona. Przetestowano " << numMatrices << " macierzy dla kazdego algorytmu.\n";
}
