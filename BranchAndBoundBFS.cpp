#include "BranchAndBoundBFS.h"
#include "SaveToCSV.h"
#include "TSPUtilities.h"
#include <vector>
#include <climits>
#include <chrono>

std::pair<std::vector<int>, int> BranchAndBoundBFS::solve(const TSPInstance& instance) {
    // Pobieramy macierz odległości i liczbę miast
    std::vector<std::vector<int>> distances = instance.getDistances();
    int num_cities = instance.getCityCount();

    // Używamy wektora jako kolejki
    std::vector<Node> queue;
    Node root;
    root.path.push_back(0); // Startujemy z miasta 0
    root.cost = 0;
    root.level = 0;

    queue.push_back(root); // Dodajemy węzeł początkowy do kolejki

    int min_cost = INT_MAX;           // Minimalny znaleziony koszt
    std::vector<int> best_path;       // Najlepsza znaleziona ścieżka

    auto start = std::chrono::high_resolution_clock::now(); // Czas rozpoczęcia algorytmu

    while (!queue.empty()) {
        // Pobieramy pierwszy węzeł z kolejki
        Node current = queue.front();
        queue.erase(queue.begin()); // Usuwamy węzeł z kolejki

        // Przycinamy gałęzie, jeśli aktualny koszt jest większy lub równy minimalnemu kosztowi
        if (current.cost >= min_cost) {
            continue;
        }

        // Jeśli odwiedziliśmy wszystkie miasta
        if (current.level == num_cities - 1) {
            // Dodajemy powrót do miasta startowego
            int return_cost = distances[current.path.back()][0];
            if (return_cost != -1) {
                int total_cost = current.cost + return_cost;
                if (total_cost < min_cost) {
                    min_cost = total_cost;
                    best_path = current.path;
                    best_path.push_back(0); // Dodajemy miasto startowe na koniec ścieżki
                }
            }
            continue;
        }

        // Generujemy dzieci (następne możliwe miasta do odwiedzenia)
        for (int i = 0; i < num_cities; ++i) {
            // Używamy funkcji Utilities::isCityInPath zamiast pętli
            if (!Utilities::isCityInPath(current.path, i)) {
                int edge_cost = distances[current.path.back()][i];
                if (edge_cost != -1) {
                    // Tworzymy nowy węzeł potomny
                    Node child;
                    child.path = current.path;
                    child.path.push_back(i);
                    child.level = current.level + 1;
                    child.cost = current.cost + edge_cost;

                    // Dodajemy węzeł do kolejki, jeśli jego koszt jest mniejszy niż min_cost
                    if (child.cost < min_cost) {
                        queue.push_back(child);
                    }
                }
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now(); // Czas zakończenia algorytmu
    std::chrono::duration<double> seconds = end - start;
    std::chrono::duration<double, std::milli> milliseconds = end - start;
    std::chrono::duration<double, std::nano> nanoseconds = end - start;

    // Zapisujemy wyniki do pliku CSV
    SaveToCSV save("BranchAndBoundBFSResults.csv");
    save.saveResults("BranchAndBoundBFS", seconds, milliseconds, nanoseconds, best_path, min_cost);

    // Zwracamy najlepszą ścieżkę i jej koszt
    return std::make_pair(best_path, min_cost);
}
