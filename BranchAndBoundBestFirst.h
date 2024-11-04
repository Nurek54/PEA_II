#ifndef BRANCHANDBOUNDBESTFIRST_H
#define BRANCHANDBOUNDBESTFIRST_H

#include "TSPInstance.h"
#include <vector>
#include <utility>

class BranchAndBoundBestFirst {
public:
    std::pair<std::vector<int>, int> solve(const TSPInstance& instance);

private:
    struct Node {
        std::vector<int> path;     // Aktualna ścieżka
        int cost;                  // Koszt dotychczasowej ścieżki
        int lower_bound;           // Dolne ograniczenie (koszt + oszacowanie)
        int level;                 // Poziom drzewa (liczba odwiedzonych miast)
    };

    int calculateLowerBound(const std::vector<std::vector<int>>& distances, const std::vector<int>& path);
    void insertNode(std::vector<Node>& nodeList, const Node& node);  // Wstawia węzeł do listy zachowując sortowanie
};

#endif // BRANCHANDBOUNDBESTFIRST_H
