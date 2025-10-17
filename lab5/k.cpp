#include <iostream>       
#include <vector>         // Для использования векторов (динамических массивов)
#include <climits>        // Для использования INT_MAX
#include <algorithm>      // Для алгоритмов 

using namespace std;      

// Класс для решения задачи коммивояжера методом ветвей и границ
class TSP {
private:
    vector<vector<int>> graph;  // Матрица расстояний между городами
    int n;                      // Количество городов
    vector<int> finalPath;      // Финальный оптимальный путь
    int finalCost;              // Финальная минимальная стоимость
    const int INF = 1000000;    // Большое число для обозначения отсутствия пути

public:
    // Конструктор класса
    TSP(vector<vector<int>> inputGraph) {
        graph = inputGraph;           // Сохраняем переданную матрицу
        n = graph.size();             // Получаем количество городов
        finalCost = INF;              // Инициализируем стоимость как "бесконечность"
        finalPath.resize(n + 1, -1);  // Выделяем память под путь и заполняем -1
    }

    // Функция для создания копии матрицы
    vector<vector<int>> copyMatrix(vector<vector<int>>& matrix) {
        vector<vector<int>> newMatrix(n, vector<int>(n));  // Создаем новую матрицу n x n
        for (int i = 0; i < n; i++) {                      // Проходим по всем строкам
            for (int j = 0; j < n; j++) {                  // Проходим по всем столбцам
                newMatrix[i][j] = matrix[i][j];            // Копируем каждый элемент
            }
        }
        return newMatrix;  // Возвращаем новую матрицу
    }

    // Функция для создания копии пути
    vector<int> copyPath(vector<int>& path) {
        vector<int> newPath(path.size());      // Создаем новый путь того же размера
        for (size_t i = 0; i < path.size(); i++) {  // Проходим по всем элементам пути
            newPath[i] = path[i];              // Копируем каждый элемент
        }
        return newPath;  // Возвращаем новый путь
    }

    // Функция приведения матрицы и вычисления нижней границы
    int reduceMatrix(vector<vector<int>>& matrix) {
        int cost = 0;  // Инициализируем стоимость приведения

        // Приведение по строкам - вычитаем минимальный элемент из каждой строки
        for (int i = 0; i < n; i++) {           // Проходим по всем строкам
            int minVal = INF;                   // Инициализируем минимальное значение как INF
            for (int j = 0; j < n; j++) {       // Проходим по всем элементам строки
                if (matrix[i][j] < minVal) {    // Если нашли элемент меньше текущего минимума
                    minVal = matrix[i][j];      // Обновляем минимальное значение
                }
            }
            // Если нашли действительный минимальный элемент
            if (minVal != INF && minVal > 0) {
                cost += minVal;                 // Добавляем к общей стоимости приведения
                for (int j = 0; j < n; j++) {   // Проходим по всем элементам строки
                    if (matrix[i][j] != INF) {  // Если элемент не INF
                        matrix[i][j] -= minVal; // Вычитаем минимальное значение
                    }
                }
            }
        }

        // Приведение по столбцам - вычитаем минимальный элемент из каждого столбца
        for (int j = 0; j < n; j++) {           // Проходим по всем столбцам
            int minVal = INF;                   // Инициализируем минимальное значение как INF
            for (int i = 0; i < n; i++) {       // Проходим по всем элементам столбца
                if (matrix[i][j] < minVal) {    // Если нашли элемент меньше текущего минимума
                    minVal = matrix[i][j];      // Обновляем минимальное значение
                }
            }
            // Если нашли действительный минимальный элемент
            if (minVal != INF && minVal > 0) {
                cost += minVal;                 // Добавляем к общей стоимости приведения
                for (int i = 0; i < n; i++) {   // Проходим по всем элементам столбца
                    if (matrix[i][j] != INF) {  // Если элемент не INF
                        matrix[i][j] -= minVal; // Вычитаем минимальное значение
                    }
                }
            }
        }

        return cost;  // Возвращаем общую стоимость приведения (нижнюю границу)
    }

