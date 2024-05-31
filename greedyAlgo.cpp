#include <iostream>
#include <vector>

using namespace std;

vector<int> nominal = {500, 200, 100, 50, 20, 10};

int minNumberOfNotes(int n) {
    vector<int> result(n + 1, -1);
    result[0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < nominal.size(); ++j) {
            if (i >= nominal[j] && result[i - nominal[j]] != -1) {
                result[i] = (result[i] == -1) ? result[i - nominal[j]] + 1 : min(result[i], result[i - nominal[j]] + 1);
            }
        }
    }

    return result[n];
}

int main() {
    int n;
    cout << "Введите сумму (0 ≤ n ≤ 1000001): ";
    cin >> n;

    int minNotes = minNumberOfNotes(n);
    if (minNotes == -1) {
        cout << "-1\n";
    } else {
        cout << "Минимальное количество купюр: " << minNotes << endl;
    }

    return 0;
}
