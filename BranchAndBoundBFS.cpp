// BranchAndBoundBFS.cpp
#include "BranchAndBoundBFS.h"
#include "SaveToCSV.h"
#include <climits>
#include <chrono>
#include <iostream>

BranchAndBoundBFS::BranchAndBoundBFS(const int** input_matrix, int num_cities)
        : distances(input_matrix), num_cities(num_cities) {}

BranchAndBoundBFS::~BranchAndBoundBFS() {
    // Nic do zrobienia
}

BranchAndBoundBFS::Result BranchAndBoundBFS::solve() {
    // Inicjalizacja kolejki
    std::queue<Node*> queue;
    std::vector<Node*> all_nodes; // Przechowujemy wszystkie węzły, aby je później usunąć

    // Węzeł początkowy
    bool* initial_visited = new bool[num_cities]();
    initial_visited[0] = true;
    Node* root = new Node(0, 0, 0, initial_visited, nullptr);

    queue.push(root);
    all_nodes.push_back(root);

    int min_cost = INT_MAX;
    Node* best_node = nullptr;

    auto start_time = std::chrono::high_resolution_clock::now();

    while (!queue.empty()) {
        Node* current = queue.front();
        queue.pop();

        if (current->cost >= min_cost) {
            continue; // Nie usuwamy current tutaj
        }

        if (current->level == num_cities - 1) {
            int return_cost = distances[current->city][0];

            if (return_cost != -1) {
                int total_cost = current->cost + return_cost;

                if (total_cost < min_cost) {
                    min_cost = total_cost;
                    best_node = current;
                }
            }
            continue; // Nie usuwamy current tutaj
        }

        for (int i = 0; i < num_cities; ++i) {
            if (!current->visited[i] && distances[current->city][i] != -1) {
                int edge_cost = distances[current->city][i];
                int new_cost = current->cost + edge_cost;

                if (new_cost >= min_cost) {
                    continue;
                }

                // Tworzymy nową tablicę visited dla dziecka
                bool* child_visited = new bool[num_cities];
                for (int j = 0; j < num_cities; ++j) {
                    child_visited[j] = current->visited[j];
                }
                child_visited[i] = true;

                Node* child = new Node(i, new_cost, current->level + 1, child_visited, current);
                queue.push(child);
                all_nodes.push_back(child);
            }
        }
    }

    // Odtwarzamy ścieżkę z best_node
    int* best_path = nullptr;
    int best_path_length = 0;
    if (best_node != nullptr) {
        reconstructPath(best_node, best_path, best_path_length);
        // Dodajemy miasto początkowe na końcu ścieżki
        int* complete_path = new int[best_path_length + 1];
        for (int i = 0; i < best_path_length; ++i) {
            complete_path[best_path_length - i - 1] = best_path[i];
        }
        complete_path[best_path_length] = 0;
        delete[] best_path;
        best_path = complete_path;
        best_path_length += 1;
    }

    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> seconds = end_time - start_time;
    std::chrono::duration<double, std::milli> milliseconds = end_time - start_time;
    std::chrono::duration<double, std::nano> nanoseconds = end_time - start_time;

    // Zapisujemy wyniki do pliku CSV
    SaveToCSV save("BranchAndBoundBFSResults.csv");
    save.saveResults("BranchAndBoundBFS", seconds, milliseconds, nanoseconds, best_path, best_path_length, min_cost);

    // Usuwamy wszystkie węzły
    for (Node* node : all_nodes) {
        delete node;
    }
    all_nodes.clear();

    // Zwracamy najlepszą ścieżkę i jej koszt
    return Result(best_path, best_path_length, min_cost);
}

void BranchAndBoundBFS::reconstructPath(Node* node, int*& path, int& path_length) {
    // Obliczamy długość ścieżki
    path_length = node->level + 1;
    path = new int[path_length];
    Node* current = node;
    int index = 0;
    while (current != nullptr) {
        path[index++] = current->city;
        current = current->parent;
    }
}
