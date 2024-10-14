#ifndef NEARESTNEIGHBORTSP_H
#define NEARESTNEIGHBORTSP_H

#include "TSPAlgorithm.h"

class NearestNeighborTSP : public TSPAlgorithm {
public:
    std::vector<int> solve(const TSPInstance& instance) override;
};

#endif // NEARESTNEIGHBORTSP_H
