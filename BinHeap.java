package src;

import java.util.ArrayList;
import java.util.List;
import java.util.NoSuchElementException;

public class BinHeap {
    private List<Integer> heapvector;  // Список для хранения элементов кучи
    private int currentSize;           // Текущее количество элементов в куче

    // Конструктор класса
    public BinHeap() {
        this.heapvector = new ArrayList<>();
        this.heapvector.add(0); // Фиктивный элемент для индексации с 1
        this.currentSize = 0;
    }

    // Конструктор с начальными значениями
    public BinHeap(List<Integer> initialVector) {
        this();
        this.buildheap(initialVector);
    }

    // Метод просеивания вверх
    private void percUp(int i) {
        while (i > 1) {  // Пока не дошли до корня
            int parentIdx = i / 2;  // Вычисляем индекс родителя
            if (this.heapvector.get(i) < this.heapvector.get(parentIdx)) {
                // Если текущий элемент меньше родителя - меняем местами
                swap(i, parentIdx);
                i = parentIdx;  // Переходим к родительской позиции
            } else {
                break;  // Свойство кучи восстановлено - выходим
            }
        }
    }

    // Вспомогательный метод для обмена элементов
    private void swap(int i, int j) {
        int temp = this.heapvector.get(i);
        this.heapvector.set(i, this.heapvector.get(j));
        this.heapvector.set(j, temp);
    }

    // Добавление элемента в кучу
    public void insert(int k) {
        this.heapvector.add(k);  // Добавляем элемент в конец списка
        this.currentSize++;      // Увеличиваем счетчик элементов
        this.percUp(this.currentSize); // Восстанавливаем свойства кучи
    }

    // Поиск минимального потомка
    private int minChild(int i) {
        int left = i * 2;      // Индекс левого потомка
        int right = i * 2 + 1; // Индекс правого потомка

        // Если правого потомка нет, возвращаем левого
        if (right > this.currentSize) {
            return left;
        }
        // Иначе возвращаем меньшего из двух
        else {
            return (this.heapvector.get(left) < this.heapvector.get(right)) ? left : right;
        }
    }

    // Метод просеивания вниз
    private void percDown(int i) {
        while (i * 2 <= this.currentSize) {  // Пока есть хотя бы левый потомок
            int mc = this.minChild(i);       // Находим минимального потомка

            // Если текущий узел больше наименьшего потомка - меняем
            if (this.heapvector.get(i) > this.heapvector.get(mc)) {
                swap(i, mc);
                i = mc;  // Переходим к позиции потомка
            } else {
                break;  // Свойство кучи восстановлено - выходим
            }
        }
    }

    // Извлечение минимального элемента
    public int delMin() {
        if (this.currentSize == 0) {
            throw new NoSuchElementException("Heap is empty");  // Проверка на пустоту
        }

        int minVal = this.heapvector.get(1);  // Сохраняем минимальный элемент (корень)
        this.heapvector.set(1, this.heapvector.get(this.currentSize));  // Перемещаем последний элемент в корень
        this.heapvector.remove(this.currentSize);  // Удаляем последний элемент
        this.currentSize--;               // Уменьшаем счетчик

        if (this.currentSize > 0) {
            this.percDown(1);  // Восстанавливаем свойства кучи от корня
        }

        return minVal;  // Возвращаем извлеченный минимальный элемент
    }

    // Построение кучи из списка
    public void buildheap(List<Integer> avector) {
        // Очищаем кучу
        this.heapvector = new ArrayList<>();
        this.heapvector.add(0);  // Фиктивный элемент
        this.currentSize = 0;     // Сбрасываем счетчик

        // Добавляем все элементы через insert
        for (int val : avector) {
            this.insert(val);  // Каждый элемент добавляется с восстановлением свойств кучи
        }
    }

    // Построение кучи из массива
    public void buildheap(int[] arr) {
        // Очищаем кучу
        this.heapvector = new ArrayList<>();
        this.heapvector.add(0);  // Фиктивный элемент
        this.currentSize = 0;     // Сбрасываем счетчик

        // Добавляем все элементы через insert
        for (int val : arr) {
            this.insert(val);  // Каждый элемент добавляется с восстановлением свойств кучи
        }
    }

    // Проверка на пустоту
    public boolean isEmpty() {
        return this.currentSize == 0;  // Проверка на пустоту кучи
    }

    // Получение минимального элемента без удаления
    public int findMin() {
        if (this.currentSize == 0) {
            throw new NoSuchElementException("Heap is empty");
        }
        return this.heapvector.get(1);  // Минимальный элемент всегда в корне (индекс 1)
    }

    // Вывод всех элементов кучи
    public void printHeap() {
        System.out.print("Heap elements: ");
        for (int i = 1; i <= this.currentSize; i++) {
            System.out.print(this.heapvector.get(i) + " ");  // Вывод всех элементов кучи
        }
        System.out.println();
    }

    // Получение размера кучи
    public int size() {
        return this.currentSize;
    }

    // Главный метод для тестирования
    public static void main(String[] args) {
        int[] arr = { 3, 1, 23, 5, 6, 7, 43, 8, 864 };  // Исходный массив

        BinHeap bh = new BinHeap();  // Создание объекта кучи
        bh.buildheap(arr);           // Построение кучи из массива

        System.out.print("Initial heap: ");
        bh.printHeap();              // Вывод начальной кучи

        System.out.println("\nExtracting elements:");
        while (!bh.isEmpty()) {      // Пока куча не пуста
            System.out.println("Extracted: " + bh.delMin());  // Извлекаем минимальный элемент
            if (!bh.isEmpty()) {
                System.out.print("Remaining heap: ");
                bh.printHeap();      // Вывод оставшейся кучи
            }
        }              
       
    }
}
