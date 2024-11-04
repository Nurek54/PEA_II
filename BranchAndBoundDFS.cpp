#include "BranchAndBoundDFS.h"
#include "SaveToCSV.h"
#include "TSPUtilities.h"
#include <stack>
#include <chrono>
#include <limits>
#include <vector>
#include <utility>

std::pair<std::vector<int>, int> BranchAndBoundDFS::solve(const TSPInstance& instance) {
    // Pobieramy macierz odległości i liczbę miast
    std::vector<std::vector<int>> distances = instance.getDistances();
    int num_cities = instance.getCityCount();

    // Używamy stosu par (ścieżka, koszt)
    std::stack<std::pair<std::vector<int>, int>> s;
    std::vector<int> root_path;
    root_path.push_back(0); // Startujemy z miasta 0
    int root_cost = 0;

    s.push(std::make_pair(root_path, root_cost)); // Dodajemy węzeł początkowy do stosu

    int min_cost = INT_MAX;           // Minimalny znaleziony koszt
    std::vector<int> best_path;       // Najlepsza znaleziona ścieżka

    auto start = std::chrono::high_resolution_clock::now(); // Czas rozpoczęcia algorytmu

    while (!s.empty()) {
        // Pobieramy węzeł ze stosu
        std::pair<std::vector<int>, int> current = s.top();
        s.pop();
        std::vector<int> current_path = current.first;
        int current_cost = current.second;
        int current_level = current_path.size() - 1; // Obliczamy poziom na podstawie długości ścieżki

        // Sprawdzamy, czy odwiedziliśmy wszystkie miasta
        if (current_level == num_cities - 1) {
            // Dodajemy powrót do miasta startowego
            current_path.push_back(0);
            current_cost += distances[current_path[current_level]][0];

            if (current_cost < min_cost) {
                min_cost = current_cost;
                best_path = current_path;
            }
            continue;
        }

        // W DFS dodajemy dzieci w odwrotnej kolejności
        for (int i = num_cities - 1; i >= 0; --i) {
            // Sprawdzamy, czy miasto i jest już w aktualnej ścieżce
            if (!Utilities::isCityInPath(current_path, i)) {
                std::vector<int> child_path = current_path;
                child_path.push_back(i);
                int child_cost = current_cost + distances[current_path.back()][i];
                int child_level = current_level + 1;

                // Przycinanie gałęzi jeśli koszt jest mniejszy niż aktualny min_cost
                if (child_cost < min_cost) {
                    s.push(std::make_pair(child_path, child_cost));
                }
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now(); // Czas zakończenia algorytmu
    std::chrono::duration<double> seconds = end - start;
    std::chrono::duration<double, std::milli> milliseconds = end - start;
    std::chrono::duration<double, std::nano> nanoseconds = end - start;

    // Zapisujemy wyniki do pliku CSV
    SaveToCSV save("BranchAndBoundDFSResults.csv");
    save.saveResults("BranchAndBoundDFS", seconds, milliseconds, nanoseconds, best_path, min_cost);

    // Zwracamy najlepszą ścieżkę i jej koszt
    return std::make_pair(best_path, min_cost);
}
