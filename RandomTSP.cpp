#include "RandomTSP.h"
#include "SaveToCSV.h"
#include "TSPUtilities.h"  // Do obliczania kosztu trasy
#include <cstdlib>
#include <chrono>
#include <iostream>
#include <ctime>  // Do ustawienia ziarna dla rand()

void generate_random_permutation(std::vector<int>& tour) {
    int n = tour.size();
    srand(time(nullptr));

    for (int i = n - 1; i > 0; --i) {
        int j = rand() % (i + 1);
        std::swap(tour[i], tour[j]);
    }
}

std::pair<std::vector<int>, int> tsp_random(const TSPInstance& instance) {
    std::vector<std::vector<int>> distances = instance.getDistances();
    int num_cities = instance.getCityCount();

    int iterations = 10000;
    std::vector<int> best_tour;
    int min_cost = INT_MAX;

    auto start = std::chrono::high_resolution_clock::now();

    for (int iter = 0; iter < iterations; ++iter) {
        std::vector<int> current_tour(num_cities);
        for (int i = 0; i < num_cities; ++i) {
            current_tour[i] = i;
        }

        generate_random_permutation(current_tour);

        // Zamiast wywołania "calculate_cost", używamy "Utilities::calculate_cost"
        int current_cost = Utilities::calculate_cost(current_tour, distances);

        if (current_cost < min_cost) {
            min_cost = current_cost;
            best_tour = current_tour;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> seconds = end - start;
    std::chrono::duration<double, std::milli> milliseconds = end - start;
    std::chrono::duration<double, std::nano> nanoseconds = end - start;

    std::cout << "Losowy Algorytm (z iteracjami)\n";
    std::cout << "Czas wykonania: " << seconds.count() << " s\n";
    std::cout << "Najlepszy koszt po " << iterations << " iteracjach: " << min_cost << "\n";

    SaveToCSV save("RandomResults.csv");
    save.saveResults("Random", seconds, milliseconds, nanoseconds, best_tour, min_cost);

    return {best_tour, min_cost};
}
