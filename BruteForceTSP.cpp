#include "BruteForceTSP.h"
#include <algorithm>
#include <climits>

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

    do {
        int current_cost = calculate_cost(cities, distances);
        if (current_cost < min_cost) {
            min_cost = current_cost;
            best_path = cities;
        }
    } while (std::next_permutation(cities.begin(), cities.end()));

    return {best_path, min_cost};
}
