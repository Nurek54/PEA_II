#include <iostream>
#include "ConfigReader.h"
#include "TSPInstance.h"
#include "BranchAndBoundBFS.h"
#include "BranchAndBoundDFS.h"
#include "BranchAndBoundBestFirst.h"
#include "TSPSimulation.h"

using namespace std;

int main() {
    // Wczytaj konfigurację z pliku
    ConfigReader config("C:\\Users\\g_sie\\OneDrive\\Pulpit\\PEA_II\\config.txt");
    if (!config.parseConfig()) {
        std::cout << "Błąd podczas parsowania pliku konfiguracyjnego." << std::endl;
        return 1;
    }

    // Pobierz algorytmy
    int algorithmCount = 0;
    char** algorithms = config.getAlgorithms(algorithmCount);
    if (algorithms == nullptr || algorithmCount == 0) {
        std::cout << "Nie podano algorytmów w konfiguracji." << std::endl;
        return 1;
    }

    bool runSimulation = config.getRunSimulation();

    if (runSimulation) {
        // Uruchom symulację
        int numMatrices = config.getNumMatrices();
        int matrixSize = config.getMatrixSize();
        int maxCost = config.getMaxCost();

        TSPSimulation simulation(numMatrices, matrixSize, maxCost, algorithms, algorithmCount);
        simulation.runSimulation();
    } else {
        // Wczytaj macierz odległości
        string matrixFile = config.getDistanceMatrixFile();
        if (matrixFile.empty()) {
            std::cout << "Nie podano pliku z macierzą odległości w konfiguracji." << std::endl;
            // Zwolnij pamięć algorytmów przed zakończeniem
            for (int i = 0; i < algorithmCount; ++i) {
                delete[] algorithms[i];
            }
            delete[] algorithms;
            return 1;
        }

        TSPInstance instance(matrixFile);
        const int* const* distances = instance.getDistances();
        int numCities = instance.getCityCount();

        // Iterujemy po wybranych algorytmach
        for (int i = 0; i < algorithmCount; ++i) {
            std::string algorithm(algorithms[i]);

            if (algorithm == "BFS") {
                BranchAndBoundBFS solver(distances, numCities);
                auto result = solver.solve();
                // Wynik zapisany do CSV, nie drukujemy
            } else if (algorithm == "DFS") {
                BranchAndBoundDFS solver(distances, numCities);
                auto result = solver.solve();
                // Wynik zapisany do CSV, nie drukujemy
            } else if (algorithm == "BEST_FIRST") {
                BranchAndBoundBestFirst solver(distances, numCities);
                auto result = solver.solve(instance);
                // Wynik zapisany do CSV, nie drukujemy
            } else {
                std::cout << "Nieznany algorytm: " << algorithm << std::endl;
                // Możesz zdecydować, czy kontynuować, czy przerwać w tym miejscu
            }
        }
    }

    // Zwolnij pamięć alokowaną dla algorytmów
    for (int i = 0; i < algorithmCount; ++i) {
        delete[] algorithms[i];
    }
    delete[] algorithms;

    return 0;
}
