#include <iostream>
#include <vector>

using namespace std;

// Функция для определения является ли число простым
bool isPrime(int n) {
    if (n <= 1) return false;
    if (n <= 3) return true;

    // Проверяем деление на числа от 2 до sqrt(n)
    for (int i = 2; i * i <= n; ++i) {
        if (n % i == 0) return false;
    }

    return true;
}

// Функция для поиска всех простых чисел в заданном диапазоне
vector<int> findPrimes(int start, int end) {
    vector<int> primes;

    // Проверяем каждое число в диапазоне на простоту
    for (int i = start; i <= end; ++i) {
        if (isPrime(i)) {
            primes.push_back(i);
        }
    }

    return primes;
}

int main() {
    int start, end;
    cout << "Введите начало и конец диапазона: ";
    cin >> start >> end;

    vector<int> primeNumbers = findPrimes(start, end);

    cout << "Простые числа в диапазоне [" << start << ", " << end << "]:" << endl;
    for (int prime : primeNumbers) {
        cout << prime << " ";
    }
    cout << endl;

    return 0;
}
