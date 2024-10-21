#ifndef TSPINSTANCE_H
#define TSPINSTANCE_H

#include <vector>
#include <string>

using namespace std;

class TSPInstance {
public:
    // Konstruktor przyjmujący nazwę pliku
    TSPInstance(const string& filename);

    // Nowy konstruktor przyjmujący macierz
    TSPInstance(const vector<vector<int>>& matrix);

    const vector<vector<int>>& getDistances() const;  // Zwraca macierz kosztów
    int getCityCount() const;  // Zwraca liczbę miast

private:
    vector<vector<int>> costMatrix;  // Macierz kosztów
    int cityCount;  // Liczba miast
    void loadFromFile(const string& filename);  // Wczytanie danych z pliku
};

#endif // TSPINSTANCE_H
