#include "TSPSimulation.h"
#include "TSPInstance.h"
#include "BranchAndBoundBFS.h"
#include "BranchAndBoundDFS.h"
#include "BranchAndBoundBestFirst.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

TSPSimulation::TSPSimulation(int numMatrices, int matrixSize, int maxCost, char** algorithms, int algorithmCount)
        : numMatrices(numMatrices), matrixSize(matrixSize), maxCost(maxCost), algorithms(algorithms), algorithmCount(algorithmCount) {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Inicjalizacja generatora liczb pseudolosowych
}

TSPSimulation::~TSPSimulation() {
    // Zakładam, że pamięć dla algorithms jest zarządzana poza klasą
}

void TSPSimulation::runSimulation() {
    for (int m = 0; m < numMatrices; ++m) {
        // Generujemy losową macierz odległości
        int** matrix = new int*[matrixSize];
        for (int i = 0; i < matrixSize; ++i) {
            matrix[i] = new int[matrixSize];
        }
        generateRandomMatrix(matrix);

        // Tworzymy instancję problemu
        TSPInstance instance(matrix, matrixSize);
        const int* const* distances = instance.getDistances();

        // Iterujemy po wybranych algorytmach
        for (int i = 0; i < algorithmCount; ++i) {
            std::string algorithm(algorithms[i]);

            if (algorithm == "BFS") {
                BranchAndBoundBFS solver(distances, matrixSize);
                auto result = solver.solve();
                // Wynik zapisany do CSV, nie drukujemy
            } else if (algorithm == "DFS") {
                BranchAndBoundDFS solver(distances, matrixSize);
                auto result = solver.solve();
                // Wynik zapisany do CSV, nie drukujemy
            } else if (algorithm == "BEST_FIRST") {
                BranchAndBoundBestFirst solver(distances, matrixSize);
                auto result = solver.solve(instance);
                // Wynik zapisany do CSV, nie drukujemy
            } else {
                // Nieznany algorytm, możemy pominąć lub logować
            }
        }

        // Zwalniamy pamięć
        for (int i = 0; i < matrixSize; ++i) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
}

void TSPSimulation::generateRandomMatrix(int** matrix) {
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            if (i == j) {
                matrix[i][j] = -1; // Brak połączenia do samego siebie
            } else {
                matrix[i][j] = std::rand() % maxCost + 1; // Losowa wartość od 1 do maxCost
            }
        }
    }
}
