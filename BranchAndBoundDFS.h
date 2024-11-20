#ifndef BRANCHANDBOUNDDFS_H
#define BRANCHANDBOUNDDFS_H

#include "TSPInstance.h"

class BranchAndBoundDFS {
public:
    BranchAndBoundDFS(const int** input_matrix, int num_cities);
    ~BranchAndBoundDFS();

    struct Result {
        int* path;
        int path_length;
        int cost;

        Result() : path(nullptr), path_length(0), cost(0) {}
        ~Result() { delete[] path; }
    };

    Result solve();

private:
    int** matrix;          // Macierz kosztów, dynamicznie alokowana
    int num_cities;        // Liczba miast

    void dfs(int node, int cost, int* path, bool* visited, int path_length, int& best_cost, int*& best_path, int& best_path_length);
    int calculateBound(int node, const bool* visited);  // Funkcja obliczająca dolną granicę (bound)
    void quickSort(int* neighbors, int* bounds, int left, int right);  // Funkcja pomocnicza do QuickSort
};

#endif // BRANCHANDBOUNDDFS_H
