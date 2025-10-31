#include <iostream>
#include <vector>
using namespace std;

int interpolationSearch(vector<int> arr, int lo, int hi, int x) {
    if (lo <= hi && x >= arr[lo] && x <= arr[hi]) {
        // Вычисляем позицию с помощью интерполяционной формулы
        int pos = lo + (((hi - lo) * (x - arr[lo])) / (arr[hi] - arr[lo]));

        // Состояние, если цель найдена
        if (arr[pos] == x) {
            return pos;
        }

        // Если x больше, x находится в правом подмассиве
        if (arr[pos] < x) {
            return interpolationSearch(arr, pos + 1, hi, x);
        }

        // Если x меньше, x находится в левом подмассиве
        if (arr[pos] > x) {
            return interpolationSearch(arr, lo, pos - 1, x);
        }
    }
    return -1;
}

int main() {
    vector<int> arr = { 10, 12, 13, 16, 18, 19, 20, 21, 22, 23, 24, 33, 35, 42, 47 };
    int x = 18;
    int n = arr.size();

    int result = interpolationSearch(arr, 0, n - 1, x);

    if (result != -1) {
        cout << "Элемент найден на позиции: " << result << endl;
    }
    else {
        cout << "Элемент не найден" << endl;
    }

    return 0;
}