#include "BruteForceTSP.h"
#include "SaveToCSV.h"
#include "TSPUtilities.h"  // Dodaj nagłówek z klasą Utilities
#include <algorithm>
#include <climits>
#include <chrono>
#include <iostream>

std::pair<std::vector<int>, int> tsp_bruteforce(const TSPInstance& instance) {
    std::vector<std::vector<int>> distances = instance.getDistances();
    int num_cities = instance.getCityCount();

    std::vector<int> cities(num_cities);
    for (int i = 0; i < num_cities; ++i) {
        cities[i] = i;
    }

    int min_cost = INT_MAX;
    std::vector<int> best_path;

    auto start = std::chrono::high_resolution_clock::now();
    do {
        // Użycie Utilities::calculate_cost zamiast calculate_cost
        int current_cost = Utilities::calculate_cost(cities, distances);
        if (current_cost < min_cost) {
            min_cost = current_cost;
            best_path = cities;
        }
    } while (std::next_permutation(cities.begin(), cities.end()));
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> seconds = end - start;
    std::chrono::duration<double, std::milli> milliseconds = end - start;
    std::chrono::duration<double, std::nano> nanoseconds = end - start;

    // Użycie Utilities::calculate_cost zamiast calculate_cost
    int final_cost = Utilities::calculate_cost(best_path, distances);

    std::cout << "Algorytm Brute Force\n";
    std::cout << "Czas wykonania: " << seconds.count() << " s\n";

    SaveToCSV save("BruteForceResults.csv");
    save.saveResults("BruteForce", seconds, milliseconds, nanoseconds, best_path, final_cost);

    return {best_path, final_cost};
}
