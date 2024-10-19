#ifndef BRUTEFORCETSP_H
#define BRUTEFORCETSP_H

#include <vector>
#include <utility>  // std::pair
#include "TSPInstance.h"

// Deklaracja funkcji brute force, która zwraca najlepszą trasę oraz jej koszt
std::pair<std::vector<int>, int> tsp_bruteforce(const TSPInstance& instance);

#endif
