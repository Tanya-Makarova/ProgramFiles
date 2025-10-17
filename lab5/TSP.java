package src;

public class TSP {
    private int[][] graph;          // Матрица расстояний между городами
    private int n;                  // Количество городов
    private int[] finalPath;        // Финальный оптимальный путь
    private int finalCost;          // Финальная минимальная стоимость
    private final int INF = 1000000; // "Бесконечность" - большое число для обозначения отсутствия пути

    // Конструктор класса
    public TSP(int[][] inputGraph) {
        this.graph = inputGraph;           // Сохраняем переданную матрицу
        this.n = inputGraph.length;        // Получаем количество городов
        this.finalCost = INF;              // Инициализируем стоимость как "бесконечность"
        this.finalPath = new int[n + 1];   // Создаем массив для пути
        Arrays.fill(finalPath, -1);        // Заполняем массив значениями -1
    }

    // Функция для создания копии матрицы
    private int[][] copyMatrix(int[][] matrix) {
        int[][] newMatrix = new int[n][n]; // Создаем новую матрицу n x n
        for (int i = 0; i < n; i++) {      // Проходим по всем строкам
            for (int j = 0; j < n; j++) {  // Проходим по всем столбцам
                newMatrix[i][j] = matrix[i][j]; // Копируем каждый элемент
            }
        }
        return newMatrix; // Возвращаем новую матрицу
    }

    // Функция для создания копии пути
    private int[] copyPath(int[] path) {
        int[] newPath = new int[path.length]; // Создаем новый путь того же размера
        for (int i = 0; i < path.length; i++) { // Проходим по всем элементам пути
            newPath[i] = path[i];           // Копируем каждый элемент
        }
        return newPath; // Возвращаем новый путь
    }

    // Функция приведения матрицы и вычисления нижней границы
    private int reduceMatrix(int[][] matrix) {
        int cost = 0; // Инициализируем стоимость приведения

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

        return cost; // Возвращаем общую стоимость приведения (нижнюю границу)
    }

    // Рекурсивная функция решения TSP методом ветвей и границ
    private void solveTSP(int[][] matrix, int currentCost, int level,
                         int[] currentPath, boolean[] visited) {

        // Проверка выхода за границы - защита от ошибок
        if (level < 0 || level > n) return;

        // Базовый случай рекурсии - все города посещены
        if (level == n) {
            // Проверяем корректность индексов перед доступом
            if (currentPath[level - 1] < 0 || currentPath[level - 1] >= n ||
                currentPath[0] < 0 || currentPath[0] >= n) {
                return; // Если индексы некорректны, выходим
            }

            // Проверяем возможность вернуться в начальный город
            int returnCost = matrix[currentPath[level - 1]][currentPath[0]];
            if (returnCost != INF) { // Если путь обратно существует
                int totalCost = currentCost + returnCost; // Вычисляем полную стоимость
                if (totalCost < finalCost) { // Если нашли лучший маршрут
                    finalCost = totalCost;   // Обновляем лучшую стоимость
                    finalPath = copyPath(currentPath); // Сохраняем путь
                    finalPath[n] = currentPath[0]; // Замыкаем цикл (возврат в начало)
                }
            }
            return; // Выходим из рекурсии
        }

        // Рекурсивный случай - перебираем все возможные следующие города
        for (int i = 0; i < n; i++) {
            if (!visited[i]) { // Если город i еще не посещен
                // Проверяем корректность индексов перед доступом
                if (currentPath[level - 1] < 0 || currentPath[level - 1] >= n) {
                    continue; // Пропускаем итерацию если индексы некорректны
                }

                // Проверяем существование пути к городу i
                if (matrix[currentPath[level - 1]][i] != INF) {

                    // Создаем копии данных для рекурсивного вызова
                    int[][] newMatrix = copyMatrix(matrix);
                    boolean[] newVisited = visited.clone();
                    int[] newPath = copyPath(currentPath);
                    int newCost = currentCost + matrix[currentPath[level - 1]][i];

                    // Запрещаем недопустимые переходы
                    for (int j = 0; j < n; j++) {
                        newMatrix[currentPath[level - 1]][j] = INF; // Запрещаем уход из текущего города
                        newMatrix[j][i] = INF;                      // Запрещаем приход в следующий город
                    }
                    // Запрещаем преждевременный возврат в начало
                    if (currentPath[0] >= 0 && currentPath[0] < n) {
                        newMatrix[i][currentPath[0]] = INF;
                    }

                    // Вычисляем нижнюю границу для нового состояния
                    int reductionCost = reduceMatrix(newMatrix);
                    newCost += reductionCost; // Добавляем стоимость приведения

                    // Если нижняя граница лучше текущего лучшего решения
                    if (newCost < finalCost) {
                        newVisited[i] = true;   // Помечаем город как посещенный
                        newPath[level] = i;     // Добавляем город в путь
                        // Рекурсивный вызов для следующего уровня
                        solveTSP(newMatrix, newCost, level + 1, newPath, newVisited);
                    }
                }
            }
        }
    }

