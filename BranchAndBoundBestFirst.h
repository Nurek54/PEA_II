#ifndef BRANCHANDBOUNDBESTFIRST_H
#define BRANCHANDBOUNDBESTFIRST_H

#include <vector>
#include <string>
#include "TSPInstance.h"

class BranchAndBoundBestFirst {
public:
    BranchAndBoundBestFirst(const int** input_matrix, int num_cities);
    ~BranchAndBoundBestFirst();

    struct Result {
        int* path;
        int path_length;
        int cost;

        Result() : path(nullptr), path_length(0), cost(0) {}
        Result(int* p, int len, int c) : path(p), path_length(len), cost(c) {}
        ~Result() { delete[] path; }
    };

    Result solve(const TSPInstance& instance);

private:
    int num_cities;
    int** matrix;
    int* minEdge; // Minimalne krawędzie dla każdego miasta

    struct Node {
        int* path;
        int path_length;
        int current_city;
        int current_cost;
        int estimated_total_cost;

        Node(int num_cities);
        ~Node();
    };

    void preprocessMinEdges();
    // Usunięto własną implementację calculateLowerBound
    // Korzystamy teraz z Utilities::calculateLowerBound

    // Implementacja kopca
    void insert(Node**& heap, int& heapSize, int& heapCapacity, Node* node);
    Node* remove(Node**& heap, int& heapSize);
};

#endif // BRANCHANDBOUNDBESTFIRST_H
