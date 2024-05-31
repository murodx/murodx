#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Функция для нахождения k-ой порядковой статистики в массиве
int kthSmallest(vector<int>& arr, int left, int right, int k) {
    // Сортировка подмассива
    sort(arr.begin() + left, arr.begin() + right + 1);

    // Возвращаем k-ую порядковую статистику
    return arr[left + k - 1];
}

int main() {
    vector<int> arr = {12, 3, 5, 7, 19};
    int k = 2; // Находим вторую порядковую статистику

    int result = kthSmallest(arr, 0, arr.size() - 1, k);
    cout << "k-ая порядковая статистика: " << result << endl;

    return 0;
}
