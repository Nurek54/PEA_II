#include "BruteForceTSP.h"
#include <algorithm>
#include <climits>
#include <chrono>  // Do mierzenia czasu
#include <fstream>  // Do zapisu pliku CSV
#include <iostream> // Do wyświetlania wyników
#include <iomanip>  // Do precyzyjnego formatowania liczb

int calculate_cost(const std::vector<int>& path, const std::vector<std::vector<int>>& distances) {
    int cost = 0;
    int num_cities = path.size();
    for (int i = 0; i < num_cities - 1; ++i) {
        cost += distances[path[i]][path[i + 1]];
    }
    cost += distances[path[num_cities - 1]][path[0]]; // Powrót do miasta początkowego
    return cost;
}

std::pair<std::vector<int>, int> tsp_bruteforce(const TSPInstance& instance) {
    std::vector<std::vector<int>> distances = instance.getDistances();
    int num_cities = instance.getCityCount();

    std::vector<int> cities(num_cities);
    for (int i = 0; i < num_cities; ++i) {
        cities[i] = i;
    }

    int min_cost = INT_MAX;
    std::vector<int> best_path;

    auto start = std::chrono::high_resolution_clock::now();  // Start pomiaru czasu
    do {
        int current_cost = calculate_cost(cities, distances);
        if (current_cost < min_cost) {
            min_cost = current_cost;
            best_path = cities;
        }
    } while (std::next_permutation(cities.begin(), cities.end()));
    auto end = std::chrono::high_resolution_clock::now();  // Koniec pomiaru czasu

    // Obliczamy czasy w różnych jednostkach
    std::chrono::duration<double> seconds = end - start;
    std::chrono::duration<double, std::milli> milliseconds = end - start;
    std::chrono::duration<double, std::nano> nanoseconds = end - start;

    // Obliczamy koszt trasy (poza pomiarem czasu)
    int final_cost = calculate_cost(best_path, distances);

    // Wyświetlanie wyników na konsoli
    std::cout << "Algorytm Brute Force\n";
    std::cout << "Czas wykonania:\n";
    std::cout << "  W sekundach: " << seconds.count() << " s\n";
    std::cout << "  W milisekundach: " << milliseconds.count() << " ms\n";
    std::cout << "  W nanosekundach: " << nanoseconds.count() << " ns\n";

    std::cout << "Najlepsza trasa: ";
    for (int city : best_path) {
        std::cout << city << " ";
    }
    std::cout << "\nKoszt: " << final_cost << "\n";

    // Zapis wyników do pliku CSV
    std::ofstream csvFile("results.csv", std::ios::app);  // Tryb dodawania do pliku
    if (csvFile.is_open()) {
        // Sprawdzenie, czy plik jest nowy, i jeśli tak, dodanie nagłówka
        static bool isFileNew = true;
        if (isFileNew) {
            csvFile << "Algorithm | Seconds | Milliseconds | Nanoseconds | Path | Cost\n";  // Nagłówek CSV
            isFileNew = false;
        }

        csvFile << std::fixed << std::setprecision(6)  // Ustaw precyzję na 6 miejsc po przecinku
                << "BruteForce" << " | "
                << seconds.count() << " | "
                << milliseconds.count() << " | "
                << nanoseconds.count() << " | ";

        // Zapisz trasę oddzielając miasta " | "
        for (size_t i = 0; i < best_path.size(); ++i) {
            csvFile << best_path[i];
            if (i != best_path.size() - 1) {
                csvFile << " | ";  // Oddziel miasta " | "
            }
        }

        csvFile << " | " << final_cost << "\n";  // Zakończ linię pliku z kosztem trasy
        csvFile.close();
        std::cout << "Wyniki zapisano do pliku: results.csv\n";
    } else {
        std::cerr << "Nie można otworzyć pliku: results.csv\n";
    }

    return {best_path, final_cost};
}
