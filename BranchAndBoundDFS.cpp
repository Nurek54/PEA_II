#include "BranchAndBoundDFS.h"
#include "SaveToCSV.h"
#include "TSPUtilities.h"
#include <stack>
#include <chrono>
#include <climits>
#include <iostream>

BranchAndBoundDFS::BranchAndBoundDFS(const int** input_matrix, int num_cities) : num_cities(num_cities) {
    // Alokujemy dynamicznie macierz odległości
    matrix = new int*[num_cities];
    for (int i = 0; i < num_cities; ++i) {
        matrix[i] = new int[num_cities];
        for (int j = 0; j < num_cities; ++j) {
            matrix[i][j] = input_matrix[i][j];
        }
    }
}

BranchAndBoundDFS::~BranchAndBoundDFS() {
    for (int i = 0; i < num_cities; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
}

BranchAndBoundDFS::Result BranchAndBoundDFS::solve() {
    // Używamy stosu do przechowywania stanów
    struct StackNode {
        int* path;
        int path_length;
        int cost;
    };

    std::stack<StackNode> s;
    int* root_path = new int[1];
    root_path[0] = 0; // Startujemy z miasta 0
    int root_cost = 0;

    s.push({root_path, 1, root_cost}); // Dodajemy węzeł początkowy do stosu

    int min_cost = INT_MAX;           // Minimalny znaleziony koszt
    int* best_path = nullptr;         // Najlepsza znaleziona ścieżka
    int best_path_length = 0;

    auto start = std::chrono::high_resolution_clock::now(); // Czas rozpoczęcia algorytmu

    while (!s.empty()) {
        // Pobieramy węzeł ze stosu
        StackNode current = s.top();
        s.pop();
        int* current_path = current.path;
        int current_path_length = current.path_length;
        int current_cost = current.cost;

        // Sprawdzamy, czy odwiedziliśmy wszystkie miasta
        if (current_path_length == num_cities) {
            // Dodajemy powrót do miasta startowego
            int* complete_path = new int[current_path_length + 1];
            for (int i = 0; i < current_path_length; ++i) {
                complete_path[i] = current_path[i];
            }
            complete_path[current_path_length] = 0;

            // Obliczamy całkowity koszt ścieżki za pomocą Utilities::calculate_cost
            int total_cost = Utilities::calculate_cost(complete_path, current_path_length + 1, const_cast<const int**>(matrix), true);

            if (total_cost < min_cost) {
                min_cost = total_cost;
                delete[] best_path;
                best_path_length = current_path_length + 1;
                best_path = new int[best_path_length];
                for (int i = 0; i < best_path_length; ++i) {
                    best_path[i] = complete_path[i];
                }
            }
            delete[] complete_path;
            delete[] current_path;
            continue;
        }

        // W DFS dodajemy dzieci w odwrotnej kolejności
        for (int i = num_cities - 1; i >= 0; --i) {
            // Sprawdzamy, czy miasto i jest już w aktualnej ścieżce
            if (!Utilities::isCityInPath(current_path, current_path_length, i)) {
                int* child_path = new int[current_path_length + 1];
                for (int j = 0; j < current_path_length; ++j) {
                    child_path[j] = current_path[j];
                }
                child_path[current_path_length] = i;

                // Obliczamy koszt ścieżki za pomocą Utilities::calculate_cost bez dodawania kosztu powrotu
                int temp_path_length = current_path_length + 1;
                int temp_cost = Utilities::calculate_cost(child_path, temp_path_length, const_cast<const int**>(matrix), false);

                // Przycinanie gałęzi jeśli koszt jest mniejszy niż aktualny min_cost
                if (temp_cost < min_cost) {
                    s.push({child_path, temp_path_length, temp_cost});
                } else {
                    delete[] child_path;
                }
            }
        }
        delete[] current_path;
    }

    auto end = std::chrono::high_resolution_clock::now(); // Czas zakończenia algorytmu
    std::chrono::duration<double> seconds = end - start;
    std::chrono::duration<double, std::milli> milliseconds = end - start;
    std::chrono::duration<double, std::nano> nanoseconds = end - start;

    // Zapisujemy wyniki do pliku CSV
    SaveToCSV save("BranchAndBoundDFSResults.csv");
    save.saveResults("BranchAndBoundDFS", seconds, milliseconds, nanoseconds, best_path, best_path_length, min_cost);

    // Zwracamy najlepszą ścieżkę i jej koszt
    Result result;
    result.path = best_path;
    result.path_length = best_path_length;
    result.cost = min_cost;

    return result;
}
