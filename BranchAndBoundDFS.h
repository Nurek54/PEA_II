#ifndef BRANCHANDBOUNDDFS_H
#define BRANCHANDBOUNDDFS_H

#include <vector>
#include "TSPInstance.h"

using namespace std;

class BranchAndBoundDFS {
public:
    BranchAndBoundDFS() {}
    pair<vector<int>, int> solve(const TSPInstance& instance);

private:
};

#endif
