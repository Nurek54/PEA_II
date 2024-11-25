#ifndef SAVETOCSV_H
#define SAVETOCSV_H

#include <string>
#include <chrono>

using namespace std;

class SaveToCSV {
public:
    SaveToCSV(const string& filename);

    void saveResults(const string& algorithmName,
                     const string& matrixType,  // Dodane
                     const chrono::duration<double>& seconds,
                     const chrono::duration<double, milli>& milliseconds,
                     const chrono::duration<double, nano>& nanoseconds,
                     const int* path, int path_length, int cost);

private:
    string filename;
    bool isFileNew;
};

#endif // SAVETOCSV_H
