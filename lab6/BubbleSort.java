package src;

public class BubbleSort {
    public static int[] bubbleSort(int[] arr) {
        int[] sortedArray = arr.clone(); // Создаем копию чтобы не менять исходный массив
        int n = sortedArray.length;
        
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (sortedArray[j] > sortedArray[j + 1]) {
                    int temp = sortedArray[j];
                    sortedArray[j] = sortedArray[j + 1];
                    sortedArray[j + 1] = temp;
                }
            }
        }
        return sortedArray;
    }
    
    public static void main(String[] args) {
        int[] arr = {64, 34, 25, 12, 22, 11, 90};
        
        System.out.println("Исходный массив: ");
        for (int num : arr) {
            System.out.print(num + " ");
        }
        
        int[] sortedArr = bubbleSort(arr);
        
        System.out.println("\nОтсортированный массив: ");
        for (int num : sortedArr) {
            System.out.print(num + " ");
        }
    }    
}
