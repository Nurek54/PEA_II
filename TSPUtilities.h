#ifndef TSPUTILITIES_H
#define TSPUTILITIES_H

class Utilities {
public:
    static int calculate_cost(const int* path, int path_length, const int* const* distances, bool include_return = true);
    static bool isCityInPath(const int* path, int path_length, int city);
};

#endif // TSPUTILITIES_H
