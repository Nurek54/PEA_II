#include "TSPInstance.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

TSPInstance::TSPInstance(const std::string& filename) {
    loadFromFile(filename);
}

void TSPInstance::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Unable to open file.");
    }

    file >> cityCount;
    costMatrix.resize(cityCount, std::vector<int>(cityCount));

    for (int i = 0; i < cityCount; ++i) {
        for (int j = 0; j < cityCount; ++j) {
            file >> costMatrix[i][j];
        }
    }
}

int TSPInstance::getCost(int i, int j) const {
    return costMatrix[i][j];
}

int TSPInstance::getCityCount() const {
    return cityCount;
}
