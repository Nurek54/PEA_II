#include "NearestNeighborTSP.h"
#include "SaveToCSV.h"
#include "TSPUtilities.h"  // Do obliczania kosztu trasy
#include <limits>
#include <chrono>
#include <iostream>
#include <cstdlib>  // Potrzebne do rand() i srand()
#include <ctime>    // Potrzebne do time()

pair<vector<int>, int> tsp_nearest_neighbor(const TSPInstance& instance) {
    vector<vector<int>> distances = instance.getDistances();
    int num_cities = instance.getCityCount();

    vector<int> tour;
    vector<bool> visited(num_cities, false);

    // Ustawienie ziarna dla funkcji rand(), aby za każdym razem uzyskać inne losowe wyniki
    srand(static_cast<unsigned int>(time(0)));

    // Wybór losowego miasta początkowego
    int currentCity = rand() % num_cities;
    tour.push_back(currentCity);
    visited[currentCity] = true;

    auto start = chrono::high_resolution_clock::now();

    for (int i = 1; i < num_cities; ++i) {
        int nearestCity = -1;
        int minCost = numeric_limits<int>::max();

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

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> seconds = end - start;
    chrono::duration<double, milli> milliseconds = end - start;
    chrono::duration<double, nano> nanoseconds = end - start;

    // Zamiast wywołania "calculate_cost", używamy "Utilities::calculate_cost"
    int totalCost = Utilities::calculate_cost(tour, distances);

    // Zapis wyników
    SaveToCSV save("NearestNeighborResults.csv");
    save.saveResults("NearestNeighbor", seconds, milliseconds, nanoseconds, tour, totalCost);

    return {tour, totalCost};
}