    // Рекурсивная функция решения TSP методом ветвей и границ
    void solveTSP(vector<vector<int>> matrix, int currentCost, int level,
        vector<int> currentPath, vector<bool> visited) {

        // Проверка выхода за границы - защита от ошибок
        if (level < 0 || level > n) return;

        // Базовый случай рекурсии - все города посещены
        if (level == n) {
            // Проверяем корректность индексов перед доступом
            if (currentPath[level - 1] < 0 || currentPath[level - 1] >= n ||
                currentPath[0] < 0 || currentPath[0] >= n) {
                return;  // Если индексы некорректны, выходим
            }

            // Проверяем возможность вернуться в начальный город
            int returnCost = matrix[currentPath[level - 1]][currentPath[0]];
            if (returnCost != INF) {  // Если путь обратно существует
                int totalCost = currentCost + returnCost;  // Вычисляем полную стоимость
                if (totalCost < finalCost) {  // Если нашли лучший маршрут
                    finalCost = totalCost;    // Обновляем лучшую стоимость
                    finalPath = copyPath(currentPath);  // Сохраняем путь
                    finalPath.push_back(currentPath[0]); // Замыкаем цикл (возврат в начало)
                }
            }
            return;  // Выходим из рекурсии
        }

        // Рекурсивный случай - перебираем все возможные следующие города
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {  // Если город i еще не посещен
                // Проверяем корректность индексов перед доступом
                if (currentPath[level - 1] < 0 || currentPath[level - 1] >= n) {
                    continue;  // Пропускаем итерацию если индексы некорректны
                }

                // Проверяем существование пути к городу i
                if (matrix[currentPath[level - 1]][i] != INF) {

                    // Создаем копии данных для рекурсивного вызова
                    vector<vector<int>> newMatrix = copyMatrix(matrix);
                    vector<bool> newVisited = visited;
                    vector<int> newPath = copyPath(currentPath);
                    int newCost = currentCost + matrix[currentPath[level - 1]][i];

                    // Запрещаем недопустимые переходы
                    for (int j = 0; j < n; j++) {
                        newMatrix[currentPath[level - 1]][j] = INF;  // Запрещаем уход из текущего города
                        newMatrix[j][i] = INF;                       // Запрещаем приход в следующий город
                    }
                    // Запрещаем преждевременный возврат в начало
                    if (currentPath[0] >= 0 && currentPath[0] < n) {
                        newMatrix[i][currentPath[0]] = INF;
                    }

                    // Вычисляем нижнюю границу для нового состояния
                    int reductionCost = reduceMatrix(newMatrix);
                    newCost += reductionCost;  // Добавляем стоимость приведения

                    // Если нижняя граница лучше текущего лучшего решения
                    if (newCost < finalCost) {
                        newVisited[i] = true;    // Помечаем город как посещенный
                        newPath[level] = i;      // Добавляем город в путь
                        // Рекурсивный вызов для следующего уровня
                        solveTSP(newMatrix, newCost, level + 1, newPath, newVisited);
                    }
                }
            }
        }
    }

    // Основная функция решения задачи
    void solve() {
        vector<bool> visited(n, false);  // Массив посещенных городов (изначально все false)
        vector<int> currentPath(n, -1);  // Текущий путь (изначально все -1)

        visited[0] = true;    // Начинаем с города 0, помечаем его как посещенный
        currentPath[0] = 0;   // Первый город в пути - 0

        // Вычисляем начальную нижнюю границу
        vector<vector<int>> tempMatrix = copyMatrix(graph);
        int initialCost = reduceMatrix(tempMatrix);

        // Запускаем рекурсивный поиск
        solveTSP(graph, initialCost, 1, currentPath, visited);
    }

    // Функция вывода результатов
    void printResult() {
        // Проверяем, найден ли действительный маршрут
        if (finalCost >= INF || finalPath[0] == -1) {
            cout << "No valid route has been found!" << endl;
            return;
        }

        // Выводим минимальную стоимость
        cout << "Minimum cost: " << finalCost << endl;
        // Выводим оптимальный маршрут
        cout << "The optimal route: ";
        for (size_t i = 0; i < finalPath.size(); i++) {
            cout << finalPath[i];
            if (i < finalPath.size() - 1) cout << " -> ";  // Стрелочки между городами
        }
        cout << endl;
    }
};

