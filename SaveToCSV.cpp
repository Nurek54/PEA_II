#include "SaveToCSV.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <iostream>

SaveToCSV::SaveToCSV(const std::string& filename)
        : filename(filename), isFileNew(false) {
    std::ifstream fileCheck(filename);
    if (!fileCheck.good()) {
        isFileNew = true;
    }
    fileCheck.close();
}

std::string replaceDotWithComma(double value) {
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(6) << value;
    std::string result = ss.str();
    for (size_t i = 0; i < result.length(); ++i) {
        if (result[i] == '.') {
            result[i] = ',';
        }
    }
    return result;
}

void SaveToCSV::saveResults(const std::string& algorithmName,
                            const std::string& matrixType,  // Dodane
                            const std::chrono::duration<double>& seconds,
                            const std::chrono::duration<double, std::milli>& milliseconds,
                            const std::chrono::duration<double, std::nano>& nanoseconds,
                            const int* path, int path_length, int cost) {

    std::ofstream csvFile(filename, std::ios::app);
    if (csvFile.is_open()) {
        if (isFileNew) {
            csvFile << "Algorithm | MatrixType | Seconds | Milliseconds | Nanoseconds | Path | Cost\n";
            isFileNew = false;
        }

        csvFile << algorithmName << " | "
                << matrixType << " | "  // Dodane
                << replaceDotWithComma(seconds.count()) << " | "
                << replaceDotWithComma(milliseconds.count()) << " | "
                << replaceDotWithComma(nanoseconds.count()) << " | ";

        for (int i = 0; i < path_length; ++i) {
            csvFile << path[i];
            if (i != path_length - 1) {
                csvFile << ",";
            }
        }

        csvFile << " | " << cost << "\n";
        csvFile.close();
    } else {
        std::cerr << "Nie można otworzyć pliku: " << filename << "\n";
    }
}
