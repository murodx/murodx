#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Task {
    int id;
    int start;
    int deadline;
};

bool compareTasks(const Task& a, const Task& b) {
    return a.deadline < b.deadline;
}

int minimizeDelay(const vector<Task>& tasks) {
    int totalDelay = 0;
    int currentTime = 0;

    for (const auto& task : tasks) {
        if (task.start >= currentTime) {
            currentTime = task.start;
        } else {
            totalDelay += currentTime - task.start;
        }
        currentTime++;
    }

    return totalDelay;
}

int main() {
    vector<Task> tasks = {
        {1, 2, 5},
        {2, 1, 3},
        {3, 5, 6},
        {4, 3, 7}
    };

    // Сортируем задачи по времени завершения (deadline)
    sort(tasks.begin(), tasks.end(), compareTasks);

    int totalDelay = minimizeDelay(tasks);
    cout << "Суммарная задержка: " << totalDelay << endl;

    return 0;
}
