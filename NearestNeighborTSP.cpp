#include "NearestNeighborTSP.h"
#include <vector>
#include <limits>

std::vector<int> NearestNeighborTSP::solve(const TSPInstance& instance) {
    int cityCount = instance.getCityCount();
    std::vector<int> tour;
    std::vector<bool> visited(cityCount, false);

    int currentCity = 0;
    tour.push_back(currentCity);
    visited[currentCity] = true;

    for (int i = 1; i < cityCount; ++i) {
        int nearestCity = -1;
        int minCost = std::numeric_limits<int>::max();

        for (int j = 0; j < cityCount; ++j) {
            if (!visited[j] && instance.getCost(currentCity, j) < minCost) {
                nearestCity = j;
                minCost = instance.getCost(currentCity, j);
            }
        }

        currentCity = nearestCity;
        tour.push_back(currentCity);
        visited[currentCity] = true;
    }

    return tour;
}
