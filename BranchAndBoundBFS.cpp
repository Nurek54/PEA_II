#include "BranchAndBoundBFS.h"
#include "SaveToCSV.h"
#include "TSPUtilities.h"
#include <queue>
#include <chrono>
#include <limits>

struct Node {
    vector<int> path;
    int cost;
    int level;
};

pair<vector<int>, int> BranchAndBoundBFS::solve(const TSPInstance& instance) {
    vector<vector<int>> distances = instance.getDistances();
    int num_cities = instance.getCityCount();

    queue<Node> q;
    Node root;
    root.path.push_back(0); // Startujemy z miasta 0
    root.cost = 0;
    root.level = 0;

    q.push(root);

    int min_cost = INT_MAX;
    vector<int> best_path;

    auto start = chrono::high_resolution_clock::now();

    while (!q.empty()) {
        Node current = q.front();
        q.pop();

        // Przycinanie gałęzi, jeśli aktualny koszt przekracza min_cost
        if (current.cost >= min_cost) {
            continue;
        }

        if (current.level == num_cities - 1) {
            // Dodaj powrót do miasta startowego
            int return_cost = distances[current.path.back()][0];
            if (return_cost != -1) {
                int total_cost = current.cost + return_cost;
                if (total_cost < min_cost) {
                    min_cost = total_cost;
                    best_path = current.path;
                    best_path.push_back(0); // Dodajemy miasto startowe na koniec ścieżki
                }
            }
            continue;
        }

        for (int i = 0; i < num_cities; ++i) {
            if (!Utilities::isCityInPath(current.path, i)) {
                int edge_cost = distances[current.path.back()][i];
                if (edge_cost != -1) {
                    Node child;
                    child.path = current.path;
                    child.path.push_back(i);
                    child.level = current.level + 1;
                    child.cost = current.cost + edge_cost;

                    // Przycinanie gałęzi, jeśli koszt jest mniejszy niż aktualny min_cost
                    if (child.cost < min_cost) {
                        q.push(child);
                    }
                }
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> seconds = end - start;
    chrono::duration<double, milli> milliseconds = end - start;
    chrono::duration<double, nano> nanoseconds = end - start;

    // Zapis wyników
    SaveToCSV save("BranchAndBoundBFSResults.csv");
    save.saveResults("BranchAndBoundBFS", seconds, milliseconds, nanoseconds, best_path, min_cost);

    return {best_path, min_cost};
}
