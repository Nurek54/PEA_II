#ifndef TSPUTILITIES_H
#define TSPUTILITIES_H

#include <vector>

class Utilities {
public:
    // Funkcja do obliczania kosztu trasy
    static int calculate_cost(const std::vector<int>& path, const std::vector<std::vector<int>>& distances);

    // Funkcja do generowania losowej macierzy odległości
    static std::vector<std::vector<int>> generate_random_matrix(int size, int minValue, int maxValue);
};

#endif // TSPUTILITIES_H
