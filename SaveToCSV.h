#ifndef SAVE_TO_CSV_H
#define SAVE_TO_CSV_H

#include <string>
#include <vector>
#include <chrono>

class SaveToCSV {
public:
    SaveToCSV(const std::string& filename);
    void saveResults(const std::string& algorithmName,
                     const std::chrono::duration<double>& seconds,
                     const std::chrono::duration<double, std::milli>& milliseconds,
                     const std::chrono::duration<double, std::nano>& nanoseconds,
                     const std::vector<int>& path, int cost);
private:
    std::string filename;
    bool isFileNew;  // Flaga, która sprawdza, czy plik jest nowy (czy nagłówki zostały już zapisane)
};

#endif // SAVE_TO_CSV_H
