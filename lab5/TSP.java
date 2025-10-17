package src;

import java.util.*;

public class TSP {
    public static void main(String[] args) {
        // Матрица расстояний между 6 городами
        int[][] dist = {
            {0, 10, 15, 20, 25, 30},  // Из города 0: мин = 10 (в город 1)
            {10, 0, 35, 25, 30, 20},   // Из города 1: мин = 10 (в город 0) или 20 (в город 5)
            {15, 35, 0, 30, 40, 35},   // Из города 2: мин = 15 (в город 0)
            {20, 25, 30, 0, 15, 10},   // Из города 3: мин = 10 (в город 5)
            {25, 30, 40, 15, 0, 12},   // Из города 4: мин = 12 (в город 5)
            {30, 20, 35, 10, 12, 0}    // Из города 5: мин = 10 (в город 3)
        };
        
        int[] cities = {1, 2, 3, 4, 5}; // Города для перестановки (кроме 0)
        int minDist = Integer.MAX_VALUE;
        int[] bestOrder = cities.clone();
        int counter = 0; // Счетчик перестановок
        System.out.println();
        
        do {
            counter++;
            // Вычисляем длину маршрута: 0 -> перестановка -> 0
            int currentDist = dist[0][cities[0]]; // 0 -> первый город
            
            // Суммируем расстояния между городами в перестановке
            for(int i = 0; i < cities.length - 1; i++) {
                currentDist += dist[cities[i]][cities[i+1]];
            }
            
            // Добавляем расстояние от последнего города обратно в 0
            currentDist += dist[cities[cities.length-1]][0];
            
            if(currentDist < minDist) {
                minDist = currentDist;
                bestOrder = cities.clone();
                
                // Выводим каждый улучшенный маршрут
                System.out.println("Найден улучшенный маршрут: " + currentDist);
                System.out.print("0");
                for(int city : bestOrder) {
                    System.out.print(" → " + city);
                }
                System.out.println(" → 0");
            }
        } while(nextPermutation(cities));
        
        System.out.println("\nВсего проверено перестановок: " + counter);
        System.out.println("Минимальное расстояние: " + minDist);
        System.out.print("Оптимальный маршрут: 0");
        for(int city : bestOrder) {
            System.out.print(" → " + city);
        }
        System.out.println(" → 0");
        
        // Детальная проверка
        System.out.println("\nДетальная проверка:");
        int total = 0;
        System.out.println("0 → " + bestOrder[0] + ": " + dist[0][bestOrder[0]]);
        total += dist[0][bestOrder[0]];
        
        for(int i = 0; i < bestOrder.length - 1; i++) {
            System.out.println(bestOrder[i] + " → " + bestOrder[i+1] + ": " + 
                             dist[bestOrder[i]][bestOrder[i+1]]);
            total += dist[bestOrder[i]][bestOrder[i+1]];
        }
        
        System.out.println(bestOrder[bestOrder.length-1] + " → 0: " + 
                         dist[bestOrder[bestOrder.length-1]][0]);
        total += dist[bestOrder[bestOrder.length-1]][0];
        
        System.out.println("Общая сумма: " + total);
        
        // Проверим ваш маршрут отдельно
        System.out.println("\nПроверка маршрута 0 → 1 → 5 → 4 → 3 → 2 → 0:");
        int yourRoute = dist[0][1] + dist[1][5] + dist[5][4] + dist[4][3] + dist[3][2] + dist[2][0];
        System.out.println("0→1: " + dist[0][1] + " + 1→5: " + dist[1][5] + " + 5→4: " + dist[5][4] + 
                          " + 4→3: " + dist[4][3] + " + 3→2: " + dist[3][2] + " + 2→0: " + dist[2][0] + 
                          " = " + yourRoute);
    }
    
    public static boolean nextPermutation(int[] array) {
        int i = array.length - 2;
        while (i >= 0 && array[i] >= array[i + 1]) i--;
        if (i < 0) return false;
        
        int j = array.length - 1;
        while (array[j] <= array[i]) j--;
        
        int temp = array[i];
        array[i] = array[j];
        array[j] = temp;
        
        for(int k = i + 1, l = array.length - 1; k < l; k++, l--) {
            temp = array[k];
            array[k] = array[l];
            array[l] = temp;
        }
        return true;
    }
}