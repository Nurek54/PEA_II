#include "TSPSimulation.h"
#include "TSPInstance.h"
#include "BruteForceTSP.h"
#include "NearestNeighborTSP.h"
#include "RandomTSP.h"
#include "TSPUtilities.h"
#include <cstdlib>    // Do rand() i srand()
#include <iostream>
#include <chrono>     // Do opóźnień i dokładnego czasu
#include <thread>     // Do sleep_for
#include <ctime>      // Do time()

// Funkcja mieszająca wartości rand() dla dodatkowej losowości
// Aby zwiększyć losowość generowania liczb, kilkukrotnie wywołujemy rand()
// (w tym przypadku 10 razy) w pętli. Dzięki temu wartości generowane przez rand()
// są bardziej "wymieszane", co redukuje ryzyko powtarzalności przy szybkim wywoływaniu rand().
void mixRand() {
    for (int i = 0; i < 10; ++i) {
        rand();  // Mieszaj wartości rand()
    }
}

// Konstruktor ustawia parametry symulacji
// Konstruktor przyjmuje liczbę macierzy, rozmiar macierzy oraz maksymalny koszt
// jako parametry wejściowe i zapisuje je jako pola klasy.
TSPSimulation::TSPSimulation(int numMatrices, int matrixSize, int maxCost)
        : numMatrices(numMatrices), matrixSize(matrixSize), maxCost(maxCost) {
    // Nic nie zmieniamy w konstruktorze
}

// Funkcja generująca losową macierz odległości
// Funkcja generateRandomMatrix() generuje losową macierz odległości o wymiarach
// matrixSize x matrixSize, gdzie każdy element ma wartość z zakresu od -maxCost do maxCost.
vector<vector<int>> TSPSimulation::generateRandomMatrix() {
    vector<vector<int>> matrix(matrixSize, vector<int>(matrixSize));

    // Ziarno mieszające na podstawie czasu w nanosekundach i wartości rand()
    // Używamy czasu systemowego w nanosekundach do inicjalizacji generatora losowego (srand).
    // Aby dodatkowo zwiększyć losowość, dodajemy wynik wcześniejszego wywołania rand() do ziarna.
    auto now = chrono::high_resolution_clock::now();
    auto duration = now.time_since_epoch();
    unsigned long long nanoseconds = chrono::duration_cast<chrono::nanoseconds>(duration).count();

    srand(nanoseconds + rand());  // Ustawienie nowego ziarna dla rand()

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
    // Po wygenerowaniu macierzy, mieszamy wartości rand(), aby następne losowania
    // miały większą różnorodność i unikały powtarzalnych wzorców.
    mixRand();

    return matrix;  // Zwracamy wygenerowaną macierz
}

// Funkcja uruchamiająca symulację
// Funkcja runSimulation() uruchamia symulację dla określonej liczby macierzy.
// Dla każdej macierzy wywoływane są algorytmy: BruteForce, Nearest Neighbor i Random Algorithm.
void TSPSimulation::runSimulation() {
    for (int i = 0; i < numMatrices; ++i) {
        // Generowanie nowej macierzy dla każdej iteracji
        vector<vector<int>> matrix = generateRandomMatrix();
        TSPInstance instance(matrix);  // Przekazujemy macierz do obiektu TSPInstance

        // Uruchamianie wszystkich trzech algorytmów dla wygenerowanej macierzy
        tsp_bruteforce(instance);
        tsp_nearest_neighbor(instance);
        tsp_random(instance);

        // Krótkie opóźnienie między kolejnymi iteracjami symulacji
        // Używamy sleep_for z opóźnieniem 50 milisekund, aby zredukować ryzyko,
        // że generator losowy w kolejnych iteracjach zostanie zainicjalizowany w tej samej milisekundzie,
        // co zwiększa szansę na bardziej unikalne macierze przy każdym wywołaniu.
        this_thread::sleep_for(chrono::milliseconds(50)); // 50 ms opóźnienia
    }

    cout << "Symulacja zakonczona.\n";
}
