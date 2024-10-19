#include "NearestNeighborTSP.h"
#include "SaveToCSV.h"
#include "TSPUtilities.h"  // Do obliczania kosztu trasy
#include <limits>
#include <chrono>
#include <iostream>

std::pair<std::vector<int>, int> tsp_nearest_neighbor(const TSPInstance& instance) {
    std::vector<std::vector<int>> distances = instance.getDistances();
    int num_cities = instance.getCityCount();

    std::vector<int> tour;
    std::vector<bool> visited(num_cities, false);

    int currentCity = 0;
    tour.push_back(currentCity);
    visited[currentCity] = true;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 1; i < num_cities; ++i) {
        int nearestCity = -1;
        int minCost = std::numeric_limits<int>::max();

        for (int j = 0; j < num_cities; ++j) {
            if (!visited[j] && distances[currentCity][j] < minCost) {
                nearestCity = j;
                minCost = distances[currentCity][j];
            }
        }

        currentCity = nearestCity;
        tour.push_back(currentCity);
        visited[currentCity] = true;
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> seconds = end - start;
    std::chrono::duration<double, std::milli> milliseconds = end - start;
    std::chrono::duration<double, std::nano> nanoseconds = end - start;

    // Zamiast wywołania "calculate_cost", używamy "Utilities::calculate_cost"
    int totalCost = Utilities::calculate_cost(tour, distances);

    //std::cout << "Algorytm Najbliższych Sąsiadów\n";
    //std::cout << "Czas wykonania: " << seconds.count() << " s\n";

    SaveToCSV save("NearestNeighborResults.csv");
    save.saveResults("NearestNeighbor", seconds, milliseconds, nanoseconds, tour, totalCost);

    return {tour, totalCost};
}
