#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

//Оптимальный рекурсивный алгоритм для генерации перестановок
void generatePermutations(string& str, int start, vector<string>& result) {
    // Базовый случай: если дошли до конца строки
    if (start == str.length() - 1) {
        result.push_back(str);
        return;
    }

    // Рекурсивный случай: генерируем перестановки
    for (int i = start; i < str.length(); i++) {
        // Пропускаем дубликаты для оптимизации (опционально)
        if (i != start && str[i] == str[start]) {
            continue;
        }

        // Меняем местами символы
        swap(str[start], str[i]);

        // Рекурсивный вызов для оставшейся части строки
        generatePermutations(str, start + 1, result);

        // Возвращаем на место (backtracking)
        swap(str[start], str[i]);
    }
}

 //Вспомогательная функция для удобного вызова
vector<string> getAllPermutations(const string& str) {
    vector<string> result;
    if (str.empty()) {
        return result; // Обработка пустой строки
    }

    string mutableStr = str;
    generatePermutations(mutableStr, 0, result);
    return result;
}

void printPermutations(const vector<string>& permutations) {
    cout << " (All permutations:" << permutations.size() << "):" << endl;
    for (size_t i = 0; i < permutations.size(); i++) {
        cout << (i + 1) << ": " << permutations[i] << endl;
    }
}


int main() {
    string input;

    cout << "Enter the string to generate the permutations: ";
    cin >> input;

    // Генерируем все перестановки
    vector<string> permutations = getAllPermutations(input);

    // Выводим результат
    printPermutations(permutations);

    return 0; // Успешное завершение программы
}