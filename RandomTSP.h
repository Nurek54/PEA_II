#ifndef RANDOMTSP_H
#define RANDOMTSP_H

#include "TSPAlgorithm.h"
#include <vector>

class RandomTSP : public TSPAlgorithm {
public:
    std::vector<int> solve(const TSPInstance& instance) override;
};

#endif // RANDOMTSP_H
