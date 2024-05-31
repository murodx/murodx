#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Order {
    int deadline;
    int cost;
};

bool compareOrders(const Order& a, const Order& b) {
    return a.cost > b.cost;
}

int maxProfit(const vector<Order>& orders) {
    int maxDeadline = 0;
    for (const auto& order : orders) {
        maxDeadline = max(maxDeadline, order.deadline);
    }

    vector<bool> dayTaken(maxDeadline, false);
    int profit = 0;

    for (const auto& order : orders) {
        for (int i = order.deadline - 1; i >= 0; --i) {
            if (!dayTaken[i]) {
                dayTaken[i] = true;
                profit += order.cost;
                break;
            }
        }
    }

    return profit;
}

int main() {
    int n;
    cout << "Введите количество заказов: ";
    cin >> n;

    vector<Order> orders(n);
    cout << "Введите дедлайн и стоимость для каждого заказа:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Для заказа " << i + 1 << ": ";
        cin >> orders[i].deadline >> orders[i].cost;
    }

    sort(orders.begin(), orders.end(), compareOrders);

    int totalProfit = maxProfit(orders);
    cout << "Максимальная суммарная стоимость выполненных заказов: " << totalProfit << endl;

    return 0;
}
