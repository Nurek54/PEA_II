#ifndef BRANCHANDBOUNDDFSSYMMETRIC_H
#define BRANCHANDBOUNDDFSSYMMETRIC_H

#include "TSPInstance.h"

class BranchAndBoundDFSSymmetric {
public:
    BranchAndBoundDFSSymmetric(const int** input_matrix, int num_cities);
    ~BranchAndBoundDFSSymmetric();

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

    // Własny stos zoptymalizowany dla macierzy symetrycznych
    struct Stack {
        struct StackNode {
            int* path;
            int path_length;
            int cost;
            int bound;
        };

        StackNode* nodes;
        int size;
        int capacity;

        Stack(int initial_capacity = 1000) : size(0), capacity(initial_capacity) {
            nodes = new StackNode[capacity];
        }

        ~Stack() {
            for (int i = 0; i < size; ++i) {
                delete[] nodes[i].path;
            }
            delete[] nodes;
        }

        void push(const StackNode& node) {
            if (size >= capacity) {
                capacity *= 2;
                StackNode* new_nodes = new StackNode[capacity];
                for (int i = 0; i < size; ++i) {
                    new_nodes[i] = nodes[i];
                }
                delete[] nodes;
                nodes = new_nodes;
            }
            nodes[size++] = node;
        }

        StackNode pop() {
            return nodes[--size];
        }

        bool empty() const {
            return size == 0;
        }
    };

    // Funkcja generująca dzieci z optymalizacją dla macierzy symetrycznych
    void generateChildren(Stack& s, const int* path, int path_length, int current_cost, int bound, int& min_cost);
};

#endif // BRANCHANDBOUNDDFSSYMMETRIC_H
