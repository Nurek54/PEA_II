#include <iostream>
#include "TSPInstance.h"
#include "BruteForceTSP.h"
#include "NearestNeighborTSP.h"
#include "RandomTSP.h"

int main() {
    try {
        // Wczytaj instancję problemu z pliku
        TSPInstance instance("../matrix_8x8.atsp");  // Podaj właściwą ścieżkę do pliku z danymi

        // Algorytm Brute Force
        //std::cout << "Algorytm Brute Force:\n";
        auto result = tsp_bruteforce(instance);

        // Algorytm Najbliższych Sąsiadów
        //std::cout << "\nAlgorytm Najbliższych Sąsiadów:\n";
        std::cout<<std::endl;

        result = tsp_nearest_neighbor(instance);

        // Losowy Algorytm
        //std::cout << "\nLosowy Algorytm:\n";
        std::cout<<std::endl;

        result = tsp_random(instance);

    } catch (const std::exception& ex) {
        std::cerr << "Wystąpił błąd: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
