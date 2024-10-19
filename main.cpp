#include <iostream>
#include <fstream>
#include "TSPInstance.h"
#include "BruteForceTSP.h"
#include "NearestNeighborTSP.h"
#include "RandomTSP.h"
#include "TSPUtilities.h"  // Do generowania macierzy
#include "TSPSimulation.h" // Nowa klasa symulacji

// Funkcja wyswietlajaca menu
void showMenu() {
    std::cout << "===========================\n";
    std::cout << "  Problem komiwojazera (TSP)\n";
    std::cout << "===========================\n";
    std::cout << "1. Uruchom Brute Force\n";
    std::cout << "2. Uruchom Nearest Neighbor\n";
    std::cout << "3. Uruchom Random Algorithm\n";
    std::cout << "4. Wygeneruj nowa losowa macierz odleglosci\n";
    std::cout << "5. Wczytaj dane z gotowego pliku\n";
    std::cout << "6. Symulacja na losowych macierzach\n";
    std::cout << "0. Wyjscie\n";
    std::cout << "Wybierz opcje: ";
}

// Funkcja pytajaca o nazwe pliku
std::string getFileNameFromUser(const std::string& prompt) {
    std::string filename;
    std::cout << prompt;
    std::cin >> filename;
    return filename;
}

// Funkcja do zapisywania macierzy do pliku
void saveMatrixToFile(const std::vector<std::vector<int>>& matrix, const std::string& filename) {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        int size = matrix.size();
        outFile << size << std::endl;
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                outFile << matrix[i][j] << " ";
            }
            outFile << std::endl;
        }
        outFile.close();
        std::cout << "Losowa macierz zapisana do pliku: " << filename << std::endl;
    } else {
        std::cerr << "Nie mozna zapisac macierzy do pliku!" << std::endl;
    }
}

int main() {
    int option = -1;
    std::string inputFilename;
    bool fileLoaded = false;

    while (true) {
        showMenu();
        std::cin >> option;

        if (option == 0) {
            std::cout << "Koniec programu.\n";
            break;  // Zakoncz program
        }

        switch (option) {
            case 1: {
                if (!fileLoaded) {
                    std::cout << "Najpierw zaladuj macierz odleglosci (opcja 4 lub 5).\n";
                    break;
                }
                // Uruchom Brute Force
                TSPInstance instance(inputFilename);
                tsp_bruteforce(instance);
                std::cout << std::endl;
                break;
            }
            case 2: {
                if (!fileLoaded) {
                    std::cout << "Najpierw zaladuj macierz odleglosci (opcja 4 lub 5).\n";
                    break;
                }
                // Uruchom Nearest Neighbor
                TSPInstance instance(inputFilename);
                tsp_nearest_neighbor(instance);
                std::cout << std::endl;
                break;
            }
            case 3: {
                if (!fileLoaded) {
                    std::cout << "Najpierw zaladuj macierz odleglosci (opcja 4 lub 5).\n";
                    break;
                }
                // Uruchom Random Algorithm
                TSPInstance instance(inputFilename);
                tsp_random(instance);
                std::cout << std::endl;
                break;
            }
            case 4: {
                // Generowanie nowej losowej macierzy
                int size, maxValue;
                std::cout << "Podaj rozmiar macierzy: ";
                std::cin >> size;
                std::cout << "Podaj maksymalna wartosc odleglosci: ";
                std::cin >> maxValue;

                std::vector<std::vector<int>> matrix = Utilities::generate_random_matrix(size, 1, maxValue);
                inputFilename = getFileNameFromUser("Podaj nazwe pliku do zapisania macierzy (np. matrix.atsp): ");
                saveMatrixToFile(matrix, inputFilename);
                fileLoaded = true;
                break;
            }
            case 5: {
                bool fileOpened = false;
                while (!fileOpened) {
                    inputFilename = getFileNameFromUser("Podaj nazwe pliku z macierza odleglosci (np. matrix.atsp): ");
                    std::ifstream file(inputFilename);
                    std::cout << "Probuje otworzyc plik: " << inputFilename << std::endl;

                    if (!file.is_open()) {
                        std::cerr << "Nie mozna otworzyc pliku: " << inputFilename << std::endl;
                        std::cout << "Czy chcesz sprobowac ponownie? (t/n): ";
                        char retry;
                        std::cin >> retry;
                        if (retry == 'n' || retry == 'N') {
                            std::cout << "Anulowano wczytywanie pliku.\n";
                            break;
                        }
                    } else {
                        std::cout << "Plik z macierza " << inputFilename << " wczytany.\n";
                        fileLoaded = true;
                        fileOpened = true;
                    }
                }
                break;
            }
            case 6: {
                int numMatrices, matrixSize, maxCost;
                std::cout << "Podaj liczbe macierzy do symulacji: ";
                std::cin >> numMatrices;
                std::cout << "Podaj rozmiar macierzy: ";
                std::cin >> matrixSize;
                std::cout << "Podaj maksymalna wartosc odleglosci: ";
                std::cin >> maxCost;

                // Tworzenie instancji klasy TSPSimulation i uruchomienie symulacji
                TSPSimulation simulation(numMatrices, matrixSize, maxCost);
                simulation.runSimulation();
                break;
            }
            default:
                std::cout << "Niepoprawna opcja. Sprobuj ponownie.\n";
        }
    }

    return 0;
}
