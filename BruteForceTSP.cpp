#include "BruteForceTSP.h"
#include <algorithm>
#include <climits>

std::vector<int> BruteForceTSP::solve(const TSPInstance& instance) {
    int cityCount = instance.getCityCount();
    std::vector<int> cities(cityCount);
    for (int i = 0; i < cityCount; ++i) {
        cities[i] = i;
    }

    int bestCost = INT_MAX;
    std::vector<int> bestTour;

    permute(cities, 1, cityCount - 1, instance, bestCost, bestTour);
    return bestTour;
}

void BruteForceTSP::permute(std::vector<int>& cities, int l, int r, const TSPInstance& instance, int& bestCost, std::vector<int>& bestTour) {
    if (l == r) {
        int currentCost = calculateTourCost(instance, cities);
        if (currentCost < bestCost) {
            bestCost = currentCost;
            bestTour = cities;
        }
    } else {
        for (int i = l; i <= r; ++i) {
            std::swap(cities[l], cities[i]);
            permute(cities, l + 1, r, instance, bestCost, bestTour);
            std::swap(cities[l], cities[i]);  // Powrót do pierwotnej permutacji
        }
    }
}
