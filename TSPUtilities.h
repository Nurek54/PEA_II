#ifndef TSPUTILITIES_H
#define TSPUTILITIES_H

#include <vector>

using namespace std;

class Utilities {
public:
    static int calculate_cost(const vector<int>& path, const vector<vector<int>>& distances);
    static vector<vector<int>> generate_random_matrix(int size, int minValue, int maxValue);

    // Dodajemy deklarację metody do obliczania silni
    static int factorial(int n);
};

#endif // TSPUTILITIES_H
