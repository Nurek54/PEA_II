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

    std::vector<std::string> algorithms = config.getAlgorithms();
    bool runSimulation = config.getRunSimulation();

    if (runSimulation) {
        // Uruchom symulację
        int numMatrices = config.getNumMatrices();
        int matrixSize = config.getMatrixSize();
        int maxCost = config.getMaxCost();

        TSPSimulation simulation(numMatrices, matrixSize, maxCost, algorithms);
        simulation.runSimulation();
    } else {
        // Wczytaj macierz odległości
        string matrixFile = config.getDistanceMatrixFile();
        if (matrixFile.empty()) {
            std::cout << "Nie podano pliku z macierzą odległości w konfiguracji." << std::endl;
            return 1;
        }

        TSPInstance instance(matrixFile);
        const int* const* distances = instance.getDistances();
        int numCities = instance.getCityCount();

        // Konwersja const int* const* na const int** (usunięcie const z pośrednich wskaźników)
        auto mutableDistances = const_cast<const int**>(distances);

        // Iterujemy po wybranych algorytmach
        for (const auto& algorithm : algorithms) {
            std::cout << "Uruchamiam algorytm: " << algorithm << std::endl;

            if (algorithm == "BFS") {
                BranchAndBoundBFS solver(mutableDistances, numCities);
                auto result = solver.solve();
                std::cout << "Koszt: " << result.cost << ", Ścieżka: ";
                for (int i = 0; i < result.path_length; ++i) {
                    std::cout << result.path[i] << " ";
                }
                std::cout << std::endl;
            } else if (algorithm == "DFS") {
                BranchAndBoundDFS solver(mutableDistances, numCities);
                auto result = solver.solve();
                std::cout << "Koszt: " << result.cost << ", Ścieżka: ";
                for (int i = 0; i < result.path_length; ++i) {
                    std::cout << result.path[i] << " ";
                }
                std::cout << std::endl;
            } else if (algorithm == "BEST_FIRST") {
                BranchAndBoundBestFirst solver(mutableDistances, numCities);
                auto result = solver.solve(instance);
                std::cout << "Koszt: " << result.cost << ", Ścieżka: ";
                for (int i = 0; i < result.path_length; ++i) {
                    std::cout << result.path[i] << " ";
                }
                std::cout << std::endl;
            } else {
                std::cout << "Nieznany algorytm: " << algorithm << std::endl;
                // Możesz zdecydować, czy kontynuować, czy przerwać w tym miejscu
            }

            std::cout << "----------------------------------------" << std::endl;
        }
    }

    return 0;
}
