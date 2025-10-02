#include <iostream>
#include <stdexcept> // для работы с исключениями
#include <vector>
using namespace std;

class BinHeap {
private:
    vector<int> heapvector; // Вектор для хранения элементов кучи, heapvector - динамический массив для хранения элементов
    int CurrentSize; // Текущее количество элементов в куче, CurrentSize - счетчик элементов (исключая фиктивный элемент)

public:
    BinHeap() {
        this->heapvector.push_back(0); // Фиктивный элемент для индексации с 1
        this->CurrentSize = 0;
    }
    // Добавляем фиктивный элемент 0 в позицию 0
    // Это позволяет использовать индексацию с 1 для удобства вычислений
    // Инициализируем размер кучи как 0

    void percUp(int i) {
        while (i > 1) { // Пока не дошли до корня
            int parentIdx = i / 2; // Вычисляем индекс родителя
            if (this->heapvector[i] < this->heapvector[parentIdx]) {
                // Если текущий элемент меньше родителя - меняем местами
                swap(this->heapvector[i], this->heapvector[parentIdx]);
                i = parentIdx; // Переходим к родительской позиции
            }
            else {
                break; // Свойство кучи восстановлено - выходим из цикла
            }
        }
    }

    void insert(int k) {
        this->heapvector.push_back(k); // Добавляем элемент в конец вектора и увеличиваем счетчик
        this->CurrentSize++;
        this->percUp(this->CurrentSize); // Восстанавливаем свойства кучи
    }
    // Вычисляет индексы левого и правого потомков
    // Возвращает индекс потомка с меньшим значением

    int minChild(int i) {
        int left = i * 2; // Индекс левого потомка
        int right = i * 2 + 1; // Индекс правого потомка

        // Если правого потомка нет, возвращаем левого
        if (right > this->CurrentSize) {
            return left;
        }
        // Иначе возвращаем меньшего из двух
        else {
            return (this->heapvector[left] < this->heapvector[right]) ? left : right;
        }
    }
    // Восстанавливает свойство кучи сверху вниз
    void percDown(int i) {
        while (i * 2 <= this->CurrentSize) {  // Пока есть хотя бы левый потомок
            int mc = this->minChild(i);

            // Если текущий узел больше наименьшего потомка - меняем
            if (this->heapvector[i] > this->heapvector[mc]) {
                swap(this->heapvector[i], this->heapvector[mc]);
                i = mc;  // Переходим к позиции потомка
            }
            else {
                break;  // Свойство кучи восстановлено - выходим
            }
        }
    }

    int delMin() {
        if (this->CurrentSize == 0) { // Проверка на пустоту
            throw runtime_error("Heap is empty");
        }

        int minVal = this->heapvector[1]; // Сохраняем минимальный элемент (корень)
        this->heapvector[1] = this->heapvector[this->CurrentSize]; // Перемещаем последний элемент в корень
        this->heapvector.pop_back(); // Удаляем последний элемент
        this->CurrentSize--; // Уменьшаем счетчик

        if (this->CurrentSize > 0) {
            this->percDown(1);
        }

        return minVal; // Возвращаем извлеченный минимальный элемент
    }

    // Построение кучи из массива:
    void buildheap(vector<int> avector) {
        // Очищаем кучу
        this->heapvector = { 0 }; // Создаем новый вектор с фиктивным элементом
        this->CurrentSize = 0; // Сбрасываем счетчик

        // Добавляем все элементы через insert
        for (int val : avector) {
            this->insert(val); // Каждый элемент добавляется с восстановлением свойств кучи
        }
    }

    bool isEmpty() {
        return this->CurrentSize == 0;
    }

    void printHeap() { // Выводит все элементы кучи (начиная с индекса 1)
        cout << "Heap elements: ";
        for (int i = 1; i <= this->CurrentSize; i++) {
            cout << this->heapvector[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    int arr[] = { 3, 1, 23, 5, 6, 7, 43, 8, 864 };
    vector<int> a(arr, arr + (sizeof(arr) / sizeof(arr[0])));

    BinHeap* bh = new BinHeap(); // Создание объекта кучи
    bh->buildheap(a); // Построение кучи из вектора

    cout << "Initial heap: ";
    bh->printHeap(); // Вывод начальной кучи


    cout << "\nExtracting elements:\n";
    while (!bh->isEmpty()) { // Пока куча не пуста
        cout << "Extracted: " << bh->delMin() << endl; // Извлекаем минимальный элемент
        if (!bh->isEmpty()) {
            cout << "Remaining heap: ";
            bh->printHeap(); // Вывод оставшейся кучи
        }
    }

    delete bh;
    return 0;
}