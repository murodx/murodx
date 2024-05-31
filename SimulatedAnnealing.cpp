#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <random>

using namespace std;

// Функция для вычисления расстояния между двумя городами
double distance(pair<int, int> city1, pair<int, int> city2) {
    return sqrt(pow(city1.first - city2.first, 2) + pow(city1.second - city2.second, 2));
}

// Функция для вычисления общей длины маршрута
double totalDistance(const vector<int>& tour, const vector<pair<int, int>>& cities) {
    double total = 0;
    for (size_t i = 0; i < tour.size() - 1; ++i) {
        total += distance(cities[tour[i]], cities[tour[i + 1]]);
    }
    total += distance(cities[tour[tour.size() - 1]], cities[tour[0]]);
    return total;
}

// Функция для выполнения случайной перестановки двух элементов в маршруте
void swapCities(vector<int>& tour) {
    int i = rand() % tour.size();
    int j = rand() % tour.size();
    swap(tour[i], tour[j]);
}

// Функция имитации отжига для решения задачи коммивояжера
vector<int> simulatedAnnealing(vector<pair<int, int>>& cities) {
    // Параметры алгоритма
    double T = 10000.0;  // Начальная температура
    double T_min = 1e-8;  // Минимальная температура
    double alpha = 0.999;  // Скорость охлаждения

    // Генератор случайных чисел
    random_device rd;
    mt19937 g(rd());

    // Начальный маршрут (случайная перестановка городов)
    vector<int> currentTour(cities.size());
    for (size_t i = 0; i < cities.size(); ++i) {
        currentTour[i] = i;
    }
    shuffle(currentTour.begin(), currentTour.end(), g);

    vector<int> bestTour = currentTour;
    double bestDistance = totalDistance(bestTour, cities);

    while (T > T_min) {
        vector<int> newTour = currentTour;
        swapCities(newTour);

        double currentDistance = totalDistance(currentTour, cities);
        double newDistance = totalDistance(newTour, cities);

        if (newDistance < currentDistance || exp((currentDistance - newDistance) / T) > ((double)rand() / RAND_MAX)) {
            currentTour = newTour;
            currentDistance = newDistance;
        }

        if (currentDistance < bestDistance) {
            bestTour = currentTour;
            bestDistance = currentDistance;
        }

        T *= alpha;
    }

    return bestTour;
}

int main() {
    srand(time(nullptr));

    // Пример набора городов (координаты)
    vector<pair<int, int>> cities = {
        {0, 0}, {1, 3}, {4, 3}, {6, 1}, {3, 0}, {5, 2}
    };

    vector<int> bestTour = simulatedAnnealing(cities);

    cout << "Лучший найденный маршрут:\n";
    for (int city : bestTour) {
        cout << city << " ";
    }
    cout << endl;

    cout << "Общая длина маршрута: " << totalDistance(bestTour, cities) << endl;

    return 0;
}
