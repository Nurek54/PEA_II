#ifndef BRUTEFORCETSP_H
#define BRUTEFORCETSP_H

#include <vector>
#include <utility>  // std::pair
#include "TSPInstance.h"

using namespace std;

// Deklaracja funkcji brute force, która zwraca najlepszą trasę oraz jej koszt
pair<vector<int>, int> tsp_bruteforce(const TSPInstance& instance);

#endif
