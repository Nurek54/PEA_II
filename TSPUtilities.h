#ifndef TSPUTILITIES_H
#define TSPUTILITIES_H

#include <vector>

using namespace std;

class Utilities {
public:
    // Funkcja do obliczania kosztu trasy
    static int calculate_cost(const vector<int>& path, const vector<vector<int>>& distances);

    // Funkcja do generowania losowej macierzy odległości
    static vector<vector<int>> generate_random_matrix(int size, int minValue, int maxValue);
};

#endif // TSPUTILITIES_H
