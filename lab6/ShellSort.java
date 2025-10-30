package src;

import java.util.Arrays;

public class ShellSort {
    public static void shellSort(int[] arr) {
        int n = arr.length;
        int gap = n / 2;
        
        while (gap > 0) {
            for (int i = gap; i < n; i++) {
                int temp = arr[i];
                int j = i;
                
                while (j >= gap && arr[j - gap] > temp) {
                    arr[j] = arr[j - gap];
                    j -= gap;
                }
                arr[j] = temp;
            }
            gap /= 2;
        }
    }
    
    public static void main(String[] args) {
        int[] arr = {12, 34, 54, 2, 3};
        
        System.out.println("First array: " + Arrays.toString(arr));
        
        int[] arrCopy = arr.clone(); // Создаем копию чтобы не менять исходный массив
        shellSort(arrCopy);
        
        System.out.println("Sorted array: " + Arrays.toString(arrCopy));
    }    
}
