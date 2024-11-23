#ifndef BRANCHANDBOUNDDFS_H
#define BRANCHANDBOUNDDFS_H

#include <string>

class BranchAndBoundDFS {
public:
    BranchAndBoundDFS(const int* const* input_matrix, int num_cities_input);
    ~BranchAndBoundDFS();

    struct Result {
        int* path;
        int path_length;
        int cost;

        Result() : path(nullptr), path_length(0), cost(0) {}
        Result(int* p, int len, int c) : path(p), path_length(len), cost(c) {}
        ~Result() { delete[] path; }
    };

    Result solve(const std::string& matrixType);

private:
    int num_cities;
    int** matrix;
    int* minEdge; // Minimalne krawędzie dla każdego miasta

    void preprocessMinEdges();
};

#endif // BRANCHANDBOUNDDFS_H
