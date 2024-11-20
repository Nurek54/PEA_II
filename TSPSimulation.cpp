#include "TSPSimulation.h"
#include "TSPInstance.h"
#include "BranchAndBoundBFS.h"
#include "BranchAndBoundDFS.h"
#include "BranchAndBoundBestFirst.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

TSPSimulation::TSPSimulation(int numMatrices, int matrixSize, int maxCost, const std::vector<std::string>& algorithms)
        : numMatrices(numMatrices), matrixSize(matrixSize), maxCost(maxCost), algorithms(algorithms) {
    std::srand(static_cast<unsigned int>(std::time(nullptr))); // Inicjalizacja generatora liczb pseudolosowych
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

        // Konwersja const int* const* na const int** (usunięcie const z pośrednich wskaźników)
        auto mutableDistances = const_cast<const int**>(distances);

        // Iterujemy po wybranych algorytmach
        for (const auto& algorithm : algorithms) {
            std::cout << "Symulacja " << m + 1 << "/" << numMatrices << ", Algorytm: " << algorithm << std::endl;

            if (algorithm == "BFS") {
                BranchAndBoundBFS solver(mutableDistances, matrixSize);
                auto result = solver.solve();
                // Możesz zapisać wyniki lub wyświetlić je tutaj
            } else if (algorithm == "DFS") {
                BranchAndBoundDFS solver(mutableDistances, matrixSize);
                auto result = solver.solve();
                // Możesz zapisać wyniki lub wyświetlić je tutaj
            } else if (algorithm == "BEST_FIRST") {
                BranchAndBoundBestFirst solver(mutableDistances, matrixSize);
                auto result = solver.solve(instance);
                // Możesz zapisać wyniki lub wyświetlić je tutaj
            } else {
                std::cout << "Nieznany algorytm: " << algorithm << std::endl;
                // Możesz zdecydować, czy kontynuować, czy przerwać w tym miejscu
            }

            std::cout << "----------------------------------------" << std::endl;
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
