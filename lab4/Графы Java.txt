package src;

import java.util.*;

public class pum {
	// Статический вложенный класс для представления вершины графа
    static class Vertex {
        String label; // Поле для хранения метки (имени) вершины
        Vertex(String label) { // Конструктор класса Vertex
            this.label = label;
        }

        // Обязательно нужно переопределить equals и hashCode
        @Override
        public boolean equals(Object o) {
            if (this == o) return true; // Проверка, является ли сравниваемый объект тем же самым объектом
            if (o == null || getClass() != o.getClass()) return false; // Проверка на null и совпадение классов
            Vertex vertex = (Vertex) o; // Приведение Object к типу Vertex
            return Objects.equals(label, vertex.label);
        }

        @Override // Переопределение метода hashCode для корректной работы с HashMap
        public int hashCode() {
            return Objects.hash(label); // Генерация хэш-кода на основе метки вершины
        }
        
        @Override // Переопределение метода toString для красивого вывода вершины
        public String toString() { // Возвращает метку вершины при преобразовании в строку
            return label; 
        }
    }

    // Статический вложенный класс для представления графа
    static class Graph {
    	// Основная структура данных графа - словарь смежности
        // Ключ: вершина, Значение: список смежных вершин
        private Map<Vertex, List<Vertex>> adjVertices;
        
        // Добавляем конструктор
        public Graph() {
            this.adjVertices = new HashMap<>(); // Инициализация словаря смежности как новой HashMap
        }
        
        // Метод для добавления новой вершины в граф
        void addVertex(String label) {
            adjVertices.putIfAbsent(new Vertex(label), new ArrayList<>());
        }

        void removeVertex(String label) { // Метод для удаления вершины из графа
        	// Добавляет вершину в словарь, если её еще нет
            // Использует новую вершину как ключ и пустой список как значение
            Vertex v = new Vertex(label);
            adjVertices.values().stream().forEach(e -> e.remove(v)); // Удаление вершины из всех списков смежности других вершин
            adjVertices.remove(new Vertex(label)); // Удаление самой вершины из словаря
        }
     
        void addEdge(String label1, String label2) { // Метод для добавления ребра между двумя вершинами
            Vertex v1 = new Vertex(label1); // Создание объектов вершин на основе меток
            Vertex v2 = new Vertex(label2);
            adjVertices.get(v1).add(v2); // Добавление v2 в список смежности v1
            adjVertices.get(v2).add(v1);  // Добавление v1 в список смежности v2 (неориентированный граф)
        }
        
        void removeEdge(String label1, String label2) { // Метод для удаления ребра между двумя вершинами
            Vertex v1 = new Vertex(label1); // Создание объектов вершин на основе меток
            Vertex v2 = new Vertex(label2);
            List<Vertex> eV1 = adjVertices.get(v1); // Получение списка смежности для первой вершины
            List<Vertex> eV2 = adjVertices.get(v2);
            if (eV1 != null) // Если список существует, удаляем v2 из списка смежности v1
                eV1.remove(v2);
            if (eV2 != null)
                eV2.remove(v1);
        }
        
        List<Vertex> getAdjVertices(String label) { // Метод для получения списка смежных вершин
            return adjVertices.get(new Vertex(label)); // Возвращает список вершин, смежных с заданной вершиной
        }
        
        // Получаем весь словарь смежности
        public Map<Vertex, List<Vertex>> getAdjVertices() {
            return adjVertices;
        }
    }

    // Метод создания предопределенного графа
    static Graph createGraph() {
        Graph graph = new Graph();
        graph.addVertex("Bob");
        graph.addVertex("Alice");
        graph.addVertex("Mark");
        graph.addVertex("Rob");
        graph.addVertex("Maria");
        graph.addEdge("Bob", "Alice");
        graph.addEdge("Bob", "Rob");
        graph.addEdge("Alice", "Mark");
        graph.addEdge("Rob", "Mark");
        graph.addEdge("Alice", "Maria");
        graph.addEdge("Rob", "Maria");
        return graph;
    }

    // Статический вложенный класс для алгоритмов обхода графа
    static class GraphTraversal {
        static Set<String> breadthFirstTraversal(Graph graph, String root) { // Обход в ширину
            Set<String> visited = new LinkedHashSet<>(); // Множество для отслеживания посещенных вершин (сохраняет порядок)
            Queue<String> queue = new LinkedList<>(); // Очередь для вершин, которые нужно посетить
            
            queue.add(root); // Добавление начальной вершины в очередь
            visited.add(root); // Отметка начальной вершины как посещенной
            
            // Пока очередь не пуста, продолжаем обход
            while (!queue.isEmpty()) {
                String vertex = queue.poll(); // Извлечение вершины из начала очереди
                List<Vertex> neighbors = graph.getAdjVertices(vertex); // Получение списка соседей текущей вершины
                if (neighbors != null) { // Если соседи существуют (вершина есть в графе)
                    for (Vertex v : neighbors) { // Обход всех соседних вершин
                        if (!visited.contains(v.label)) { // Если сосед еще не посещен
                            visited.add(v.label); // Отметить соседа как посещенного
                            queue.add(v.label); // Добавить соседа в очередь для дальнейшего обхода
                        }
                    }
                }
            }
            return visited;
        }
    }

    public static void main(String[] args) {  // Главный метод программы
        Graph graph = createGraph(); // Создание графа
        Set<String> result = GraphTraversal.breadthFirstTraversal(graph, "Bob"); // Выполнение обхода графа в ширину начиная с вершины "Bob"
           
        System.out.println(result.toString());  // Вывод результата обхода в консоль
    }
}
//     Bob
//   /    \
// Alice    Rob
// | \     /  |
// |  \   /   |
// Mark  Maria
