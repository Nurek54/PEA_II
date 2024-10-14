#ifndef RANDOMTSP_H
#define RANDOMTSP_H

#include "TSPInstance.h"
#include <vector>
#include <utility>  // Dla std::pair

std::pair<std::vector<int>, int> tsp_random(const TSPInstance& instance);

#endif // RANDOMTSP_H
