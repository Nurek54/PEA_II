#ifndef TSPUTILITIES_H
#define TSPUTILITIES_H

#include <vector>

using namespace std;

class Utilities {
public:
    static int calculate_cost(const vector<int>& path, const vector<vector<int>>& distances);
    static vector<vector<int>> generate_random_matrix(int size, int minValue, int maxValue);
    static int factorial(int n);

    static bool isCityInPath(const vector<int>& path, int city);
};

#endif
