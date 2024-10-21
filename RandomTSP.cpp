#include "RandomTSP.h"
#include "SaveToCSV.h"
#include "TSPUtilities.h"  // Do obliczania kosztu trasy
#include <cstdlib>
#include <chrono>
#include <iostream>
#include <ctime>  // Do ustawienia ziarna dla rand()

// Funkcja generująca losową permutację trasy
void generate_random_permutation(vector<int>& tour) {
    int n = tour.size();

    // Algorytm Fisher-Yates do losowej permutacji
    for (int i = n - 1; i > 0; --i) {
        int j = rand() % (i + 1);  // Losowa liczba od 0 do i
        swap(tour[i], tour[j]);
    }
}

// Funkcja implementująca algorytm Random TSP z dynamiczną liczbą iteracji
pair<vector<int>, int> tsp_random(const TSPInstance& instance) {
    vector<vector<int>> distances = instance.getDistances();
    int num_cities = instance.getCityCount();

    // Sprawdzenie, czy liczba miast jest wystarczająca do obliczenia (N-2)!
    if (num_cities < 3) {
        cerr << "Zbyt mała liczba miast, aby obliczyć (N-2)!\n";
        return {{}, -1};
    }

    // liczba iteracji: (N-2)!
    int iterations = Utilities::factorial(num_cities - 2);

    vector<int> best_tour;
    int min_cost = INT_MAX;

    // Próg akceptowalnego rozwiązania — jeśli znajdziemy trasę o takim koszcie, zakończymy wcześniej
    const int acceptable_cost = 100;

    // Mierzenie czasu działania algorytmu
    auto start = chrono::high_resolution_clock::now();

    // Wykonywanie wielu losowych tras i szukanie najlepszej
    for (int iter = 0; iter < iterations; ++iter) {
        vector<int> current_tour(num_cities);
        for (int i = 0; i < num_cities; ++i) {
            current_tour[i] = i;  // Inicjalizacja trasy miast
        }

        // Generowanie losowej permutacji
        generate_random_permutation(current_tour);

        // Obliczanie kosztu trasy
        int current_cost = Utilities::calculate_cost(current_tour, distances);

        // Sprawdzenie, czy aktualna trasa jest lepsza od dotychczasowej
        if (current_cost < min_cost) {
            min_cost = current_cost;
            best_tour = current_tour;
        }

        // Przerwanie, jeśli znaleziono akceptowalnie dobry wynik
        if (min_cost <= acceptable_cost) {
            //cout << "Znaleziono akceptowalny wynik. Wczesne zakończenie iteracji.\n";
            break;
        }
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> seconds = end - start;
    chrono::duration<double, milli> milliseconds = end - start;
    chrono::duration<double, nano> nanoseconds = end - start;

    // Zapisanie wyników do pliku CSV
    SaveToCSV save("RandomResults.csv");
    save.saveResults("Random", seconds, milliseconds, nanoseconds, best_tour, min_cost);

    return {best_tour, min_cost};
}

// Funkcja do ustawienia ziarna dla rand() - do wywołania raz w programie głównym
void initialize_random_seed() {
    srand(static_cast<unsigned>(time(nullptr)));  // Inicjalizacja ziarna na podstawie aktualnego czasu
}
