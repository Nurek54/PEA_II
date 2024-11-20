#include "TSPSimulation.h"
#include "TSPInstance.h"
#include "BranchAndBoundBFS.h"
#include "BranchAndBoundDFS.h"
#include "BranchAndBoundBestFirst.h"
#include <cstdlib>
#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>

void mixRand() {
    for (int i = 0; i < 10; ++i) {
        rand();
    }
}

TSPSimulation::TSPSimulation(int numMatrices, int matrixSize, int maxCost)
        : numMatrices(numMatrices), matrixSize(matrixSize), maxCost(maxCost) {}

int** TSPSimulation::generateRandomMatrix() {
    int** matrix = new int*[matrixSize];
    for (int i = 0; i < matrixSize; ++i) {
        matrix[i] = new int[matrixSize];
    }

    auto now = std::chrono::high_resolution_clock::now();
    auto duration = now.time_since_epoch();
    unsigned long long nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();

    srand(static_cast<unsigned int>(nanoseconds + rand()));

    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            if (i == j) {
                matrix[i][j] = -1;
            } else {
                matrix[i][j] = rand() % maxCost + 1;
            }
        }
    }

    mixRand();

    return matrix;
}

void TSPSimulation::runSimulation() {
    std::cout << "Postęp symulacji: ";
    for (int i = 0; i < numMatrices; ++i) {
        int** matrix = generateRandomMatrix();
        TSPInstance instance(matrix, matrixSize);
        const int* const* distances = instance.getDistances();
        int numCities = instance.getCityCount();

        // Konwersja const int* const* na const int** (usunięcie const z pośrednich wskaźników)
        auto mutableDistances = const_cast<const int**>(distances);

        // Uruchamianie wszystkich trzech algorytmów dla wygenerowanej macierzy
        BranchAndBoundBFS bfsSolver(mutableDistances, numCities);
        auto bfsResult = bfsSolver.solve();
        std::cout << "BFS - Koszt: " << bfsResult.cost << "\n";

        BranchAndBoundDFS dfsSolver(mutableDistances, numCities);
        auto dfsResult = dfsSolver.solve();
        std::cout << "DFS - Koszt: " << dfsResult.cost << "\n";

        BranchAndBoundBestFirst bestFirstSolver(mutableDistances, numCities);
        auto bestFirstResult = bestFirstSolver.solve(instance);
        std::cout << "Best First - Koszt: " << bestFirstResult.cost << "\n";

        // Obliczanie procentu ukończenia symulacji
        int progress = (i + 1) * 100 / numMatrices;

        // Przesunięcie kursora i nadpisywanie tylko wartości procentowej
        std::cout << "\rPostęp symulacji: " << progress << "%" << std::flush;

        // Krótkie opóźnienie między kolejnymi iteracjami symulacji
        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        // Zwalniamy pamięć macierzy
        for (int j = 0; j < matrixSize; ++j) {
            delete[] matrix[j];
        }
        delete[] matrix;
    }

    std::cout << "\nSymulacja zakończona.\n";
}
