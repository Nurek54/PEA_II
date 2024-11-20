#include "SaveToCSV.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <iostream>

// Konstruktor klasy SaveToCSV
SaveToCSV::SaveToCSV(const std::string& filename)
        : filename(filename), isFileNew(false) {
    // Sprawdzenie, czy plik istnieje
    std::ifstream fileCheck(filename);
    if (!fileCheck.good()) {
        isFileNew = true;  // Plik nie istnieje, więc jest nowy
    }
    fileCheck.close();
}

// Własna funkcja do zamiany kropki na przecinek w stringu
std::string replaceDotWithComma(double value) {
    std::ostringstream ss;
    ss << std::fixed << std::setprecision(6) << value;
    std::string result = ss.str();
    // Zamieniamy kropki na przecinki
    for (size_t i = 0; i < result.length(); ++i) {
        if (result[i] == '.') {
            result[i] = ',';
        }
    }
    return result;
}

// Funkcja do zapisu wyników dla pojedynczej iteracji
void SaveToCSV::saveResults(const std::string& algorithmName,
                            const std::chrono::duration<double>& seconds,
                            const std::chrono::duration<double, std::milli>& milliseconds,
                            const std::chrono::duration<double, std::nano>& nanoseconds,
                            const int* path, int path_length, int cost) {

    std::ofstream csvFile(filename, std::ios::app);  // Otwórz plik w trybie dodawania
    if (csvFile.is_open()) {
        // Zapisz nagłówki i nazwę algorytmu tylko raz (jeśli plik jest nowy)
        if (isFileNew) {
            csvFile << "Algorithm | Seconds | Milliseconds | Nanoseconds | Path | Cost\n";
            isFileNew = false;  // Ustaw flagę na false, aby nagłówki nie były już zapisywane
        }

        // Zapisujemy dane z ręczną zamianą kropki na przecinek
        csvFile << algorithmName << " | "
                << replaceDotWithComma(seconds.count()) << " | "
                << replaceDotWithComma(milliseconds.count()) << " | "
                << replaceDotWithComma(nanoseconds.count()) << " | ";

        // Zapisujemy miasta na trasie oddzielone przecinkami
        for (int i = 0; i < path_length; ++i) {
            csvFile << path[i];
            if (i != path_length - 1) {
                csvFile << ",";  // Oddziela miasta przecinkami
            }
        }

        // Na końcu zapisujemy koszt trasy
        csvFile << " | " << cost << "\n";
        csvFile.close();
    } else {
        std::cerr << "Nie można otworzyć pliku: " << filename << "\n";
    }
}
