#ifndef BRANCHANDBOUNDBFS_H
#define BRANCHANDBOUNDBFS_H

#include <string>

// Przed deklaracją klas SaveToCSV i TSPInstance zakładamy, że są one zdefiniowane gdzie indziej
class TSPInstance;
class SaveToCSV;

class BranchAndBoundBFS {
public:
    // Struktura wyników algorytmu
    struct Result {
        int* path;
        int path_length;
        int cost;

        Result() : path(nullptr), path_length(0), cost(0) {}
        Result(int* p, int len, int c) : path(p), path_length(len), cost(c) {}
        ~Result() { delete[] path; }
    };

    // Konstruktor i destruktor
    BranchAndBoundBFS(const int** input_matrix, int num_cities_input);
    ~BranchAndBoundBFS();

    // Główna funkcja rozwiązująca problem
    Result solve();

private:
    int num_cities;    // Liczba miast
    int** matrix;      // Macierz kosztów
    int* minEdge;      // Minimalne krawędzie dla każdego miasta

    // Funkcja do wstępnej obróbki minimalnych krawędzi
    void preprocessMinEdges();

    // Wyłączamy konstruktor kopiujący i operator przypisania
    BranchAndBoundBFS(const BranchAndBoundBFS&) = delete;
    BranchAndBoundBFS& operator=(const BranchAndBoundBFS&) = delete;

    // Własna implementacja kolejki
    struct Queue {
        struct QueueNode {
            int* path;
            int path_length;
            int cost;
            int bound;
        };

        QueueNode* nodes;   // Dynamicznie alokowana tablica węzłów
        int front;          // Indeks frontu
        int rear;           // Indeks tyłu
        int size;           // Aktualny rozmiar kolejki
        int capacity;       // Maksymalna pojemność

        // Konstruktor
        Queue(int initial_capacity = 1000) : front(0), rear(initial_capacity - 1), size(0), capacity(initial_capacity) {
            nodes = new QueueNode[capacity];
        }

        // Destruktor
        ~Queue() {
            for (int i = 0; i < size; ++i) {
                int index = (front + i) % capacity;
                if (nodes[index].path != nullptr) {
                    delete[] nodes[index].path;
                }
            }
            delete[] nodes;
        }

        // Funkcja enqueue - dodaje węzeł do kolejki
        void enqueue(const QueueNode& node) {
            if (size >= capacity) {
                // Zwiększenie pojemności kolejki (podwajanie)
                int new_capacity = capacity * 2;
                QueueNode* new_nodes = new QueueNode[new_capacity];
                for (int i = 0; i < size; ++i) {
                    int old_index = (front + i) % capacity;
                    new_nodes[i] = nodes[old_index];
                }
                delete[] nodes;
                nodes = new_nodes;
                front = 0;
                rear = size - 1;
                capacity = new_capacity;
            }
            rear = (rear + 1) % capacity;
            nodes[rear] = node;
            size++;
        }

        // Funkcja dequeue - usuwa i zwraca węzeł z frontu kolejki
        QueueNode dequeue() {
            QueueNode node = {nullptr, 0, 0, 0};
            if (empty()) {
                // Można rzucić wyjątek lub obsłużyć pustą kolejkę inaczej
                return node;
            }
            node = nodes[front];
            front = (front + 1) % capacity;
            size--;
            return node;
        }

        // Funkcja sprawdzająca, czy kolejka jest pusta
        bool empty() const {
            return size == 0;
        }
    };
};

#endif // BRANCHANDBOUNDBFS_H
