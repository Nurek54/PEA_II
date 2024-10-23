#ifndef SAVE_TO_CSV_H
#define SAVE_TO_CSV_H

#include <string>
#include <vector>
#include <chrono>

using namespace std;

class SaveToCSV {
public:
    SaveToCSV(const string& filename);

    // Funkcja zapisu wyników dla pojedynczej iteracji
    void saveResults(const string& algorithmName,
                     const chrono::duration<double>& seconds,
                     const chrono::duration<double, milli>& milliseconds,
                     const chrono::duration<double, nano>& nanoseconds,
                     const vector<int>& path, int cost);

    // Funkcja do aktualizowania sum wyników z każdej iteracji
    void updateTotals(const chrono::duration<double>& seconds,
                      const chrono::duration<double, milli>& milliseconds,
                      const chrono::duration<double, nano>& nanoseconds,
                      int cost);

private:
    string filename;
    bool isFileNew;

    // Zmienne do gromadzenia wyników z wielu iteracji
    double totalSeconds = 0.0;
    double totalMilliseconds = 0.0;
    double totalNanoseconds = 0.0;
    int totalCost = 0;
};

#endif  // SAVE_TO_CSV_H
