#ifndef BRUTEFORCETSP_H
#define BRUTEFORCETSP_H

#include "TSPAlgorithm.h"
#include <vector>

class BruteForceTSP : public TSPAlgorithm {
public:
    std::vector<int> solve(const TSPInstance& instance) override;  // Implementacja algorytmu
private:
    void permute(std::vector<int>& cities, int l, int r, const TSPInstance& instance, int& bestCost, std::vector<int>& bestTour);
};

#endif // BRUTEFORCETSP_H
