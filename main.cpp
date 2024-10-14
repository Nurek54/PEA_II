#include <iostream>
#include "TSPInstance.h"
#include "BruteForceTSP.h"
#include "NearestNeighborTSP.h"
#include "RandomTSP.h"
#include "TSPExperiment.h"

int main() {
    try {
        // Wczytaj instancję problemu z pliku
        TSPInstance instance("../matrix_6x6.atsp");

        // Utwórz obiekty algorytmów
        BruteForceTSP bruteForce;
        NearestNeighborTSP nearestNeighbor;
        RandomTSP randomAlg;

        // Utwórz obiekt do eksperymentów
        TSPExperiment experiment;

        std::cout << "Algorytm Brute Force:\n";
        experiment.runExperiment(bruteForce, instance);

        std::cout << "\nAlgorytm Najbliższych Sąsiadów:\n";
        experiment.runExperiment(nearestNeighbor, instance);

        std::cout << "\nLosowy Algorytm:\n";
        experiment.runExperiment(randomAlg, instance);

    } catch (const std::exception& ex) {
        std::cerr << "Wystąpił błąd: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}
