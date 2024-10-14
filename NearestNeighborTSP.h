#ifndef NEARESTNEIGHBORTSP_H
#define NEARESTNEIGHBORTSP_H

#include "TSPInstance.h"
#include <vector>
#include <utility> // for std::pair

std::pair<std::vector<int>, int> tsp_nearest_neighbor(const TSPInstance& instance);

#endif // NEARESTNEIGHBORTSP_H
