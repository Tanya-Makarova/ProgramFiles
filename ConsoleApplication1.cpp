#include <iostream>
#include <vector>

void selectionSort(std::vector<int>& arr) {  // Создаем метод
    // Проходим по всем элементам массива
    for (int i = 0; i < arr.size(); i++) {
        // Предполагаем, что первый элемент - минимальный
        int minIndex = i;

        // Ищем минимальный элемент в оставшейся части массива
        for (int j = i + 1; j < arr.size(); j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        // Меняем найденный минимальный элемент с первым элементом в неотсортированной части
        std::swap(arr[i], arr[minIndex]);
    }
}

// Тестируем
int main() {
    // Создаем тестовый массив
    std::vector<int> testArray = { 64, 22, 12, 25, 11 };

    std::cout << "Base array: ";
    for (int num : testArray) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    // Сортируем массив
    selectionSort(testArray);

    std::cout << "Sorted array: ";
    for (int num : testArray) {
        std::cout << num << " ";
    }
    std::cout << std::endl;

    return 0;
}