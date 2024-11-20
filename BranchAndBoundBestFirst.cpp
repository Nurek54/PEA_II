#include "BranchAndBoundBestFirst.h"
#include "SaveToCSV.h"
#include "TSPUtilities.h"
#include <climits>
#include <chrono>
#include <iostream>

BranchAndBoundBestFirst::BranchAndBoundBestFirst(const int** input_matrix, int num_cities)
        : distances(input_matrix), num_cities(num_cities) {
    minEdge = new int[num_cities];
}

BranchAndBoundBestFirst::~BranchAndBoundBestFirst() {
    delete[] minEdge;
}

BranchAndBoundBestFirst::Node::Node(int num_cities) {
    path = new int[num_cities + 1]; // Prealokacja ścieżki
}

BranchAndBoundBestFirst::Node::~Node() {
    delete[] path;
}

void BranchAndBoundBestFirst::preprocessMinEdges() {
    for (int i = 0; i < num_cities; ++i) {
        int min_value = INT_MAX;
        for (int j = 0; j < num_cities; ++j) {
            if (i != j && distances[i][j] != -1 && distances[i][j] < min_value) {
                min_value = distances[i][j];
            }
        }
        minEdge[i] = (min_value != INT_MAX) ? min_value : 0;
    }
}

int BranchAndBoundBestFirst::calculateLowerBound(Node* node) {
    int path_length = node->path_length;
    const int* path = node->path;

    int current_cost = node->current_cost;
    int bound = current_cost;

    int last_node = path[path_length - 1];

    // Zbiór odwiedzonych miast
    bool* visited = new bool[num_cities]();
    for (int i = 0; i < path_length; ++i) {
        visited[path[i]] = true;
    }

    // Dodaj minimalny koszt powrotu do miasta początkowego
    int min_return = (distances[last_node][path[0]] != -1) ? distances[last_node][path[0]] : INT_MAX / 2;

    // Sumujemy minimalne koszty wejścia i wyjścia dla nieodwiedzonych miast
    for (int i = 0; i < num_cities; ++i) {
        if (!visited[i]) {
            int min_out = INT_MAX;
            int min_in = INT_MAX;

            for (int j = 0; j < num_cities; ++j) {
                if (i != j && distances[i][j] != -1 && distances[i][j] < min_out) {
                    min_out = distances[i][j];
                }
                if (i != j && distances[j][i] != -1 && distances[j][i] < min_in) {
                    min_in = distances[j][i];
                }
            }

            if (min_out == INT_MAX) min_out = minEdge[i];
            if (min_in == INT_MAX) min_in = minEdge[i];

            bound += (min_out + min_in);
        }
    }

    bound = (bound + min_return + 1) / 2;

    delete[] visited;

    return bound;
}

void BranchAndBoundBestFirst::insert(Node**& heap, int& heapSize, int& heapCapacity, Node* node) {
    if (heapSize >= heapCapacity) {
        int new_capacity = heapCapacity * 2;
        Node** new_heap = new Node*[new_capacity];
        for (int i = 0; i < heapSize; ++i) {
            new_heap[i] = heap[i];
        }
        delete[] heap;
        heap = new_heap;
        heapCapacity = new_capacity;
    }

    heap[heapSize] = node;
    int idx = heapSize;
    ++heapSize;

    // Przesuwanie elementu w górę kopca
    while (idx > 0 && heap[idx]->estimated_total_cost < heap[(idx - 1) / 2]->estimated_total_cost) {
        Node* temp = heap[idx];
        heap[idx] = heap[(idx - 1) / 2];
        heap[(idx - 1) / 2] = temp;
        idx = (idx - 1) / 2;
    }
}

BranchAndBoundBestFirst::Node* BranchAndBoundBestFirst::remove(Node**& heap, int& heapSize) {
    if (heapSize == 0) {
        return nullptr;
    }

    Node* node = heap[0];
    heap[0] = heap[heapSize - 1];
    --heapSize;

    int idx = 0;
    while (true) {
        int smallest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        if (left < heapSize && heap[left]->estimated_total_cost < heap[smallest]->estimated_total_cost) {
            smallest = left;
        }
        if (right < heapSize && heap[right]->estimated_total_cost < heap[smallest]->estimated_total_cost) {
            smallest = right;
        }
        if (smallest == idx) break;

        Node* temp = heap[idx];
        heap[idx] = heap[smallest];
        heap[smallest] = temp;

        idx = smallest;
    }

    return node;
}

