#include "TSPUtilities.h"
#include <cstdlib>
#include <ctime>

// Funkcja obliczająca koszt trasy
int Utilities::calculate_cost(const std::vector<int>& path, const std::vector<std::vector<int>>& distances) {
    int cost = 0;
    int num_cities = path.size();
    for (int i = 0; i < num_cities - 1; ++i) {
        cost += distances[path[i]][path[i + 1]];
    }
    cost += distances[path[num_cities - 1]][path[0]]; // Powrót do miasta początkowego
    return cost;
}

// Funkcja generująca losową macierz odległości (kosztów)
std::vector<std::vector<int>> Utilities::generate_random_matrix(int size, int minValue, int maxValue) {
    std::vector<std::vector<int>> matrix(size, std::vector<int>(size));

    // Ustawienie ziarna dla funkcji rand()
    srand(time(nullptr));

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (i == j) {
                matrix[i][j] = 0;  // Odległość do samego siebie to 0
            } else {
                matrix[i][j] = rand() % (maxValue - minValue + 1) + minValue;  // Losowe wartości z zakresu
            }
        }
    }
    return matrix;
}
