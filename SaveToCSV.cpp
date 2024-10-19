#include "SaveToCSV.h"
#include <fstream>
#include <iomanip>
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

void SaveToCSV::saveResults(const std::string& algorithmName,
                            const std::chrono::duration<double>& seconds,
                            const std::chrono::duration<double, std::milli>& milliseconds,
                            const std::chrono::duration<double, std::nano>& nanoseconds,
                            const std::vector<int>& path, int cost) {

    std::ofstream csvFile(filename, std::ios::app);  // Otwórz plik w trybie dodawania
    if (csvFile.is_open()) {
        // Zapisz nagłówki i nazwę algorytmu tylko raz (jeśli plik jest nowy)
        if (isFileNew) {
            csvFile << "Algorithm | Seconds | Milliseconds | Nanoseconds | Path | Cost\n";
            isFileNew = false;  // Ustaw flagę na false, aby nagłówki nie były już zapisywane
        }

        // Zapisujemy sekcje danych oddzielone " | "
        csvFile << std::fixed << std::setprecision(6)
                << algorithmName << " | "
                << seconds.count() << " | "
                << milliseconds.count() << " | "
                << nanoseconds.count() << " | ";

        // Zapisujemy miasta na trasie oddzielone przecinkami ","
        for (size_t i = 0; i < path.size(); ++i) {
            csvFile << path[i];
            if (i != path.size() - 1) {
                csvFile << ",";  // Oddziel miasta przecinkami
            }
        }

        // Na końcu zapisujemy koszt trasy
        csvFile << " | " << cost << "\n";
        csvFile.close();
        std::cout << "Wyniki zapisano do pliku: " << filename << "\n";
    } else {
        std::cerr << "Nie można otworzyć pliku: " << filename << "\n";
    }
}
