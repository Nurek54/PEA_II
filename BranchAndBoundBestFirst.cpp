#include "BranchAndBoundBestFirst.h"
#include "SaveToCSV.h"
#include "TSPUtilities.h"
#include <vector>
#include <climits>
#include <chrono>

std::pair<std::vector<int>, int> BranchAndBoundBestFirst::solve(const TSPInstance& instance) {
    std::vector<std::vector<int>> distances = instance.getDistances();
    int num_cities = instance.getCityCount();

    std::vector<Node> nodeList;
    Node root;
    root.path.push_back(0); // Startujemy z miasta 0
    root.cost = 0;
    root.level = 0;
    root.lower_bound = calculateLowerBound(distances, root.path);

    nodeList.push_back(root);

    int min_cost = INT_MAX;
    std::vector<int> best_path;

    auto start = std::chrono::high_resolution_clock::now();

    while (!nodeList.empty()) {
        Node current = nodeList.front();
        nodeList.erase(nodeList.begin());

        if (current.lower_bound >= min_cost) {
            continue;
        }

        if (current.level == num_cities - 1) {
            current.path.push_back(0);
            current.cost += distances[current.path[current.level]][0];

            if (current.cost < min_cost) {
                min_cost = current.cost;
                best_path = current.path;
            }
            continue;
        }

        for (int i = 0; i < num_cities; ++i) {
            // Używamy funkcji Utilities::isCityInPath zamiast pętli
            if (!Utilities::isCityInPath(current.path, i)) {
                Node child;
                child.path = current.path;
                child.path.push_back(i);
                child.level = current.level + 1;
                child.cost = current.cost + distances[current.path.back()][i];
                child.lower_bound = calculateLowerBound(distances, child.path);

                if (child.lower_bound < min_cost) {
                    insertNode(nodeList, child);
                }
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> seconds = end - start;
    std::chrono::duration<double, std::milli> milliseconds = end - start;
    std::chrono::duration<double, std::nano> nanoseconds = end - start;

    SaveToCSV save("BranchAndBoundBestFirstResults.csv");
    save.saveResults("BranchAndBoundBestFirst", seconds, milliseconds, nanoseconds, best_path, min_cost);

    return std::make_pair(best_path, min_cost);
}

int BranchAndBoundBestFirst::calculateLowerBound(const std::vector<std::vector<int>>& distances, const std::vector<int>& path) {
    int lower_bound = 0;
    int num_cities = distances.size();

    std::vector<bool> visited(num_cities, false);
    for (int i = 0; i < path.size(); ++i) {
        visited[path[i]] = true;
    }

    // Dodaj koszt aktualnej ścieżki
    for (int i = 0; i < path.size() - 1; ++i) {
        lower_bound += distances[path[i]][path[i + 1]];
    }

    // Oszacuj minimalny koszt pozostałych krawędzi
    for (int i = 0; i < num_cities; ++i) {
        if (!visited[i]) {
            int min_edge = INT_MAX;
            for (int j = 0; j < num_cities; ++j) {
                if (!visited[j] && distances[i][j] < min_edge && i != j) {
                    min_edge = distances[i][j];
                }
            }
            lower_bound += min_edge;
        }
    }

    return lower_bound;
}

void BranchAndBoundBestFirst::insertNode(std::vector<Node>& nodeList, const Node& node) {
    bool inserted = false;
    for (int i = 0; i < nodeList.size(); ++i) {
        if (node.lower_bound < nodeList[i].lower_bound) {
            nodeList.insert(nodeList.begin() + i, node);
            inserted = true;
            break;
        }
    }
    if (!inserted) {
        nodeList.push_back(node);
    }
}
