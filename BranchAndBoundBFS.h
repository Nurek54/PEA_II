#ifndef BRANCHANDBOUNDBFS_H
#define BRANCHANDBOUNDBFS_H

#include "TSPInstance.h"
#include <vector>
#include <utility>

class BranchAndBoundBFS {
public:
    std::pair<std::vector<int>, int> solve(const TSPInstance& instance);

private:
    struct Node {
        std::vector<int> path; // Aktualna ścieżka
        int cost;              // Koszt aktualnej ścieżki
        int level;             // Poziom w drzewie (liczba odwiedzonych miast)
    };
};

#endif // BRANCHANDBOUNDBFS_H
