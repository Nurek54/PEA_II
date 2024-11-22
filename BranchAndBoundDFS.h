#ifndef BRANCHANDBOUNDDFS_H
#define BRANCHANDBOUNDDFS_H

class BranchAndBoundDFS {
public:
    BranchAndBoundDFS(const int** input_matrix, int num_cities);
    ~BranchAndBoundDFS();

    struct Result {
        int* path;
        int path_length;
        int cost;

        Result() : path(nullptr), path_length(0), cost(0) {}
        Result(int* p, int len, int c) : path(p), path_length(len), cost(c) {}
        ~Result() { delete[] path; }
    };

    Result solve();

private:
    int num_cities;
    int** matrix;
    int* minEdge; // Minimalne krawędzie dla każdego miasta

    void preprocessMinEdges();
};

#endif // BRANCHANDBOUNDDFS_H
