#include "TSPExperiment.h"
#include <iostream>

void TSPExperiment::runExperiment(TSPAlgorithm& algorithm, const TSPInstance& instance) {
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> tour = algorithm.solve(instance);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "Czas: " << duration.count() << " sekund\n";
    std::cout << "Trasa: ";
    for (int city : tour) {
        std::cout << city << " ";
    }
    std::cout << std::endl;
}
