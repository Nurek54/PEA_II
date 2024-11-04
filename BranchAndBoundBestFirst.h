#ifndef BRANCHANDBOUNDBESTFIRST_H
#define BRANCHANDBOUNDBESTFIRST_H

#include <vector>
#include "TSPInstance.h"

using namespace std;

class BranchAndBoundBestFirst {
public:
    BranchAndBoundBestFirst() {}
    pair<vector<int>, int> solve(const TSPInstance& instance);

private:
    int calculateLowerBound(const vector<vector<int>>& distances, const vector<int>& path);
};

#endif
