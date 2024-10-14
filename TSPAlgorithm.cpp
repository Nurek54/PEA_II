#include "TSPAlgorithm.h"

int TSPAlgorithm::calculateTourCost(const TSPInstance& instance, const std::vector<int>& tour) {
    int totalCost = 0;
    for (size_t i = 0; i < tour.size() - 1; ++i) {
        totalCost += instance.getCost(tour[i], tour[i + 1]);
    }
    totalCost += instance.getCost(tour.back(), tour[0]);  // Powrót do miasta początkowego
    return totalCost;
}
