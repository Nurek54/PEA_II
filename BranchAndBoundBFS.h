// BranchAndBoundBFS.h
#ifndef BRANCHANDBOUNDBFS_H
#define BRANCHANDBOUNDBFS_H

#include "TSPInstance.h"
#include <queue>

class BranchAndBoundBFS {
public:
    BranchAndBoundBFS(const int** input_matrix, int num_cities);
    ~BranchAndBoundBFS();

    struct Result {
        int* path;
        int path_length;
        int cost;

        Result() : path(nullptr), path_length(0), cost(0) {}
        Result(int* p, int len, int c) : path(p), path_length(len), cost(c) {}
        ~Result() { delete[] path; }
    };

    struct Node {
        int city;
        int cost;
        int level;
        bool* visited;
        Node* parent;

        Node(int city, int cost, int level, bool* visited, Node* parent)
                : city(city), cost(cost), level(level), visited(visited), parent(parent) {}
        ~Node() { delete[] visited; }
    };

    Result solve();

private:
    const int** distances;
    int num_cities;

    void reconstructPath(Node* node, int*& path, int& path_length);
};

#endif // BRANCHANDBOUNDBFS_H
