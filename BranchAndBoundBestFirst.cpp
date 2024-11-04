#include "BranchAndBoundBestFirst.h"
#include "SaveToCSV.h"
#include "TSPUtilities.h"
#include <queue>
#include <chrono>
#include <limits>

struct Node {
    vector<int> path;
    int cost;
    int lower_bound;
    int level;

    bool operator>(const Node& other) const {
        return lower_bound > other.lower_bound;
    }
};

int BranchAndBoundBestFirst::calculateLowerBound(const vector<vector<int>>& distances, const vector<int>& path) {
    int lower_bound = 0;
    int num_cities = distances.size();

    vector<bool> visited(num_cities, false);
    for (size_t i = 0; i < path.size(); ++i) {
        visited[path[i]] = true;
    }

    // Dodaj koszt aktualnej ścieżki
    for (size_t i = 0; i < path.size() - 1; ++i) {
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

pair<vector<int>, int> BranchAndBoundBestFirst::solve(const TSPInstance& instance) {
    vector<vector<int>> distances = instance.getDistances();
    int num_cities = instance.getCityCount();

    auto cmp = [](const Node& a, const Node& b) { return a.lower_bound > b.lower_bound; };
    priority_queue<Node, vector<Node>, decltype(cmp)> pq(cmp);

    Node root;
    root.path.push_back(0); // Startujemy z miasta 0
    root.cost = 0;
    root.level = 0;
    root.lower_bound = calculateLowerBound(distances, root.path);

    pq.push(root);

    int min_cost = INT_MAX;
    vector<int> best_path;

    auto start = chrono::high_resolution_clock::now();

    while (!pq.empty()) {
        Node current = pq.top();
        pq.pop();

        if (current.lower_bound >= min_cost) {
            continue;
        }

        if (current.level == num_cities - 1) {
            // Dodaj powrót do miasta startowego
            current.path.push_back(0);
            current.cost += distances[current.path[current.level]][0];

            if (current.cost < min_cost) {
                min_cost = current.cost;
                best_path = current.path;
            }
            continue;
        }

        for (int i = 0; i < num_cities; ++i) {
            if (!Utilities::isCityInPath(current.path, i)) {
                Node child;
                child.path = current.path;
                child.path.push_back(i);
                child.level = current.level + 1;
                child.cost = current.cost + distances[current.path.back()][i];
                child.lower_bound = child.cost + calculateLowerBound(distances, child.path);

                if (child.lower_bound < min_cost) {
                    pq.push(child);
                }
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> seconds = end - start;
    chrono::duration<double, milli> milliseconds = end - start;
    chrono::duration<double, nano> nanoseconds = end - start;

    // Zapis wyników
    SaveToCSV save("BranchAndBoundBestFirstResults.csv");
    save.saveResults("BranchAndBoundBestFirst", seconds, milliseconds, nanoseconds, best_path, min_cost);

    return {best_path, min_cost};
}
