#include <iostream>
using namespace std;

// Функция для сортировки массива вставками
void insertionSort(int arr[], int n) {
    // Проходим по всем элементам массива, начиная со второго
    for (int i = 1; i < n; i++) {
        int j = i - 1;
        int key = arr[i];  // Текущий элемент, который нужно вставить

        // Перемещаем элементы arr[0..i-1], которые больше key
        // на одну позицию вперед
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;  // Вставляем key на правильное место
    }
}

// Функция для вывода массива
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

// Основная функция для тестирования
int main() {
    int arr[] = { 12, 11, 13, 5, 6 };
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Base array:" << endl;
    printArray(arr, n);

    insertionSort(arr, n);

    cout << "Sorted array:" << endl;
    printArray(arr, n);

    return 0;
}
