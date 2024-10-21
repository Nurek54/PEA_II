#ifndef NEARESTNEIGHBORTSP_H
#define NEARESTNEIGHBORTSP_H

#include "TSPInstance.h"
#include <vector>
#include <utility> // for std::pair

using namespace std;

pair<vector<int>, int> tsp_nearest_neighbor(const TSPInstance& instance);

#endif // NEARESTNEIGHBORTSP_H
