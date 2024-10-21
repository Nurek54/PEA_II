#include "Menu.h"
#include "TSPInstance.h"
#include "BruteForceTSP.h"
#include "NearestNeighborTSP.h"
#include "RandomTSP.h"
#include "TSPUtilities.h"
#include "TSPSimulation.h"
#include <iostream>
#include <fstream>

// Funkcja obsługująca całe menu
void Menu::run() {
    int option = -1;

    while (true) {
        showMenu();
        cin >> option;

        if (option == 0) {
            cout << "Koniec programu.\n";
            break;  // Zakoncz program
        }

        switch (option) {
            case 1:
                bruteForceOption();
                break;
            case 2:
                nearestNeighborOption();
                break;
            case 3:
                randomAlgorithmOption();
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
                cout << "Niepoprawna opcja. Sprobuj ponownie.\n";
        }
    }
}

// Funkcja wyswietlajaca menu
void Menu::showMenu() {
    cout << "===========================\n";
    cout << "  Problem komiwojazera (TSP)\n";
    cout << "===========================\n";
    cout << "1. Uruchom Brute Force\n";
    cout << "2. Uruchom Nearest Neighbor\n";
    cout << "3. Uruchom Random Algorithm\n";
    cout << "4. Wygeneruj nowa losowa macierz odleglosci\n";
    cout << "5. Wczytaj dane z gotowego pliku\n";
    cout << "6. Symulacja na losowych macierzach\n";
    cout << "0. Wyjscie\n";
    cout << "Wybierz opcje: ";
}

// Funkcja pytajaca o nazwe pliku
string Menu::getFileNameFromUser(const string& prompt) {
    string filename;
    cout << prompt;
    cin >> filename;
    return filename;
}

// Funkcja do zapisywania macierzy do pliku
void Menu::saveMatrixToFile(const vector<vector<int>>& matrix, const string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        int size = matrix.size();
        outFile << size << endl;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                outFile << matrix[i][j] << " ";
            }
            outFile << endl;
        }
        outFile.close();
        cout << "Losowa macierz zapisana do pliku: " << filename << endl;
    } else {
        cerr << "Nie mozna zapisac macierzy do pliku!" << endl;
    }
}

// Opcje menu
void Menu::bruteForceOption() {
    if (!fileLoaded) {
        cout << "Najpierw zaladuj macierz odleglosci (opcja 4 lub 5).\n";
        return;
    }
    TSPInstance instance(inputFilename);
    tsp_bruteforce(instance);
    cout << endl;
}

void Menu::nearestNeighborOption() {
    if (!fileLoaded) {
        cout << "Najpierw zaladuj macierz odleglosci (opcja 4 lub 5).\n";
        return;
    }
    TSPInstance instance(inputFilename);
    tsp_nearest_neighbor(instance);
    cout << endl;
}

void Menu::randomAlgorithmOption() {
    if (!fileLoaded) {
        cout << "Najpierw zaladuj macierz odleglosci (opcja 4 lub 5).\n";
        return;
    }
    TSPInstance instance(inputFilename);
    tsp_random(instance);
    cout << endl;
}

void Menu::generateRandomMatrixOption() {
    int size, maxValue;
    cout << "Podaj rozmiar macierzy: ";
    cin >> size;
    cout << "Podaj maksymalna wartosc odleglosci: ";
    cin >> maxValue;

    vector<vector<int>> matrix = Utilities::generate_random_matrix(size, 1, maxValue);
    inputFilename = getFileNameFromUser("Podaj nazwe pliku do zapisania macierzy (np. matrix.atsp): ");
    saveMatrixToFile(matrix, inputFilename);
    fileLoaded = true;
}

void Menu::loadMatrixFromFileOption() {
    bool fileOpened = false;
    while (!fileOpened) {
        inputFilename = getFileNameFromUser("Podaj nazwe pliku z macierza odleglosci (np. matrix.atsp): ");
        ifstream file(inputFilename);
        cout << "Probuje otworzyc plik: " << inputFilename << endl;

        if (!file.is_open()) {
            cerr << "Nie mozna otworzyc pliku: " << inputFilename << endl;
            cout << "Czy chcesz sprobowac ponownie? (t/n): ";
            char retry;
            cin >> retry;
            if (retry == 'n' || retry == 'N') {
                cout << "Anulowano wczytywanie pliku.\n";
                return;
            }
        } else {
            cout << "Plik z macierza " << inputFilename << " wczytany.\n";
            fileLoaded = true;
            fileOpened = true;
        }
    }
}

void Menu::runSimulationOption() {
    int numMatrices, matrixSize, maxCost;
    cout << "Podaj liczbe macierzy do symulacji: ";
    cin >> numMatrices;
    cout << "Podaj rozmiar macierzy: ";
    cin >> matrixSize;
    cout << "Podaj maksymalna wartosc odleglosci: ";
    cin >> maxCost;

    cout << endl;

    TSPSimulation simulation(numMatrices, matrixSize, maxCost);
    simulation.runSimulation();
}