// Упрощенный класс TSP с backtracking (более надежный)
class SimpleTSP {
private:
    vector<vector<int>> graph;  // Матрица расстояний
    int n;                      // Количество городов
    int minCost;                // Минимальная стоимость
    vector<int> bestPath;       // Лучший путь
    const int INF = 1000000;    // "Бесконечность"

public:
    // Конструктор
    SimpleTSP(vector<vector<int>> inputGraph) {
        graph = inputGraph;           // Сохраняем матрицу
        n = graph.size();             // Получаем количество городов
        minCost = INF;                // Инициализируем минимальную стоимость
        bestPath.resize(n + 1, -1);   // Выделяем память под путь
    }

    // Основная функция решения
    void solve() {
        vector<int> path(n, -1);        // Текущий путь
        vector<bool> visited(n, false); // Посещенные города

        path[0] = 0;        // Начинаем с города 0
        visited[0] = true;  // Помечаем город 0 как посещенный

        // Запускаем backtracking
        backtrack(path, visited, 1, 0);
    }

private:
    // Рекурсивная функция backtracking
    void backtrack(vector<int>& path, vector<bool>& visited, int count, int cost) {
        // Базовый случай - все города посещены
        if (count == n) {
            // Добавляем стоимость возврата в начальный город
            int finalCost = cost + graph[path[count - 1]][0];
            // Если нашли лучший маршрут
            if (finalCost < minCost) {
                minCost = finalCost;  // Обновляем минимальную стоимость
                // Копируем путь
                for (int i = 0; i < n; i++) {
                    bestPath[i] = path[i];
                }
                bestPath[n] = 0;  // Замыкаем цикл
            }
            return;
        }

        // Перебираем все возможные следующие города
        for (int i = 0; i < n; i++) {
            // Если город не посещен и существует путь к нему
            if (!visited[i] && graph[path[count - 1]][i] < INF) {
                visited[i] = true;      // Помечаем город как посещенный
                path[count] = i;        // Добавляем город в путь
                // Рекурсивный вызов с обновленной стоимостью
                backtrack(path, visited, count + 1, cost + graph[path[count - 1]][i]);
                visited[i] = false;     // Backtrack - снимаем отметку о посещении
            }
        }
    }

public:
    // Функция вывода результатов
    void printResult() {
        // Проверяем, найден ли маршрут
        if (minCost >= INF) {
            cout << "No valid route has been found!" << endl;
            return;
        }

        // Выводим результаты
        cout << "Minimum cost: " << minCost << endl;
        cout << "The optimal route: ";
        for (int i = 0; i <= n; i++) {
            cout << bestPath[i];
            if (i < n) cout << " -> ";
        }
        cout << endl;

        // Проверка стоимости - вычисляем заново для верификации
        cout << "Cost verification: ";
        int total = 0;
        for (int i = 0; i < n; i++) {
            total += graph[bestPath[i]][bestPath[i + 1]];
        }
        cout << total << endl;
    }
};

// Главная функция программы
int main() {
    // Определяем "бесконечность"
    int INF = 1000000;

    // Создаем матрицу расстояний между городами
    // INF означает, что прямого пути между городами нет
    vector<vector<int>> graph = {
        // Расстояния из города 0 в другие города
        {INF, 20, 30, 10, 11},  // 0->1=20, 0->2=30, 0->3=10, 0->4=11
        // Расстояния из города 1 в другие города  
        {15, INF, 16, 4, 2},    // 1->0=15, 1->2=16, 1->3=4, 1->4=2
        // Расстояния из города 2 в другие города
        {3, 5, INF, 2, 4},      // 2->0=3, 2->1=5, 2->3=2, 2->4=4
        // Расстояния из города 3 в другие города
        {19, 6, 18, INF, 3},    // 3->0=19, 3->1=6, 3->2=18, 3->4=3
        // Расстояния из города 4 в другие города
        {16, 4, 7, 16, INF}     // 4->0=16, 4->1=4, 4->2=7, 4->3=16
    };

    cout << "=== Simplified version ===" << endl;
    // Создаем объект упрощенного TSP
    SimpleTSP simpleTsp(graph);
    // Решаем задачу
    simpleTsp.solve();
    // Выводим результаты
    simpleTsp.printResult();

    cout << "\n=== Full version ===" << endl;
    // Создаем объект полного TSP
    TSP fullTsp(graph);
    // Решаем задачу
    fullTsp.solve();
    // Выводим результаты
    fullTsp.printResult();

    return 0;  // Завершаем программу
}
