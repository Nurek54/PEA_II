#include "TSPInstance.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

TSPInstance::TSPInstance(const std::string& filename) {
    loadFromFile(filename);
}

TSPInstance::TSPInstance(int** matrix, int size) {
    cityCount = size;
    costMatrix = new int*[cityCount];
    for (int i = 0; i < cityCount; ++i) {
        costMatrix[i] = new int[cityCount];
        for (int j = 0; j < cityCount; ++j) {
            costMatrix[i][j] = matrix[i][j];
        }
    }
}

TSPInstance::~TSPInstance() {
    for (int i = 0; i < cityCount; ++i) {
        delete[] costMatrix[i];
    }
    delete[] costMatrix;
}

void TSPInstance::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Nie można otworzyc pliku: " + filename);
    }

    file >> cityCount;
    if (file.fail()) {
        throw std::runtime_error("Blad podczas odczytu liczby miast.");
    }
    std::cout << "Liczba miast w pliku: " << cityCount << std::endl;

    costMatrix = new int*[cityCount];
    for (int i = 0; i < cityCount; ++i) {
        costMatrix[i] = new int[cityCount];
    }

    for (int i = 0; i < cityCount; ++i) {
        for (int j = 0; j < cityCount; ++j) {
            file >> costMatrix[i][j];
            if (file.fail()) {
                throw std::runtime_error("Blad podczas odczytu macierzy kosztow.");
            }
        }
    }

    // Opcjonalnie wyświetl macierz
    std::cout << "Macierz kosztow:" << std::endl;
    for (int i = 0; i < cityCount; ++i) {
        for (int j = 0; j < cityCount; ++j) {
            std::cout << costMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

const int* const* TSPInstance::getDistances() const {
    return costMatrix;
}

int TSPInstance::getCityCount() const {
    return cityCount;
}
