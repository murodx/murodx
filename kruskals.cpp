#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Структура для представления ребра графа
struct Edge {
    int src, dest, weight;
};

// Структура для представления графа
struct Graph {
    int V, E;
    vector<Edge> edges;
};

// Структура для представления множества (подмножества) для алгоритма объединения-поиска
struct Subset {
    int parent;
    int rank;
};

// Функция для создания графа с V вершинами и E ребрами
Graph* createGraph(int V, int E) {
    Graph* graph = new Graph;
    graph->V = V;
    graph->E = E;
    return graph;
}

// Функция для нахождения множества вершины i (с применением сжатия пути)
int find(Subset subsets[], int i) {
    if (subsets[i].parent != i)
        subsets[i].parent = find(subsets, subsets[i].parent);
    return subsets[i].parent;
}

// Функция для объединения двух множеств x и y (по рангу)
void Union(Subset subsets[], int x, int y) {
    int xroot = find(subsets, x);
    int yroot = find(subsets, y);

    if (subsets[xroot].rank < subsets[yroot].rank) {
        subsets[xroot].parent = yroot;
    } else if (subsets[xroot].rank > subsets[yroot].rank) {
        subsets[yroot].parent = xroot;
    } else {
        subsets[yroot].parent = xroot;
        subsets[xroot].rank++;
    }
}

// Функция для сравнения двух ребер по весу (для сортировки)
bool compareEdges(Edge a, Edge b) {
    return a.weight < b.weight;
}

// Основная функция для поиска минимального остовного дерева с использованием алгоритма Краскала
void KruskalMST(Graph* graph, int minWeight, int maxWeight) {
    int V = graph->V;
    vector<Edge> result;  // Вектор для хранения ребер МОД

    // Шаг 1: Отсортировать все ребра по возрастанию веса
    sort(graph->edges.begin(), graph->edges.end(), compareEdges);

    // Создать V подмножеств с одним элементом в каждом
    Subset *subsets = new Subset[(V * sizeof(Subset))];
    for (int v = 0; v < V; ++v) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Инициализировать индексы для result[]
    int e = 0;  // Количество ребер в результате
    int i = 0;  // Начальный индекс отсортированных ребер

    // Пока количество ребер в результате не равно V-1
    while (e < V - 1 && i < graph->E) {
        // Шаг 2: Выбрать следующее ребро с наименьшим весом
        Edge next_edge = graph->edges[i++];

        // Проверить, находится ли вес ребра в заданном диапазоне
        if (next_edge.weight < minWeight || next_edge.weight > maxWeight) {
            continue;
        }

        int x = find(subsets, next_edge.src);
        int y = find(subsets, next_edge.dest);

        // Если включение этого ребра не образует цикл, включить его в результат
        if (x != y) {
            result.push_back(next_edge);
            Union(subsets, x, y);
            e++;
        }
    }

    // Вывести результат
    cout << "Следующие ребра входят в минимальное остовное дерево:\n";
    for (i = 0; i < result.size(); ++i) {
        cout << result[i].src << " -- " << result[i].dest << " == " << result[i].weight << endl;
    }

    delete[] subsets;
}

int main() {
    int V = 4;  // Количество вершин в графе
    int E = 5;  // Количество ребер в графе
    Graph* graph = createGraph(V, E);

    // Добавление ребер
    graph->edges.push_back({0, 1, 10});
    graph->edges.push_back({0, 2, 6});
    graph->edges.push_back({0, 3, 5});
    graph->edges.push_back({1, 3, 15});
    graph->edges.push_back({2, 3, 4});

    // Задание ограничений на веса ребер
    int minWeight = 5;
    int maxWeight = 15;

    KruskalMST(graph, minWeight, maxWeight);

    delete graph;
    return 0;
}
