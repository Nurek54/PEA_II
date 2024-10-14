#ifndef TSPINSTANCE_H
#define TSPINSTANCE_H

#include <vector>
#include <string>

class TSPInstance {
public:
    TSPInstance(const std::string& filename);  // Konstruktor wczytujący dane z pliku
    const std::vector<std::vector<int>>& getDistances() const;  // Zwraca macierz kosztów
    int getCityCount() const;                  // Zwraca liczbę miast

private:
    std::vector<std::vector<int>> costMatrix;  // Macierz kosztów
    int cityCount;                             // Liczba miast
    void loadFromFile(const std::string& filename); // Wczytanie danych z pliku
};

#endif // TSPINSTANCE_H
