#include "SaveToCSV.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <iostream>

using namespace std;

SaveToCSV::SaveToCSV(const string& filename)
        : filename(filename), isFileNew(false) {
    ifstream fileCheck(filename);
    if (!fileCheck.good()) {
        isFileNew = true;
    }
    fileCheck.close();
}

string replaceDotWithComma(double value) {
    ostringstream ss;
    ss << fixed << setprecision(6) << value;
    string result = ss.str();
    for (size_t i = 0; i < result.length(); ++i) {
        if (result[i] == '.') {
            result[i] = ',';
        }
    }
    return result;
}

void SaveToCSV::saveResults(const string& algorithmName,
                            const string& matrixType,  // Dodane
                            const chrono::duration<double>& seconds,
                            const chrono::duration<double, milli>& milliseconds,
                            const chrono::duration<double, nano>& nanoseconds,
                            const int* path, int path_length, int cost) {

    ofstream csvFile(filename, ios::app);
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
        cout << "Nie można otworzyć pliku: " << filename << "\n";
    }
}
