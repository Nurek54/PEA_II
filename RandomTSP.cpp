#include "RandomTSP.h"
#include <algorithm>  // Dla std::random_shuffle
#include <cstdlib>    // Dla srand() i rand()
#include <ctime>      // Dla time()

int calculate_cost(const std::vector<int>& path, const std::vector<std::vector<int>>& distances);

std::pair<std::vector<int>, int> tsp_random(const TSPInstance& instance) {
    std::vector<std::vector<int>> distances = instance.getDistances();
    int num_cities = instance.getCityCount();

    std::vector<int> tour(num_cities);
    for (int i = 0; i < num_cities; ++i) {
        tour[i] = i;
    }

    // Inicjalizacja generatora losowego
    srand((time(NULL)));

    // Tasowanie trasy losowo
    std::random_shuffle(tour.begin(), tour.end());

    // Obliczenie kosztu trasy
    int totalCost = calculate_cost(tour, distances);
    return {tour, totalCost};
}
