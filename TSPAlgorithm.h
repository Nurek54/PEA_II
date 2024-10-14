#ifndef TSPALGORITHM_H
#define TSPALGORITHM_H

#include "TSPInstance.h"
#include <vector>

class TSPAlgorithm {
public:
    virtual std::vector<int> solve(const TSPInstance& instance) = 0;  // Główna metoda rozwiązująca problem
    virtual ~TSPAlgorithm() {}                                        // Wirtualny destruktor
protected:
    int calculateTourCost(const TSPInstance& instance, const std::vector<int>& tour);  // Oblicz koszt danej trasy
};

#endif // TSPALGORITHM_H
