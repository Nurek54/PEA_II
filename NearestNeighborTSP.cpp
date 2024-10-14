#include "NearestNeighborTSP.h"
#include <limits>

int calculate_cost(const std::vector<int>& path, const std::vector<std::vector<int>>& distances);

std::pair<std::vector<int>, int> tsp_nearest_neighbor(const TSPInstance& instance) {
    std::vector<std::vector<int>> distances = instance.getDistances();
    int num_cities = instance.getCityCount();

    std::vector<int> tour;
    std::vector<bool> visited(num_cities, false);

    int currentCity = 0;
    tour.push_back(currentCity);
    visited[currentCity] = true;

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

    int totalCost = calculate_cost(tour, distances);
    return {tour, totalCost};
}
