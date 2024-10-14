#include <iostream>
#include "TSPInstance.h"
#include "BruteForceTSP.h"
#include "NearestNeighborTSP.h"
#include "RandomTSP.h"

int main() {
    try {
        // Wczytaj instancję problemu z pliku
        TSPInstance instance("../matrix_6x6.atsp");

        // Algorytm Brute Force
        std::cout << "Algorytm Brute Force:\n";
        auto result = tsp_bruteforce(instance);
        std::cout << "Najlepsza trasa: ";
        for (int city : result.first) {
            std::cout << city << " ";
        }
        std::cout << "\nKoszt: " << result.second << "\n\n";

        // Algorytm Najbliższych Sąsiadów
        std::cout << "Algorytm Najbliższych Sąsiadów:\n";
        result = tsp_nearest_neighbor(instance);
        std::cout << "Najlepsza trasa: ";
        for (int city : result.first) {
            std::cout << city << " ";
        }
        std::cout << "\nKoszt: " << result.second << "\n\n";

        // Losowy Algorytm
        std::cout << "Losowy Algorytm:\n";
        result = tsp_random(instance);
        std::cout << "Najlepsza trasa: ";
        for (int city : result.first) {
            std::cout << city << " ";
        }
        std::cout << "\nKoszt: " << result.second << "\n";

    } catch (const std::exception& ex) {
        std::cerr << "Wystąpił błąd: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