    // Основная функция решения задачи
    public void solve() {
        boolean[] visited = new boolean[n]; // Массив посещенных городов
        int[] currentPath = new int[n];     // Текущий путь
        Arrays.fill(visited, false);        // Изначально все города не посещены
        Arrays.fill(currentPath, -1);       // Изначально путь заполнен -1

        visited[0] = true;    // Начинаем с города 0, помечаем его как посещенный
        currentPath[0] = 0;   // Первый город в пути - 0

        // Вычисляем начальную нижнюю границу
        int[][] tempMatrix = copyMatrix(graph);
        int initialCost = reduceMatrix(tempMatrix);

        // Запускаем рекурсивный поиск
        solveTSP(graph, initialCost, 1, currentPath, visited);
    }

    // Функция вывода результатов
    public void printResult() {
        // Проверяем, найден ли действительный маршрут
        if (finalCost >= INF || finalPath[0] == -1) {
            System.out.println("No valid route has been found!");
            return;
        }

        // Выводим минимальную стоимость
        System.out.println("Minimum cost: " + finalCost);
        // Выводим оптимальный маршрут
        System.out.print("The optimal route: ");
        for (int i = 0; i < finalPath.length; i++) {
            System.out.print(finalPath[i]);
            if (i < finalPath.length - 1) System.out.print(" -> "); // Стрелочки между городами
        }
        System.out.println();
    }
}

// Упрощенный класс TSP с backtracking (более надежный)
class SimpleTSP {
    private int[][] graph;          // Матрица расстояний
    private int n;                  // Количество городов
    private int minCost;            // Минимальная стоимость
    private int[] bestPath;         // Лучший путь
    private final int INF = 1000000; // "Бесконечность"

    // Конструктор
    public SimpleTSP(int[][] inputGraph) {
        this.graph = inputGraph;           // Сохраняем матрицу
        this.n = inputGraph.length;        // Получаем количество городов
        this.minCost = INF;                // Инициализируем минимальную стоимость
        this.bestPath = new int[n + 1];    // Создаем массив для пути
        Arrays.fill(bestPath, -1);         // Заполняем массив значениями -1
    }

    // Основная функция решения
    public void solve() {
        int[] path = new int[n];           // Текущий путь
        boolean[] visited = new boolean[n]; // Посещенные города
        Arrays.fill(path, -1);             // Заполняем путь значениями -1
        Arrays.fill(visited, false);       // Изначально все города не посещены

        path[0] = 0;        // Начинаем с города 0
        visited[0] = true;  // Помечаем город 0 как посещенный

        // Запускаем backtracking
        backtrack(path, visited, 1, 0);
    }

    // Рекурсивная функция backtracking
    private void backtrack(int[] path, boolean[] visited, int count, int cost) {
        // Базовый случай - все города посещены
        if (count == n) {
            // Добавляем стоимость возврата в начальный город
            int finalCost = cost + graph[path[count - 1]][0];
            // Если нашли лучший маршрут
            if (finalCost < minCost) {
                minCost = finalCost; // Обновляем минимальную стоимость
                // Копируем путь
                for (int i = 0; i < n; i++) {
                    bestPath[i] = path[i];
                }
                bestPath[n] = 0; // Замыкаем цикл
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

    // Функция вывода результатов
    public void printResult() {
        // Проверяем, найден ли маршрут
        if (minCost >= INF) {
            System.out.println("No valid route has been found!");
            return;
        }

        // Выводим результаты
        System.out.println("Minimum cost: " + minCost);
        System.out.print("The optimal route: ");
        for (int i = 0; i <= n; i++) {
            System.out.print(bestPath[i]);
            if (i < n) System.out.print(" -> ");
        }
        System.out.println();

        // Проверка стоимости - вычисляем заново для верификации
        System.out.print("Cost verification: ");
        int total = 0;
        for (int i = 0; i < n; i++) {
            total += graph[bestPath[i]][bestPath[i + 1]];
        }
        System.out.println(total);
    }
}

// Главный класс программы
public class Main {
    // Главная функция программы
    public static void main(String[] args) {
        // Определяем "бесконечность"
        int INF = 1000000;

        // Создаем матрицу расстояний между городами
        // INF означает, что прямого пути между городами нет
        int[][] graph = {
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

        System.out.println("=== Simplified version ===");
        // Создаем объект упрощенного TSP
        SimpleTSP simpleTsp = new SimpleTSP(graph);
        // Решаем задачу
        simpleTsp.solve();
        // Выводим результаты
        simpleTsp.printResult();

        System.out.println("\n=== Full version ===");
        // Создаем объект полного TSP
        TSP fullTsp = new TSP(graph);
        // Решаем задачу
        fullTsp.solve();
        // Выводим результаты
        fullTsp.printResult();
    }
}
