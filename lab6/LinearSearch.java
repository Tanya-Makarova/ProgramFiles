package src;

public class LinearSearch {
    
    public static int linearSearch(int[] arr, int n, int target) {
        for (int i = 0; i < n; i++) {
            if (arr[i] == target) {
                return i;
            }
        }
        return -1;
    }
    
    public static void main(String[] args) {
        int[] arr = {3, 5, 2, 7, 9, 1, 4};
        int target = 7;
        
        int res = linearSearch(arr, arr.length, target);
        
        if (res != -1) {
            System.out.println("Искомое значение найдено на позиции: " + res);
        } else {
            System.out.println("Искомое значение не найдено");
        }
    }
}
