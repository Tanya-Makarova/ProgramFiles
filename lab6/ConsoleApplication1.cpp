#include <iostream>
#include <vector>
using namespace std;

// Функция для слияния двух отсортированных массивов
vector<int> merge(vector<int> left, vector<int> right) {
    vector<int> result;
    int i = 0, j = 0;

    // Пока есть элементы в обоих массивах
    while (i < left.size() && j < right.size()) {
        if (left[i] < right[j]) {
            result.push_back(left[i]);
            i++;
        }
        else {
            result.push_back(right[j]);
            j++;
        }
    }

    // Добавляем оставшиеся элементы
    while (i < left.size()) {
        result.push_back(left[i]);
        i++;
    }

    while (j < right.size()) {
        result.push_back(right[j]);
        j++;
    }

    return result;
}

// Функция сортировки слиянием
vector<int> merge_sort(vector<int> arr) {
    // Базовый случай: массив длиной 0 или 1 уже отсортирован
    if (arr.size() <= 1) {
        return arr;
    }

    // Находим середину массива
    int mid = arr.size() / 2;

    // Делим массив на две части
    vector<int> left(arr.begin(), arr.begin() + mid);
    vector<int> right(arr.begin() + mid, arr.end());

    // Рекурсивно сортируем каждую часть
    left = merge_sort(left);
    right = merge_sort(right);

    // Сливаем отсортированные части
    return merge(left, right);
}

// Функция для вывода массива
void printArray(vector<int> arr) {
    for (int value : arr) {
        cout << value << " ";
    }
    cout << endl;
}

int main() {
    vector<int> array = { 38, 27, 43, 3, 9, 82, 10 };

    cout << "Base array: ";
    printArray(array);

    vector<int> sorted_array = merge_sort(array);

    cout << "Sorted array: ";
    printArray(sorted_array);

    return 0;
}