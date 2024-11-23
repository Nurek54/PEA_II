#include "BranchAndBoundDFSSymmetric.h"
#include "SaveToCSV.h"
#include "TSPUtilities.h"
#include <climits>
#include <chrono>
#include <iostream>

// Konstruktor klasy BranchAndBoundDFSSymmetric
BranchAndBoundDFSSymmetric::BranchAndBoundDFSSymmetric(const int** input_matrix, int num_cities_input)
        : num_cities(num_cities_input) {
    // Alokujemy dynamicznie macierz odległości
    matrix = new int*[num_cities];
    for (int i = 0; i < num_cities; ++i) {
        matrix[i] = new int[num_cities];
        for (int j = 0; j < num_cities; ++j) {
            matrix[i][j] = input_matrix[i][j];
        }
    }
    // Inicjalizujemy minEdge
    minEdge = new int[num_cities];
    preprocessMinEdges();
}

// Destruktor klasy BranchAndBoundDFSSymmetric
BranchAndBoundDFSSymmetric::~BranchAndBoundDFSSymmetric() {
    for (int i = 0; i < num_cities; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    delete[] minEdge;
}

// Funkcja preprocessMinEdges
void BranchAndBoundDFSSymmetric::preprocessMinEdges() {
    for (int i = 0; i < num_cities; ++i) {
        int min_value = INT_MAX;
        for (int j = 0; j < num_cities; ++j) {
            if (i != j && matrix[i][j] != -1 && matrix[i][j] < min_value) {
                min_value = matrix[i][j];
            }
        }
        minEdge[i] = (min_value != INT_MAX) ? min_value : 0;
    }
}

// Główna funkcja solve
BranchAndBoundDFSSymmetric::Result BranchAndBoundDFSSymmetric::solve() {
    // Zapisujemy czas rozpoczęcia algorytmu
    auto start_time = std::chrono::high_resolution_clock::now();

    Stack s;

    // Tworzymy węzeł początkowy
    int* root_path = new int[1];
    root_path[0] = 0;

    int root_bound = Utilities::calculateLowerBound(root_path, 1, matrix, minEdge, num_cities);
    s.push({root_path, 1, 0, root_bound});

    int min_cost = INT_MAX;
    int* best_path = nullptr;
    int best_path_length = 0;

    while (!s.empty()) {
        Stack::StackNode current = s.pop();

        if (current.bound >= min_cost) {
            delete[] current.path;
            continue;
        }

        if (current.path_length == num_cities) {
            // Obliczamy całkowity koszt ścieżki wraz z powrotem do miasta początkowego
            int total_cost = Utilities::calculate_cost(current.path, current.path_length, matrix, true);
            if (total_cost < min_cost) {
                min_cost = total_cost;
                delete[] best_path;
                best_path_length = current.path_length + 1;
                best_path = new int[best_path_length];
                for (int i = 0; i < current.path_length; ++i) {
                    best_path[i] = current.path[i];
                }
                best_path[best_path_length - 1] = 0; // Dodaj powrót do miasta początkowego
            }
            delete[] current.path;
            continue;
        }

        // Generowanie dzieci węzła
        for (int i = current.path[current.path_length - 1] + 1; i < num_cities; ++i) {
            if (!Utilities::isCityInPath(current.path, current.path_length, i)) {
                int* child_path = new int[current.path_length + 1];
                for (int j = 0; j < current.path_length; ++j) {
                    child_path[j] = current.path[j];
                }
                child_path[current.path_length] = i;

                int temp_cost = Utilities::calculate_cost(child_path, current.path_length + 1, matrix, false);
                int child_bound = Utilities::calculateLowerBound(child_path, current.path_length + 1, matrix, minEdge, num_cities);

                if (child_bound < min_cost) {
                    s.push({child_path, current.path_length + 1, temp_cost, child_bound});
                } else {
                    delete[] child_path;
                }
            }
        }

        delete[] current.path;
    }

    // Zapisujemy czas zakończenia algorytmu
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> seconds = end_time - start_time;
    std::chrono::duration<double, std::milli> milliseconds = end_time - start_time;
    std::chrono::duration<double, std::nano> nanoseconds = end_time - start_time;

    // Zapis do pliku
    SaveToCSV save("BranchAndBoundDFSSymmetricResults.csv");
    save.saveResults("DFS_SYM", seconds, milliseconds, nanoseconds, best_path, best_path_length, min_cost);

    return Result(best_path, best_path_length, min_cost);
}

