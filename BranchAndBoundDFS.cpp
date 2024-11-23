#include "BranchAndBoundDFS.h"
#include "SaveToCSV.h"
#include "TSPUtilities.h"
#include <chrono>
#include <climits>
#include <iostream>

BranchAndBoundDFS::BranchAndBoundDFS(const int* const* input_matrix, int num_cities_input)
        : num_cities(num_cities_input) {    matrix = new int*[num_cities];
    for (int i = 0; i < num_cities; ++i) {
        matrix[i] = new int[num_cities];
        for (int j = 0; j < num_cities; ++j) {
            matrix[i][j] = input_matrix[i][j];
        }
    }
    minEdge = new int[num_cities];
    preprocessMinEdges();
}

BranchAndBoundDFS::~BranchAndBoundDFS() {
    for (int i = 0; i < num_cities; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;
    delete[] minEdge;
}

void BranchAndBoundDFS::preprocessMinEdges() {
    for (int i = 0; i < num_cities; ++i) {
        int min_value = INT_MAX;
        for (int j = 0; j < num_cities; ++j) {
            if (i != j && matrix[i][j] != -1 && matrix[i][j] < min_value) {
                min_value = matrix[i][j];
            }
        }
        minEdge[i] = (min_value != INT_MAX) ? min_value : 0;
    }
}

BranchAndBoundDFS::Result BranchAndBoundDFS::solve() {
    struct StackNode {
        int* path;
        int path_length;
        int cost;
        int bound;
    };

    struct Stack {
        StackNode* nodes;
        int size;
        int capacity;

        Stack(int initial_capacity = 1000) {
            nodes = new StackNode[initial_capacity];
            size = 0;
            capacity = initial_capacity;
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

    Stack s;
    int* root_path = new int[1];
    root_path[0] = 0;

    int root_bound = Utilities::calculateLowerBound(root_path, 1, matrix, minEdge, num_cities);
    s.push({root_path, 1, 0, root_bound});

    int min_cost = INT_MAX;
    int* best_path = nullptr;
    int best_path_length = 0;

    auto start_time = std::chrono::high_resolution_clock::now();

    while (!s.empty()) {
        StackNode current = s.pop();
        int* current_path = current.path;
        int current_path_length = current.path_length;
        int current_cost = current.cost;
        int current_bound = current.bound;

        if (current_bound >= min_cost) {
            delete[] current_path;
            continue;
        }

        if (current_path_length == num_cities) {
            int* complete_path = new int[current_path_length + 1];
            for (int i = 0; i < current_path_length; ++i) {
                complete_path[i] = current_path[i];
            }
            complete_path[current_path_length] = current_path[0];

            int total_cost = Utilities::calculate_cost(complete_path, current_path_length + 1, matrix, true);
            if (total_cost < min_cost) {
                min_cost = total_cost;
                delete[] best_path;
                best_path_length = current_path_length + 1;
                best_path = complete_path;
            } else {
                delete[] complete_path;
            }
            delete[] current_path;
            continue;
        }

        for (int i = num_cities - 1; i >= 0; --i) {
            if (!Utilities::isCityInPath(current_path, current_path_length, i)) {
                int* child_path = new int[current_path_length + 1];
                for (int j = 0; j < current_path_length; ++j) {
                    child_path[j] = current_path[j];
                }
                child_path[current_path_length] = i;

                int temp_cost = Utilities::calculate_cost(child_path, current_path_length + 1, matrix, false);
                int child_bound = Utilities::calculateLowerBound(child_path, current_path_length + 1, matrix, minEdge, num_cities);

                if (child_bound < min_cost) {
                    s.push({child_path, current_path_length + 1, temp_cost, child_bound});
                } else {
                    delete[] child_path;
                }
            }
        }
        delete[] current_path;
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> seconds = end_time - start_time;
    std::chrono::duration<double, std::milli> milliseconds = end_time - start_time;
    std::chrono::duration<double, std::nano> nanoseconds = end_time - start_time;

    SaveToCSV save("BranchAndBoundDFSResults.csv");
    save.saveResults("BranchAndBoundDFS", seconds, milliseconds, nanoseconds, best_path, best_path_length, min_cost);

    Result result;
    result.path = best_path;
    result.path_length = best_path_length;
    result.cost = min_cost;

    return result;
}
