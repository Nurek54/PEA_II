#include "ConfigReader.h"
#include <fstream>
#include <iostream>
#include <sstream>

ConfigReader::ConfigReader(const std::string& filename) {
    this->filename = filename;
}

bool ConfigReader::parseConfig() {
    std::ifstream inFile(filename.c_str());
    if (!inFile.is_open()) {
        std::cout << "Nie można otworzyć pliku konfiguracyjnego: " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        // Usuwamy białe znaki z początku i końca linii
        line = trim(line);

        // Sprawdzamy, czy linia nie jest pusta i nie jest komentarzem
        if (line.length() == 0 || line[0] == '#') {
            continue;
        }

        // Szukamy pozycji znaku '='
        size_t delimiterPos = line.find('=');

        if (delimiterPos == std::string::npos) {
            std::cout << "Nieprawidłowy format linii w pliku konfiguracyjnym: " << line << std::endl;
            continue;
        }

        // Pobieramy klucz i wartość
        std::string key = line.substr(0, delimiterPos);
        std::string value = line.substr(delimiterPos + 1);

        // Usuwamy białe znaki z klucza i wartości
        key = trim(key);
        value = trim(value);

        // Dodajemy klucz i wartość do mapy
        configData[key] = value;
    }

    inFile.close();
    return true;
}

std::vector<std::string> ConfigReader::getAlgorithms() const {
    std::vector<std::string> algorithms;
    if (configData.count("algorithms") > 0) {
        std::string value = configData.find("algorithms")->second;
        // Rozdzielamy wartość po przecinku
        std::istringstream ss(value);
        std::string item;
        while (std::getline(ss, item, ',')) {
            item = trim(item); // 'trim' musi być const
            algorithms.push_back(item);
        }
    } else if (configData.count("algorithm") > 0) {
        // Dla kompatybilności wstecznej, jeśli używany jest klucz 'algorithm'
        algorithms.push_back(configData.find("algorithm")->second);
    }
    return algorithms;
}

std::string ConfigReader::getDistanceMatrixFile() const {
    if (configData.count("distance_matrix_file") > 0) {
        return configData.find("distance_matrix_file")->second;
    } else {
        return "";
    }
}

bool ConfigReader::getRunSimulation() const {
    if (configData.count("run_simulation") > 0) {
        std::string value = configData.find("run_simulation")->second;
        if (value == "true" || value == "1") {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}

int ConfigReader::getNumMatrices() const {
    if (configData.count("num_matrices") > 0) {
        return atoi(configData.find("num_matrices")->second.c_str());
    } else {
        return 0;
    }
}

int ConfigReader::getMatrixSize() const {
    if (configData.count("matrix_size") > 0) {
        return atoi(configData.find("matrix_size")->second.c_str());
    } else {
        return 0;
    }
}

int ConfigReader::getMaxCost() const {
    if (configData.count("max_cost") > 0) {
        return atoi(configData.find("max_cost")->second.c_str());
    } else {
        return 0;
    }
}

std::string ConfigReader::trim(const std::string& str) const {
    size_t start = 0;
    while (start < str.length() && (str[start] == ' ' || str[start] == '\t' || str[start] == '\n' || str[start] == '\r')) {
        start++;
    }

    size_t end = str.length();
    while (end > start && (str[end - 1] == ' ' || str[end - 1] == '\t' || str[end - 1] == '\n' || str[end - 1] == '\r')) {
        end--;
    }

    if (start >= end) {
        return "";
    } else {
        return str.substr(start, end - start);
    }
}
