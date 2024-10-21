#include "RandomTSP.h"
#include "SaveToCSV.h"
#include "TSPUtilities.h"  // Do obliczania kosztu trasy
#include <cstdlib>
#include <chrono>
#include <iostream>
#include <ctime>  // Do ustawienia ziarna dla rand()

// Funkcja generująca losową permutację trasy
void generate_random_permutation(std::vector<int>& tour) {
    int n = tour.size();

    // Algorytm Fisher-Yates do losowej permutacji
    for (int i = n - 1; i > 0; --i) {
        int j = rand() % (i + 1);  // Losowa liczba od 0 do i
        std::swap(tour[i], tour[j]);
    }
}

// Funkcja implementująca algorytm Random TSP z dynamiczną liczbą iteracji
std::pair<std::vector<int>, int> tsp_random(const TSPInstance& instance) {
    std::vector<std::vector<int>> distances = instance.getDistances();
    int num_cities = instance.getCityCount();

    // Dynamiczna liczba iteracji: im więcej miast, tym więcej prób
    int iterations = num_cities * num_cities * 10;

    std::vector<int> best_tour;
    int min_cost = INT_MAX;

    // Próg akceptowalnego rozwiązania — jeśli znajdziemy trasę o takim koszcie, zakończymy wcześniej
    const int acceptable_cost = 100;  // Można ustawić jako dynamiczny, zależny od problemu

    // Mierzenie czasu działania algorytmu
    auto start = std::chrono::high_resolution_clock::now();

    // Wykonywanie wielu losowych tras i szukanie najlepszej
    for (int iter = 0; iter < iterations; ++iter) {
        std::vector<int> current_tour(num_cities);
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
            std::cout << "Znaleziono akceptowalny wynik. Wczesne zakończenie iteracji.\n";
            break;
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> seconds = end - start;
    std::chrono::duration<double, std::milli> milliseconds = end - start;
    std::chrono::duration<double, std::nano> nanoseconds = end - start;

    // Zapisanie wyników do pliku CSV
    SaveToCSV save("RandomResults.csv");
    save.saveResults("Random", seconds, milliseconds, nanoseconds, best_tour, min_cost);

    return {best_tour, min_cost};
}

// Funkcja do ustawienia ziarna dla rand() - do wywołania raz w programie głównym
void initialize_random_seed() {
    srand(static_cast<unsigned>(time(nullptr)));  // Inicjalizacja ziarna na podstawie aktualnego czasu
}
