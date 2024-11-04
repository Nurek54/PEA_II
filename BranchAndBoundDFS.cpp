#include "BranchAndBoundDFS.h"
#include "SaveToCSV.h"
#include "TSPUtilities.h"
#include <stack>
#include <chrono>
#include <limits>


struct Node {
    vector<int> path;
    int cost;
    int level;
};

pair<vector<int>, int> BranchAndBoundDFS::solve(const TSPInstance& instance) {
    vector<vector<int>> distances = instance.getDistances();
    int num_cities = instance.getCityCount();

    stack<Node> s;
    Node root;
    root.path.push_back(0); // Startujemy z miasta 0
    root.cost = 0;
    root.level = 0;

    s.push(root);

    int min_cost = INT_MAX;
    vector<int> best_path;

    auto start = chrono::high_resolution_clock::now();

    while (!s.empty()) {
        Node current = s.top();
        s.pop();

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

        // W DFS dodajemy dzieci w odwrotnej kolejności
        for (int i = num_cities - 1; i >= 0; --i) {
            if (!Utilities::isCityInPath(current.path, i)) {
                Node child;
                child.path = current.path;
                child.path.push_back(i);
                child.level = current.level + 1;
                child.cost = current.cost + distances[current.path.back()][i];

                // Przycinanie gałęzi jeśli koszt jest mniejszy niż aktualny min_cost
                if (child.cost < min_cost) {
                    s.push(child);
                }
            }
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> seconds = end - start;
    chrono::duration<double, milli> milliseconds = end - start;
    chrono::duration<double, nano> nanoseconds = end - start;

    // Zapis wyników
    SaveToCSV save("BranchAndBoundDFSResults.csv");
    save.saveResults("BranchAndBoundDFS", seconds, milliseconds, nanoseconds, best_path, min_cost);

    return {best_path, min_cost};
}
