#ifndef CONFIGREADER_H
#define CONFIGREADER_H

#include <string>

class ConfigReader {
public:
    // Konstruktor przyjmujący nazwę pliku konfiguracyjnego
    ConfigReader(const std::string& filename);

    // Destruktor
    ~ConfigReader();

    // Funkcja parsująca plik konfiguracyjny
    bool parseConfig();

    // Funkcje dostępowe
    // Zwraca dynamicznie alokowaną tablicę nazw algorytmów oraz ich liczbę
    char** getAlgorithms(int& count) const;

    // Zwraca nazwę pliku z macierzą odległości
    std::string getDistanceMatrixFile() const;

    // Zwraca flagę czy uruchomić symulację
    bool getRunSimulation() const;

    // Zwraca liczbę macierzy do symulacji
    int getNumMatrices() const;

    // Zwraca rozmiar macierzy
    int getMatrixSize() const;

    // Zwraca maksymalny koszt
    int getMaxCost() const;

private:
    std::string filename;

    // Struktura przechowująca parę klucz-wartość
    struct ConfigEntry {
        char* key;
        char* value;
    };

    ConfigEntry* configEntries; // Dynamicznie alokowana tablica par klucz-wartość
    int numEntries;              // Aktualna liczba wpisów
    int capacityEntries;         // Pojemność tablicy configEntries

    // Funkcje pomocnicze
    std::string trim(const std::string& str) const;
    const char* getValue(const std::string& key) const;

    // Wyłączamy konstruktor kopiujący i operator przypisania
    ConfigReader(const ConfigReader&) = delete;
    ConfigReader& operator=(const ConfigReader&) = delete;
};

#endif // CONFIGREADER_H
