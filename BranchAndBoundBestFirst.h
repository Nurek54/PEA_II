#ifndef BRANCHANDBOUNDBESTFIRST_H
#define BRANCHANDBOUNDBESTFIRST_H

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
    const int** distances;
    int num_cities;
    int* minEdge; // Minimalne krawędzie dla każdego miasta

    // Struktura węzła z prealokowaną ścieżką
    struct Node {
        int estimated_total_cost;
        int current_cost;
        int current_city;
        int path_length;
        int* path;

        Node(int num_cities);
        ~Node();
    };

    // Funkcje pomocnicze
    void preprocessMinEdges();
    int calculateLowerBound(Node* node);
    void insert(Node**& heap, int& heapSize, int& heapCapacity, Node* node);
    Node* remove(Node**& heap, int& heapSize);
};

#endif // BRANCHANDBOUNDBESTFIRST_H
