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
    ConfigReader config("C:\\Users\\g_sie\\OneDrive\\Pulpit\\PEA_II\\config.cfg");
    if (!config.parseConfig()) {
        std::cout << "Błąd podczas parsowania pliku konfiguracyjnego." << std::endl;
        return 1;
    }

    string algorithm = config.getAlgorithm();
    bool runSimulation = config.getRunSimulation();

    if (runSimulation) {
        // Uruchom symulację
        int numMatrices = config.getNumMatrices();
        int matrixSize = config.getMatrixSize();
        int maxCost = config.getMaxCost();

        TSPSimulation simulation(numMatrices, matrixSize, maxCost);
        simulation.runSimulation();
    } else {
        // Wczytaj macierz odległości
        string matrixFile = config.getDistanceMatrixFile();
        if (matrixFile.empty()) {
            std::cout << "Nie podano pliku z macierzą odległości w konfiguracji." << std::endl;
            return 1;
        }

        TSPInstance instance(matrixFile);

        if (algorithm == "BFS") {
            BranchAndBoundBFS solver;
            solver.solve(instance);
        } else if (algorithm == "DFS") {
            BranchAndBoundDFS solver;
            solver.solve(instance);
        } else if (algorithm == "BEST_FIRST") {
            BranchAndBoundBestFirst solver;
            solver.solve(instance);
        } else {
            std::cout << "Nieznany algorytm: " << algorithm << std::endl;
            return 1;
        }
    }

    return 0;
}
