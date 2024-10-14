#ifndef BRUTEFORCETSP_H
#define BRUTEFORCETSP_H

#include "TSPInstance.h"
#include <vector>
#include <utility> // for std::pair

std::pair<std::vector<int>, int> tsp_bruteforce(const TSPInstance& instance);

#endif // BRUTEFORCETSP_H