BranchAndBoundBestFirst::Result BranchAndBoundBestFirst::solve(const TSPInstance& instance) {
    int best_cost = INT_MAX;
    int* best_path = nullptr;
    int best_path_length = 0;

    preprocessMinEdges();

    int heapCapacity = 1000;
    int heapSize = 0;
    Node** heap = new Node*[heapCapacity];

    // Tworzenie węzła początkowego
    Node* root = new Node(num_cities);
    root->path_length = 1;
    root->path[0] = 0; // Startujemy z miasta 0
    root->current_city = 0;
    root->current_cost = 0;
    root->estimated_total_cost = calculateLowerBound(root);

    insert(heap, heapSize, heapCapacity, root);

    bool* visited = new bool[num_cities];

    // Zapisujemy czas rozpoczęcia algorytmu
    auto start_time = std::chrono::high_resolution_clock::now();

    while (heapSize > 0) {
        Node* current_node = remove(heap, heapSize);

        // Aktualizacja odwiedzonych miast
        for (int i = 0; i < num_cities; ++i) {
            visited[i] = false;
        }
        for (int i = 0; i < current_node->path_length; ++i) {
            visited[current_node->path[i]] = true;
        }

        int last_node = current_node->current_city;

        // Jeśli odwiedziliśmy wszystkie miasta
        if (current_node->path_length == num_cities) {
            int total_cost = Utilities::calculate_cost(current_node->path, current_node->path_length, distances);
            if (total_cost < best_cost) {
                // Aktualizacja najlepszego kosztu i ścieżki
                best_cost = total_cost;
                if (best_path != nullptr) {
                    delete[] best_path;
                }
                best_path_length = current_node->path_length;
                best_path = new int[best_path_length];
                for (int i = 0; i < best_path_length; ++i) {
                    best_path[i] = current_node->path[i];
                }
            }
            delete current_node;
            continue;
        }

        // Generowanie nowych ścieżek
        for (int i = 0; i < num_cities; ++i) {
            if (!visited[i] && distances[last_node][i] != -1) {
                Node* child = new Node(num_cities);
                // Kopiowanie ścieżki
                for (int j = 0; j < current_node->path_length; ++j) {
                    child->path[j] = current_node->path[j];
                }
                child->path[current_node->path_length] = i;
                child->path_length = current_node->path_length + 1;
                child->current_city = i;
                child->current_cost = current_node->current_cost + distances[last_node][i];

                // Obliczamy dolne ograniczenie dla nowej ścieżki
                child->estimated_total_cost = calculateLowerBound(child);

                // Wczesne odrzucenie ścieżki
                if (child->estimated_total_cost <= best_cost) {
                    insert(heap, heapSize, heapCapacity, child);
                } else {
                    delete child;
                }
            }
        }

        delete current_node;
    }

    // Dodajemy koszt powrotu do miasta początkowego dla najlepszej ścieżki
    if (best_path != nullptr) {
        int final_cost = Utilities::calculate_cost(best_path, best_path_length, distances);
        best_cost = final_cost;
        // Dodajemy miasto początkowe na końcu ścieżki, aby zamknąć cykl
        int* complete_path = new int[best_path_length + 1];
        for (int i = 0; i < best_path_length; ++i) {
            complete_path[i] = best_path[i];
        }
        complete_path[best_path_length] = best_path[0];
        delete[] best_path;
        best_path = complete_path;
        best_path_length += 1;
    }

    // Zapisujemy czas zakończenia algorytmu
    auto end_time = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> seconds = end_time - start_time;
    std::chrono::duration<double, std::milli> milliseconds = end_time - start_time;
    std::chrono::duration<double, std::nano> nanoseconds = end_time - start_time;

    // Zapisywanie wyników do pliku CSV
    SaveToCSV save("BranchAndBoundBestFirstResults.csv");
    save.saveResults("BranchAndBoundBestFirst", seconds, milliseconds, nanoseconds, best_path, best_path_length, best_cost);

    // Czyszczenie pamięci
    for (int i = 0; i < heapSize; ++i) {
        delete heap[i];
    }
    delete[] heap;
    delete[] visited;

    return Result(best_path, best_path_length, best_cost);
}
