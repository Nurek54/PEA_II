#include "TSPSimulation.h"
#include "TSPInstance.h"
#include "BranchAndBoundBFS.h"
#include "BranchAndBoundDFS.h"
#include "BranchAndBoundBestFirst.h"
#include "TSPUtilities.h"
#include <cstdlib>    // Do rand() i srand()
#include <iostream>
#include <chrono>     // Do opóźnień i dokładnego czasu
#include <thread>     // Do sleep_for
#include <ctime>      // Do time()

// Funkcja mieszająca wartości rand() dla dodatkowej losowości
void mixRand() {
    for (int i = 0; i < 10; ++i) {
        rand();  // Mieszaj wartości rand()
    }
}

// Konstruktor ustawia parametry symulacji
TSPSimulation::TSPSimulation(int numMatrices, int matrixSize, int maxCost)
        : numMatrices(numMatrices), matrixSize(matrixSize), maxCost(maxCost) {
    // Nic nie zmieniamy w konstruktorze
}

// Funkcja generująca losową macierz odległości
vector<vector<int>> TSPSimulation::generateRandomMatrix() {
    vector<vector<int>> matrix(matrixSize, vector<int>(matrixSize));

    // Ziarno mieszające na podstawie czasu w nanosekundach i wartości rand()
    auto now = chrono::high_resolution_clock::now();
    auto duration = now.time_since_epoch();
    unsigned long long nanoseconds = chrono::duration_cast<chrono::nanoseconds>(duration).count();

    srand(static_cast<unsigned int>(nanoseconds + rand()));  // Ustawienie nowego ziarna dla rand()

    // Generowanie wartości losowych dla każdego elementu macierzy
    for (int i = 0; i < matrixSize; ++i) {
        for (int j = 0; j < matrixSize; ++j) {
            if (i == j) {
                // Wartości na przekątnej (koszt przejścia z miasta do siebie samego) są -1
                matrix[i][j] = -1;
            } else {
                // Losowanie wartości od 1 do maxCost
                matrix[i][j] = rand() % maxCost + 1;  // Gwarantuje wartości od 1 do maxCost
            }
        }
    }

    // Mieszanie wartości rand() dla większej losowości przed następną macierzą
    mixRand();

    return matrix;  // Zwracamy wygenerowaną macierz
}

// Funkcja uruchamiająca symulację
void TSPSimulation::runSimulation() {
    cout << "Postęp symulacji: ";  // Stała część tekstu
    for (int i = 0; i < numMatrices; ++i) {
        // Generowanie nowej macierzy dla każdej iteracji
        vector<vector<int>> matrix = generateRandomMatrix();
        TSPInstance instance(matrix);  // Przekazujemy macierz do obiektu TSPInstance

        // Uruchamianie wszystkich trzech algorytmów dla wygenerowanej macierzy
        BranchAndBoundBFS bfsSolver;
        bfsSolver.solve(instance);

        BranchAndBoundDFS dfsSolver;
        dfsSolver.solve(instance);

        BranchAndBoundBestFirst bestFirstSolver;
        bestFirstSolver.solve(instance);

        // Obliczanie procentu ukończenia symulacji
        int progress = (i + 1) * 100 / numMatrices;  // Obliczenie postępu w procentach

        // Przesunięcie kursora i nadpisywanie tylko wartości procentowej
        cout << "\rPostęp symulacji: " << progress << "%" << flush;

        // Krótkie opóźnienie między kolejnymi iteracjami symulacji
        this_thread::sleep_for(chrono::milliseconds(50)); // 50 ms opóźnienia
    }

    cout << "\nSymulacja zakończona.\n";
}
