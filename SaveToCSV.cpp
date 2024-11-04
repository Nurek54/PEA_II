#include "SaveToCSV.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

// Konstruktor klasy SaveToCSV
SaveToCSV::SaveToCSV(const string& filename)
        : filename(filename), isFileNew(false) {
    // Sprawdzenie, czy plik istnieje
    ifstream fileCheck(filename);
    if (!fileCheck.good()) {
        isFileNew = true;  // Plik nie istnieje, więc jest nowy
    }
    fileCheck.close();
}

// Własna funkcja do zamiany kropki na przecinek w stringu
string replaceDotWithComma(double value) {
    ostringstream ss;
    ss << fixed << std::setprecision(6) << value;
    string result = ss.str();
    // Zamieniamy kropki na przecinki bez użycia std::replace
    for (size_t i = 0; i < result.length(); ++i) {
        if (result[i] == '.') {
            result[i] = ',';
        }
    }
    return result;
}

// Funkcja do zapisu wyników dla pojedynczej iteracji
void SaveToCSV::saveResults(const string& algorithmName,
                            const chrono::duration<double>& seconds,
                            const chrono::duration<double, milli>& milliseconds,
                            const chrono::duration<double, nano>& nanoseconds,
                            const vector<int>& path, int cost) {

    ofstream csvFile(filename, ios::app);  // Otwórz plik w trybie dodawania
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

        // Zapisujemy miasta na trasie oddzielone przecinkami ","
        for (size_t i = 0; i < path.size(); ++i) {
            csvFile << path[i];
            if (i != path.size() - 1) {
                csvFile << ",";  // Oddziela miasta przecinkami
            }
        }

        // Na końcu zapisujemy koszt trasy
        csvFile << " | " << cost << "\n";
        csvFile.close();
    } else {
        cerr << "Nie można otworzyć pliku: " << filename << "\n";
    }
}

// Funkcja do aktualizowania sum wyników z każdej iteracji (jeśli jest używana)
void SaveToCSV::updateTotals(const chrono::duration<double>& seconds,
                             const chrono::duration<double, milli>& milliseconds,
                             const chrono::duration<double, nano>& nanoseconds,
                             int cost) {
    totalSeconds += seconds.count();
    totalMilliseconds += milliseconds.count();
    totalNanoseconds += nanoseconds.count();
    totalCost += cost;
}
