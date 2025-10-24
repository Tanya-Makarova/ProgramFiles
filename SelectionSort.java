package src;

import java.util.Arrays;

public class SelectionSort {
    
    public static void selectionSort(int[] arr) {
        // Проходим по всем элементам массива
        for (int i = 0; i < arr.length; i++) {
            // Предполагаем, что первый элемент - минимальный
            int minIndex = i;
            
            // Ищем минимальный элемент в оставшейся части массива
            for (int j = i + 1; j < arr.length; j++) {
                if (arr[j] < arr[minIndex]) {
                    minIndex = j;
                }
            }
            
            // Меняем найденный минимальный элемент с первым элементом в неотсортированной части
            int temp = arr[i];
            arr[i] = arr[minIndex];
            arr[minIndex] = temp;
        }
    }
    
    // Пример использования
    public static void main(String[] args) {
        // Создаем тестовый массив
        int[] testArray = {64, 25, 12, 22, 11};
        
        System.out.println("Исходный массив: " + Arrays.toString(testArray));
        
        // Сортируем массив
        selectionSort(testArray);
        
        System.out.println("Отсортированный массив: " + Arrays.toString(testArray));
    }
}
