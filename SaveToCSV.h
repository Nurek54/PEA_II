#ifndef SAVETOCSV_H
#define SAVETOCSV_H

#include <string>
#include <chrono>

class SaveToCSV {
public:
    SaveToCSV(const std::string& filename);

    void saveResults(const std::string& algorithmName,
                     const std::chrono::duration<double>& seconds,
                     const std::chrono::duration<double, std::milli>& milliseconds,
                     const std::chrono::duration<double, std::nano>& nanoseconds,
                     const int* path, int path_length, int cost);

private:
    std::string filename;
    bool isFileNew;
};

#endif // SAVETOCSV_H
