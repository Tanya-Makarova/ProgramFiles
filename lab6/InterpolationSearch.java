package src;

import java.util.Arrays;

public class InterpolationSearch {
    
    public static int interpolationSearch(int[] arr, int lo, int hi, int x) {
        if (lo <= hi && x >= arr[lo] && x <= arr[hi]) {
            int pos = lo + (((hi - lo) * (x - arr[lo])) / (arr[hi] - arr[lo]));            
            // Если цель найдена
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
    
    public static void main(String[] args) {
        int[] arr = {10, 12, 13, 16, 18, 19, 20, 21, 22, 23, 24, 33, 35, 42, 47};
        int x = 18;
        
        int result = interpolationSearch(arr, 0, arr.length - 1, x);
        
        if (result != -1) {
            System.out.println("Элемент найден на позиции: " + result);
        } else {
            System.out.println("Элемент не найден");
        }
    }
}