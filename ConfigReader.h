#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <string>

class ConfigReader {
public:
    ConfigReader(const std::string& filename);
    ~ConfigReader();
    bool parseConfig();
    char** getAlgorithms(int& count) const;
    std::string getDistanceMatrixFile() const;
    bool getRunSimulation() const;
    int getNumMatrices() const;
    int getMatrixSize() const;
    int getMaxCost() const;
    std::string getMatrixType() const;

private:
    std::string filename;

    struct ConfigEntry {
        char* key;
        char* value;
    };

    ConfigEntry* configEntries;
    int numEntries;
    int capacityEntries;

    std::string trim(const std::string& str) const;
    const char* getValue(const std::string& key) const;

    ConfigReader(const ConfigReader&) = delete;
    ConfigReader& operator=(const ConfigReader&) = delete;
};

#endif // CONFIGREADER_H
