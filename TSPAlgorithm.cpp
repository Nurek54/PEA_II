#include "TSPAlgorithm.h"  // Dołączenie nagłówka klasy TSPAlgorithm
#include <vector>

int TSPAlgorithm::calculateTourCost(const TSPInstance& instance, const std::vector<int>& tour) {
    int totalCost = 0;
    const std::vector<std::vector<int>>& distances = instance.getDistances();  // Pobranie macierzy kosztów

    for (size_t i = 0; i < tour.size() - 1; ++i) {
        totalCost += distances[tour[i]][tour[i + 1]];  // Dodanie kosztu przejścia między miastami
    }
    totalCost += distances[tour.back()][tour[0]];  // Powrót do miasta początkowego
    return totalCost;
}
