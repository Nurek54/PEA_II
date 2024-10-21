#ifndef SAVE_TO_CSV_H
#define SAVE_TO_CSV_H

#include <string>
#include <vector>
#include <chrono>

using namespace std;

class SaveToCSV {
public:
    SaveToCSV(const string& filename);
    void saveResults(const string& algorithmName,
                     const chrono::duration<double>& seconds,
                     const chrono::duration<double, std::milli>& milliseconds,
                     const chrono::duration<double, std::nano>& nanoseconds,
                     const vector<int>& path, int cost);
private:
    string filename;
    bool isFileNew;  // Flaga, która sprawdza, czy plik jest nowy (czy nagłówki zostały już zapisane)
};

#endif // SAVE_TO_CSV_H
