#include "Menu.h"
#include "TSPInstance.h"
#include "BranchAndBoundBFS.h"
#include "BranchAndBoundDFS.h"
#include "BranchAndBoundBestFirst.h"
#include "TSPUtilities.h"
#include "TSPSimulation.h"
#include <iostream>
#include <fstream>

using namespace std;

// Funkcja obsługująca całe menu
void Menu::run() {
    int option = -1;

    while (true) {
        showMenu();
        cin >> option;

        if (option == 0) {
            cout << "Koniec programu.\n";
            break;  // Zakończ program
        }

        switch (option) {
            case 1:
                branchAndBoundBFSOption();
                break;
            case 2:
                branchAndBoundDFSOption();
                break;
            case 3:
                branchAndBoundBestFirstOption();
                break;
            case 4:
                generateRandomMatrixOption();
                break;
            case 5:
                loadMatrixFromFileOption();
                break;
            case 6:
                runSimulationOption();
                break;
            default:
                cout << "Niepoprawna opcja. Spróbuj ponownie.\n";
        }
    }
}

// Funkcja wyświetlająca menu
void Menu::showMenu() {
    cout << "===========================\n";
    cout << "  Problem komiwojażera (TSP)\n";
    cout << "===========================\n";
    cout << "1. Branch and Bound - Przeszukiwanie wszerz (BFS)\n";
    cout << "2. Branch and Bound - Przeszukiwanie wgłąb (DFS)\n";
    cout << "3. Branch and Bound - Przeszukiwanie pod kątem najniższego kosztu (Best-First Search)\n";
    cout << "4. Wygeneruj nową losową macierz odległości\n";
    cout << "5. Wczytaj dane z gotowego pliku\n";
    cout << "6. Symulacja na losowych macierzach\n";
    cout << "0. Wyjście\n";
    cout << "Wybierz opcję: ";
}

// Funkcja pobierająca nazwę pliku od użytkownika
string Menu::getFileNameFromUser(const string& prompt) {
    string filename;
    cout << prompt;
    cin >> filename;
    return filename;
}

// Funkcja do zapisywania macierzy do pliku
void Menu::saveMatrixToFile(const vector<vector<int>>& matrix, const string& filename) {
    string astpFilename = filename + ".atsp";

    ofstream outFile(astpFilename);
    if (outFile.is_open()) {
        int size = matrix.size();
        outFile << size << endl;  // Zapisujemy rozmiar macierzy
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                outFile << matrix[i][j] << " ";  // Zapisujemy wartości wiersz po wierszu
            }
            outFile << endl;
        }
        outFile.close();
        cout << "Macierz zapisana do pliku: " << astpFilename << endl;
    } else {
        cerr << "Nie można zapisać macierzy do pliku!" << endl;
    }
}

// Opcje menu
void Menu::branchAndBoundBFSOption() {
    if (!fileLoaded) {
        cout << "Najpierw załaduj macierz odległości (opcja 4 lub 5).\n";
        return;
    }
    TSPInstance instance(inputFilename);
    BranchAndBoundBFS solver;
    solver.solve(instance);
    cout << endl;
}

void Menu::branchAndBoundDFSOption() {
    if (!fileLoaded) {
        cout << "Najpierw załaduj macierz odległości (opcja 4 lub 5).\n";
        return;
    }
    TSPInstance instance(inputFilename);
    BranchAndBoundDFS solver;
    solver.solve(instance);
    cout << endl;
}

void Menu::branchAndBoundBestFirstOption() {
    if (!fileLoaded) {
        cout << "Najpierw załaduj macierz odległości (opcja 4 lub 5).\n";
        return;
    }
    TSPInstance instance(inputFilename);
    BranchAndBoundBestFirst solver;
    solver.solve(instance);
    cout << endl;
}

void Menu::generateRandomMatrixOption() {
    int size, maxValue;
    cout << "Podaj rozmiar macierzy: ";
    cin >> size;
    cout << "Podaj maksymalną wartość odległości: ";
    cin >> maxValue;

    vector<vector<int>> matrix = Utilities::generate_random_matrix(size, 1, maxValue);
    inputFilename = getFileNameFromUser("Podaj nazwę pliku do zapisania macierzy (bez rozszerzenia): ");
    saveMatrixToFile(matrix, inputFilename);
    fileLoaded = true;
}

void Menu::loadMatrixFromFileOption() {
    bool fileOpened = false;
    while (!fileOpened) {
        inputFilename = getFileNameFromUser("Podaj nazwę pliku z macierzą odległości (np. matrix.atsp): ");
        ifstream file(inputFilename);
        cout << "Próbuję otworzyć plik: " << inputFilename << endl;

        if (!file.is_open()) {
            cerr << "Nie można otworzyć pliku: " << inputFilename << endl;
            cout << "Czy chcesz spróbować ponownie? (t/n): ";
            char retry;
            cin >> retry;
            if (retry == 'n' || retry == 'N') {
                cout << "Anulowano wczytywanie pliku.\n";
                return;
            }
        } else {
            cout << "Plik z macierzą " << inputFilename << " wczytany.\n";
            fileLoaded = true;
            fileOpened = true;
        }
    }
}

void Menu::runSimulationOption() {
    int numMatrices, matrixSize, maxCost;
    cout << "Podaj liczbę macierzy do symulacji: ";
    cin >> numMatrices;
    cout << "Podaj rozmiar macierzy: ";
    cin >> matrixSize;
    cout << "Podaj maksymalną wartość odległości: ";
    cin >> maxCost;

    cout << endl;

    TSPSimulation simulation(numMatrices, matrixSize, maxCost);
    simulation.runSimulation();
}
