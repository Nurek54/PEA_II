#include "BranchAndBoundBFS.h"
#include "SaveToCSV.h"
#include "TSPUtilities.h"
#include <chrono>
#include <climits>
#include <iostream>

// Konstruktor klasy BranchAndBoundBFS
BranchAndBoundBFS::BranchAndBoundBFS(const int* const* input_matrix, int num_cities_input)
        : num_cities(num_cities_input) {
    // Alokacja macierzy kosztów
    matrix = new int*[num_cities];
    for (int i = 0; i < num_cities; ++i) {
        matrix[i] = new int[num_cities];
        for (int j = 0; j < num_cities; ++j) {
            matrix[i][j] = input_matrix[i][j];
        }
    }

    // Inicjalizacja tablicy minimalnych krawędzi
    minEdge = new int[num_cities];
    preprocessMinEdges();
}

// Destruktor klasy BranchAndBoundBFS
BranchAndBoundBFS::~BranchAndBoundBFS() {
    for (int i = 0; i < num_cities; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    delete[] minEdge;
}

// Funkcja preprocessMinEdges - oblicza minimalne krawędzie dla każdego miasta
void BranchAndBoundBFS::preprocessMinEdges() {
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

// Funkcja solve - główna implementacja algorytmu BFS
BranchAndBoundBFS::Result BranchAndBoundBFS::solve(const std::string& matrixType) {
    // Inicjalizacja własnej kolejki
    Queue q;

    // Tworzenie węzła początkowego
    int* root_path = new int[1];
    root_path[0] = 0; // Startujemy z miasta 0

    // Obliczanie dolnej granicy dla węzła początkowego
    int root_bound = Utilities::calculateLowerBound(root_path, 1, matrix, minEdge, num_cities);

    // Dodanie węzła początkowego do kolejki
    q.enqueue({root_path, 1, 0, root_bound});

    // Inicjalizacja zmiennych do przechowywania najlepszej ścieżki
    int min_cost = INT_MAX;
    int* best_path = nullptr;
    int best_path_length = 0;

    // Zapisujemy czas rozpoczęcia algorytmu
    auto start_time = std::chrono::high_resolution_clock::now();

    // Główna pętla algorytmu BFS
    while (!q.empty()) {
        // Pobieramy węzeł z kolejki
        Queue::QueueNode current = q.dequeue();

        // Obsługa pustego węzła (jeśli kolejka była pusta)
        if (current.path == nullptr && current.path_length == 0 && current.cost == 0 && current.bound == 0) {
            continue;
        }

        int* current_path = current.path;
        int current_path_length = current.path_length;
        int current_cost = current.cost;
        int current_bound = current.bound;

        // Przycinanie gałęzi
        if (current_bound >= min_cost) {
            delete[] current_path;
            continue;
        }

        // Sprawdzamy, czy odwiedziliśmy wszystkie miasta
        if (current_path_length == num_cities) {
            // Dodajemy powrót do miasta startowego, aby zamknąć cykl
            int* complete_path = new int[current_path_length + 1];
            for (int i = 0; i < current_path_length; ++i) {
                complete_path[i] = current_path[i];
            }
            complete_path[current_path_length] = current_path[0];

            // Obliczamy całkowity koszt ścieżki
            int total_cost = Utilities::calculate_cost(complete_path, current_path_length + 1, matrix, true);

            if (total_cost < min_cost) {
                min_cost = total_cost;
                delete[] best_path;
                best_path_length = current_path_length + 1;
                best_path = complete_path;
            } else {
                delete[] complete_path;
            }

            delete[] current_path;
            continue;
        }

        // Generowanie dzieci węzła
        for (int i = 0; i < num_cities; ++i) {
            // Sprawdzamy, czy miasto i jest już w ścieżce i czy istnieje połączenie
            if (!Utilities::isCityInPath(current_path, current_path_length, i) &&
                matrix[current_path[current_path_length - 1]][i] != -1) {

                // Tworzymy nową ścieżkę dla dziecka
                int* child_path = new int[current_path_length + 1];
                for (int j = 0; j < current_path_length; ++j) {
                    child_path[j] = current_path[j];
                }
                child_path[current_path_length] = i;

                // Obliczamy nowy koszt ścieżki
                int temp_cost = current_cost + matrix[current_path[current_path_length - 1]][i];

                // Obliczamy nową dolną granicę dla dziecka
                int child_bound = Utilities::calculateLowerBound(child_path, current_path_length + 1, matrix, minEdge, num_cities);

                // Przycinamy gałęzie, jeśli dolna granica jest mniejsza niż obecny minimalny koszt
                if (child_bound < min_cost) {
                    q.enqueue({child_path, current_path_length + 1, temp_cost, child_bound});
                } else {
                    delete[] child_path;
                }
            }
        }

        // Usuwamy bieżącą ścieżkę, aby uniknąć wycieków pamięci
        delete[] current_path;
    }

    // Zapisujemy czas zakończenia algorytmu
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> seconds = end_time - start_time;
    std::chrono::duration<double, std::milli> milliseconds = end_time - start_time;
    std::chrono::duration<double, std::nano> nanoseconds = end_time - start_time;

    // Dodajemy koszt powrotu do miasta początkowego dla najlepszej ścieżki (jeśli istnieje)
    if (best_path != nullptr) {
        // Sprawdzamy, czy ostatnie miasto nie jest już miastem początkowym
        if (best_path_length > 0 && best_path[best_path_length - 1] != best_path[0]) {
            int* complete_path = new int[best_path_length + 1];
            for (int i = 0; i < best_path_length; ++i) {
                complete_path[i] = best_path[i];
            }
            complete_path[best_path_length] = best_path[0];
            delete[] best_path;
            best_path = complete_path;
            best_path_length += 1;
        }

        // Aktualizacja minimalnego kosztu z powrotem do miasta startowego
        int final_cost = Utilities::calculate_cost(best_path, best_path_length, matrix, true);
        min_cost = final_cost;
    }

    // Zapisujemy wyniki do pliku CSV
    SaveToCSV save("BranchAndBoundBFSResults.csv");
    save.saveResults("BranchAndBoundBFS", matrixType, seconds, milliseconds, nanoseconds, best_path, best_path_length, min_cost);

    // Przygotowujemy wynik do zwrócenia
    Result result;
    result.path = best_path;
    result.path_length = best_path_length;
    result.cost = min_cost;

    return result;
}
