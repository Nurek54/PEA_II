#ifndef TSPEXPERIMENT_H
#define TSPEXPERIMENT_H

#include "TSPAlgorithm.h"
#include <chrono>

class TSPExperiment {
public:
    void runExperiment(TSPAlgorithm& algorithm, const TSPInstance& instance);
};

#endif // TSPEXPERIMENT_H
