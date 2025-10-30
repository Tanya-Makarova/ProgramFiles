#include <iostream>
using namespace std;

// Метод для разбиения массива
int partition(int array[], int low, int high) {
    int pivot = array[high];
    int i = low - 1; // Индекс меньшего элемента

    for (int j = low; j < high; j++) {        
        if (array[j] <= pivot) {
            i++;            
            int temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
    }

    int temp = array[i + 1];
    array[i + 1] = array[high];
    array[high] = temp;

    return i + 1;
}

// Метод для сортировки массива
void quickSort(int array[], int low, int high) {
    if (low < high) {
        int pi = partition(array, low, high);
        
        quickSort(array, low, pi - 1);
        quickSort(array, pi + 1, high);
    }
}

// Mетод для вывода массива
void printArray(int array[], int size) {
    for (int i = 0; i < size; i++) {
        cout << array[i] << " ";
    }
    cout << endl;
}

// Основная функция для запуска сортировки
int main() {
    int array[] = { 10, 7, 8, 9, 1, 5 };
    int n = sizeof(array) / sizeof(array[0]);

    cout << "Base array:" << endl;
    printArray(array, n);

    quickSort(array, 0, n - 1);

    cout << "Sorted array:" << endl;
    printArray(array, n);

    return 0;
}