#include "TSPInstance.h"
#include <fstream>
#include <stdexcept>

TSPInstance::TSPInstance(const string& filename) {
    loadFromFile(filename);
}

// Nowy konstruktor przyjmujący macierz
TSPInstance::TSPInstance(const vector<vector<int>>& matrix) {
    cityCount = matrix.size();
    costMatrix = matrix;
}

void TSPInstance::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("Unable to open file.");
    }

    file >> cityCount;
    costMatrix.resize(cityCount, vector<int>(cityCount));

    for (int i = 0; i < cityCount; ++i) {
        for (int j = 0; j < cityCount; ++j) {
            file >> costMatrix[i][j];
        }
    }
}

const vector<vector<int>>& TSPInstance::getDistances() const {
    return costMatrix;
}

int TSPInstance::getCityCount() const {
    return cityCount;
}
