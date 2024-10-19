#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>

class Menu {
public:
    // Funkcja obsługująca logikę menu
    void run();

private:
    // Funkcje pomocnicze
    void showMenu();
    std::string getFileNameFromUser(const std::string& prompt);
    void saveMatrixToFile(const std::vector<std::vector<int>>& matrix, const std::string& filename);

    // Zmienna do przechowywania nazwy pliku z macierzą
    std::string inputFilename;
    bool fileLoaded = false;

    // Funkcje odpowiedzialne za poszczególne opcje
    void bruteForceOption();
    void nearestNeighborOption();
    void randomAlgorithmOption();
    void generateRandomMatrixOption();
    void loadMatrixFromFileOption();
    void runSimulationOption();
};

#endif // MENU_H
