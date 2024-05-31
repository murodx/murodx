#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int minCostPath(const vector<vector<int>>& grid) {
    int n = grid.size();
    int m = grid[0].size();

    // Создаем массив для хранения минимальных весов
    vector<vector<int>> dp(n, vector<int>(m, 0));

    // Инициализируем значение верхнего левого угла
    dp[0][0] = grid[0][0];
    

    // Заполняем первый столбец
    for (int i = 1; i < n; ++i) {
        dp[i][0] = dp[i - 1][0] + grid[i][0];
    }

    // Заполняем первую строку
    for (int j = 1; j < m; ++j) {
        dp[0][j] = dp[0][j - 1] + grid[0][j];
    }

    // Заполняем остальные клетки
    for (int i = 1; i < n; ++i) {
        for (int j = 1; j < m; ++j) {
            dp[i][j] = grid[i][j] + min(dp[i - 1][j], min(dp[i][j - 1], dp[i - 1][j - 1]));
        }
    }

    // Возвращаем значение в правом нижнем углу
    return dp[n - 1][m - 1];
}

int main() {
    int n, m;
    cout << "Введите размеры поля (n, m): ";
    cin >> n >> m;

    vector<vector<int>> grid(n, vector<int>(m));
    cout << "Введите значения для каждой клетки:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> grid[i][j];
        }
    }

    int minCost = minCostPath(grid);
    cout << "Минимальный вес маршрута: " << minCost << endl;

    return 0;
}
