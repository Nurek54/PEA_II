#ifndef MENU_H
#define MENU_H

#include <string>
#include <vector>

using namespace std;

class Menu {
public:
    Menu() : fileLoaded(false), inputFilename("") {}

    void run();
    void showMenu();

private:
    bool fileLoaded;
    string inputFilename;

    // Funkcje pomocnicze
    string getFileNameFromUser(const string& prompt);
    void saveMatrixToFile(const vector<vector<int>>& matrix, const string& filename);

    // Opcje menu
    void branchAndBoundBFSOption();
    void branchAndBoundDFSOption();
    void branchAndBoundBestFirstOption();
    void generateRandomMatrixOption();
    void loadMatrixFromFileOption();
    void runSimulationOption();
};

#endif
