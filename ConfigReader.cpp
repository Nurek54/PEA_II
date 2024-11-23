#include "ConfigReader.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <cstring> // dla strcpy, strdup

// Konstruktor
ConfigReader::ConfigReader(const std::string& filename)
        : filename(filename), configEntries(nullptr), numEntries(0), capacityEntries(10) {
    // Inicjalizacja tablicy configEntries z początkową pojemnością
    configEntries = new ConfigEntry[capacityEntries];
}

// Destruktor
ConfigReader::~ConfigReader() {
    // Zwolnienie pamięci dla każdego wpisu
    for (int i = 0; i < numEntries; ++i) {
        delete[] configEntries[i].key;
        delete[] configEntries[i].value;
    }
    // Zwolnienie pamięci tablicy configEntries
    delete[] configEntries;
}

// Funkcja do usuwania białych znaków z początku i końca stringa
std::string ConfigReader::trim(const std::string& str) const {
    size_t start = 0;
    while (start < str.length() &&
           (str[start] == ' ' || str[start] == '\t' ||
            str[start] == '\n' || str[start] == '\r')) {
        start++;
    }

    size_t end = str.length();
    while (end > start &&
           (str[end - 1] == ' ' || str[end - 1] == '\t' ||
            str[end - 1] == '\n' || str[end - 1] == '\r')) {
        end--;
    }

    if (start >= end) {
        return "";
    } else {
        return str.substr(start, end - start);
    }
}

// Funkcja pomocnicza do pobierania wartości dla danego klucza
const char* ConfigReader::getValue(const std::string& key) const {
    for (int i = 0; i < numEntries; ++i) {
        if (key == configEntries[i].key) {
            return configEntries[i].value;
        }
    }
    return nullptr; // Klucz nie został znaleziony
}

// Funkcja parsująca plik konfiguracyjny
bool ConfigReader::parseConfig() {
    std::ifstream inFile(filename.c_str());
    if (!inFile.is_open()) {
        std::cout << "Nie można otworzyć pliku konfiguracyjnego: " << filename << std::endl;
        return false;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        // Usuwamy białe znaki
        line = trim(line);

        // Pomijamy puste linie i komentarze
        if (line.empty() || line[0] == '#') {
            continue;
        }

        // Szukamy znaku '='
        size_t delimiterPos = line.find('=');
        if (delimiterPos == std::string::npos) {
            std::cout << "Nieprawidłowy format linii w pliku konfiguracyjnym: " << line << std::endl;
            continue;
        }

        // Rozdzielamy klucz i wartość
        std::string key = trim(line.substr(0, delimiterPos));
        std::string value = trim(line.substr(delimiterPos + 1));

        // Alokujemy pamięć dla klucza i wartości
        char* key_cstr = new char[key.length() + 1];
        std::strcpy(key_cstr, key.c_str());

        char* value_cstr = new char[value.length() + 1];
        std::strcpy(value_cstr, value.c_str());

        // Dodajemy wpis do tablicy configEntries
        if (numEntries >= capacityEntries) {
            // Podwajamy pojemność tablicy
            int newCapacity = capacityEntries * 2;
            ConfigEntry* newEntries = new ConfigEntry[newCapacity];
            for (int i = 0; i < numEntries; ++i) {
                newEntries[i] = configEntries[i];
            }
            delete[] configEntries;
            configEntries = newEntries;
            capacityEntries = newCapacity;
        }

        configEntries[numEntries].key = key_cstr;
        configEntries[numEntries].value = value_cstr;
        numEntries++;
    }

    inFile.close();
    return true;
}

// Funkcja zwracająca algorytmy jako dynamicznie alokowaną tablicę C-stringów
char** ConfigReader::getAlgorithms(int& count) const {
    count = 0;
    const char* algorithmsStr = getValue("algorithms");
    if (algorithmsStr == nullptr) {
        // Próbujemy z kluczem 'algorithm' dla kompatybilności wstecznej
        algorithmsStr = getValue("algorithm");
        if (algorithmsStr == nullptr) {
            return nullptr; // Brak algorytmów w konfiguracji
        }
    }

    // Najpierw liczymy liczbę algorytmów poprzez liczenie przecinków
    int algoCount = 1; // Minimum jeden algorytm
    for (const char* p = algorithmsStr; *p != '\0'; ++p) {
        if (*p == ',') {
            algoCount++;
        }
    }

    // Alokujemy tablicę dla nazw algorytmów
    char** algorithms = new char*[algoCount];
    int currentAlgo = 0;

    std::string algoStr(algorithmsStr);
    std::istringstream ss(algoStr);
    std::string item;
    while (std::getline(ss, item, ',')) {
        item = trim(item);
        // Alokujemy pamięć dla każdego algorytmu
        algorithms[currentAlgo] = new char[item.length() + 1];
        std::strcpy(algorithms[currentAlgo], item.c_str());
        currentAlgo++;
    }

    count = algoCount;
    return algorithms;
}

// Funkcja zwracająca nazwę pliku z macierzą odległości
std::string ConfigReader::getDistanceMatrixFile() const {
    const char* value = getValue("distance_matrix_file");
    if (value != nullptr) {
        return std::string(value);
    } else {
        return "";
    }
}

// Funkcja zwracająca flagę czy uruchomić symulację
bool ConfigReader::getRunSimulation() const {
    const char* value = getValue("run_simulation");
    if (value != nullptr) {
        std::string valStr(value);
        if (valStr == "true" || valStr == "1") {
            return true;
        }
    }
    return false;
}

// Funkcja zwracająca liczbę macierzy do symulacji
int ConfigReader::getNumMatrices() const {
    const char* value = getValue("num_matrices");
    if (value != nullptr) {
        return std::atoi(value);
    } else {
        return 0;
    }
}

// Funkcja zwracająca rozmiar macierzy
int ConfigReader::getMatrixSize() const {
    const char* value = getValue("matrix_size");
    if (value != nullptr) {
        return std::atoi(value);
    } else {
        return 0;
    }
}

// Funkcja zwracająca maksymalny koszt
int ConfigReader::getMaxCost() const {
    const char* value = getValue("max_cost");
    if (value != nullptr) {
        return std::atoi(value);
    } else {
        return 0;
    }
}

std::string ConfigReader::getMatrixType() const {
    const char* value = getValue("matrix_type");
    if (value != nullptr) {
        return std::string(value);
    } else {
        return "random"; // Domyślny typ macierzy
    }
}

