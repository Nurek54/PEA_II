#include "RandomTSP.h"
#include <algorithm>
#include <random>

std::vector<int> RandomTSP::solve(const TSPInstance& instance) {
    int cityCount = instance.getCityCount();
    std::vector<int> tour(cityCount);
    for (int i = 0; i < cityCount; ++i) {
        tour[i] = i;
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(tour.begin(), tour.end(), g);

    return tour;
}
