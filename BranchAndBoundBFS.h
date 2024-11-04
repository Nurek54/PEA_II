#ifndef BRANCHANDBOUNDBFS_H
#define BRANCHANDBOUNDBFS_H

#include <vector>
#include "TSPInstance.h"

using namespace std;

class BranchAndBoundBFS {
public:
    BranchAndBoundBFS() {}
    pair<vector<int>, int> solve(const TSPInstance& instance);

private:
};

#endif
