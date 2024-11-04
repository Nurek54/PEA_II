#ifndef SAVETOCSV_H
#define SAVETOCSV_H

#include <string>
#include <vector>
#include <chrono>

using namespace std;

class SaveToCSV {
public:
    SaveToCSV(const string& filename);

    void saveResults(const string& algorithmName,
                     const chrono::duration<double>& seconds,
                     const chrono::duration<double, milli>& milliseconds,
                     const chrono::duration<double, nano>& nanoseconds,
                     const vector<int>& path, int cost);

    void updateTotals(const chrono::duration<double>& seconds,
                      const chrono::duration<double, milli>& milliseconds,
                      const chrono::duration<double, nano>& nanoseconds,
                      int cost);

private:
    string filename;
    bool isFileNew;

    // Zmienne do przechowywania sum czasów i kosztów (jeśli są potrzebne)
    double totalSeconds = 0;
    double totalMilliseconds = 0;
    double totalNanoseconds = 0;
    int totalCost = 0;
};

#endif
