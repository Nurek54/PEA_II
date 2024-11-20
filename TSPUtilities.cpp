#include "TSPUtilities.h"

int Utilities::calculate_cost(const int* path, int path_length, const int* const* distances, bool include_return) {
    int cost = 0;
    for (int i = 0; i < path_length - 1; ++i) {
        cost += distances[path[i]][path[i + 1]];
    }
    // Dodajemy koszt powrotu do miasta początkowego tylko, jeśli ostatnie miasto nie jest miastem początkowym i jeśli include_return jest true
    if (include_return && path[path_length - 1] != path[0]) {
        cost += distances[path[path_length - 1]][path[0]]; // Powrót do miasta początkowego
    }
    return cost;
}

bool Utilities::isCityInPath(const int* path, int path_length, int city) {
    for (int i = 0; i < path_length; ++i) {
        if (path[i] == city) {
            return true;
        }
    }
    return false;
}
