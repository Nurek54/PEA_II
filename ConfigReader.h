#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <string>
#include <map>
#include <vector>

class ConfigReader {
public:
    ConfigReader(const std::string& filename);
    bool parseConfig();

    std::vector<std::string> getAlgorithms() const;
    std::string getDistanceMatrixFile() const;
    bool getRunSimulation() const;
    int getNumMatrices() const;
    int getMatrixSize() const;
    int getMaxCost() const;

private:
    std::string filename;
    std::map<std::string, std::string> configData;

    std::string trim(const std::string& str) const; // Dodano 'const' na końcu
};

#endif // CONFIGREADER_H
