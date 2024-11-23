#include "TSPSimulation.h"
#include "TSPInstance.h"
#include "BranchAndBoundBFS.h"
#include "BranchAndBoundDFS.h"
#include "BranchAndBoundBestFirst.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

TSPSimulation::TSPSimulation(int numMatrices, int matrixSize, int maxCost, char** algorithms, int algorithmCount, const std::string& matrixType)
        : numMatrices(numMatrices), matrixSize(matrixSize), maxCost(maxCost), algorithms(algorithms), algorithmCount(algorithmCount), matrixType(matrixType) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

TSPSimulation::~TSPSimulation() {
}

void TSPSimulation::runSimulation() {
    for (int m = 0; m < numMatrices; ++m) {
        // Tworzymy macierz odległości
        int** matrix = new int*[matrixSize];
        for (int i = 0; i < matrixSize; ++i) {
            matrix[i] = new int[matrixSize];
        }

        // Wybieramy metodę generowania macierzy
        if (matrixType == "symmetric") {
            generateSymmetricMatrix(matrix);
        } else {
            generateRandomMatrix(matrix);
        }

        // Tworzymy instancję problemu
        TSPInstance instance(matrix, matrixSize);
        const int* const* distances = instance.getDistances();

        // Iterujemy po wybranych algorytmach
        for (int i = 0; i < algorithmCount; ++i) {
            std::string algorithm(algorithms[i]);

            if (algorithm == "BFS") {
                BranchAndBoundBFS solver(distances, matrixSize);
                auto result = solver.solve(matrixType);
                // Wynik zapisany do CSV, nie drukujemy
            } else if (algorithm == "DFS") {
                BranchAndBoundDFS solver(distances, matrixSize);
                auto result = solver.solve(matrixType);
                // Wynik zapisany do CSV, nie drukujemy
            } else if (algorithm == "BEST_FIRST") {
                BranchAndBoundBestFirst solver(distances, matrixSize);
                auto result = solver.solve(instance, matrixType);
                // Wynik zapisany do CSV, nie drukujemy
            } else {
                std::cout << "Nieznany algorytm: " << algorithm << std::endl;
                // Możemy pominąć lub logować
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

void TSPSimulation::generateSymmetricMatrix(int** matrix) {
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = i; j < matrixSize; ++j) {
            if (i == j) {
                matrix[i][j] = -1; // Brak połączenia do samego siebie
            } else {
                int cost = std::rand() % maxCost + 1; // Losowa wartość od 1 do maxCost
                matrix[i][j] = cost;
                matrix[j][i] = cost; // Symetryczność
            }
        }
    }
}
