#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <string>
#include <unordered_map>

using namespace std;

class ConfigReader {
public:
    ConfigReader(const string& filename);
    bool parseConfig();

    // Metody dostępu do poszczególnych parametrów
    string getAlgorithm() const;
    string getDistanceMatrixFile() const;
    bool getRunSimulation() const;
    int getNumMatrices() const;
    int getMatrixSize() const;
    int getMaxCost() const;
private:
    string filename;
    unordered_map<string, string> configData;

    // Funkcja pomocnicza do usuwania białych znaków
    string trim(const string& str);
};

#endif
