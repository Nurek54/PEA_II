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
    ConfigReader config("config.txt");
    if (!config.parseConfig()) {
        cout << "Błąd podczas parsowania pliku konfiguracyjnego." << endl;
        return 1;
    }

    // Pobierz algorytmy
    int algorithmCount = 0;
    char** algorithms = config.getAlgorithms(algorithmCount);
    if (algorithms == nullptr || algorithmCount == 0) {
        cout << "Nie podano algorytmów w konfiguracji." << endl;
        return 1;
    }

    bool runSimulation = config.getRunSimulation();
    string matrixType = config.getMatrixType(); // Pobierz typ macierzy (random/symmetric)

    if (runSimulation) {
        // Uruchom symulację
        int numMatrices = config.getNumMatrices();
        int matrixSize = config.getMatrixSize();
        int maxCost = config.getMaxCost();

        TSPSimulation simulation(numMatrices, matrixSize, maxCost, algorithms, algorithmCount, matrixType);
        simulation.runSimulation();
    } else {
        // Wczytaj macierz odległości
        string matrixFile = config.getDistanceMatrixFile();
        if (matrixFile.empty()) {
            cout << "Nie podano pliku z macierzą odległości w konfiguracji." << endl;
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
            string algorithm(algorithms[i]);

            if (algorithm == "BFS") {
                BranchAndBoundBFS solver(distances, numCities);
                auto result = solver.solve(matrixType);
                // Wynik zapisany do CSV, nie drukujemy
            } else if (algorithm == "DFS") {
                BranchAndBoundDFS solver(distances, numCities);
                auto result = solver.solve(matrixType);
                // Wynik zapisany do CSV, nie drukujemy
            } else if (algorithm == "BEST_FIRST") {
                BranchAndBoundBestFirst solver(distances, numCities);
                auto result = solver.solve(instance, matrixType);
                // Wynik zapisany do CSV, nie drukujemy
            } else {
                cout << "Nieznany algorytm: " << algorithm << endl;
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
