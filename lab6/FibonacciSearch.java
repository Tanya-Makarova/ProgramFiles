package src;

import java.util.Arrays;

public class FibonacciSearch {
    
    public static int fibonacciSearch(int[] arr, int x) {
        int n = arr.length;
        
        // Находим наименьшее число Фибоначчи, большее или равное n
        int fib_m2 = 0;  // (m-2)'е число Фибоначчи
        int fib_m1 = 1;  // (m-1)'е число Фибоначчи
        int fib_m = fib_m2 + fib_m1;
        
        // Находим m такое, что F[m] >= n
        while (fib_m < n) {
            fib_m2 = fib_m1;
            fib_m1 = fib_m;
            fib_m = fib_m2 + fib_m1;
        }
        
        // Маркеры для элементов, которые не входят в массив
        int offset = -1;
        
        // Поиск
        while (fib_m > 1) {
            // Проверяем возможный индекс
            int i = Math.min(offset + fib_m2, n - 1);
            
            // Если x больше элемента, переходим к правому подмассиву
            if (arr[i] < x) {
                fib_m = fib_m1;
                fib_m1 = fib_m2;
                fib_m2 = fib_m - fib_m1;
                offset = i;
            }
            // Если x меньше элемента, переходим к левому подмассиву
            else if (arr[i] > x) {
                fib_m = fib_m2;
                fib_m1 = fib_m1 - fib_m2;
                fib_m2 = fib_m - fib_m1;
            }
            // Элемент найден
            else {
                return i;
            }
        }
        
        // Проверяем последний элемент
        if (fib_m1 != 0 && offset + 1 < n && arr[offset + 1] == x) {
            return offset + 1;
        }
        
        return -1;  // Элемент не найден
    }
    
    public static void main(String[] args) {
        int[] arr = {10, 22, 35, 40, 45, 50, 80, 82, 85, 90, 100};
        int x = 85;
        
        int result = fibonacciSearch(arr, x);
        
        if (result != -1) {
            System.out.println("Элемент найден на позиции: " + result);
        } else {
            System.out.println("Элемент не найден");
        }
    }
}