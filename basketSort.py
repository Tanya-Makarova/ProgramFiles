# Пусть по условию значения массива не превышают 100
# Разделим значения на 4 корзины 
import time

def basket(arr, k):
    b = [[] for i in range(k)]
    n = max(arr)
    for i in range(len(arr)):
        if arr[i] <= n//k:
            b[0].append(arr[i])
        elif (arr[i] > n//k) and (arr[i] <= 2*(n//k)):
            b[1].append(arr[i])
        elif arr[i] > 2*(n//k) and arr[i] <= 3*(n//k):
            b[2].append(arr[i])
        else:
            b[3].append(arr[i])
    return b

# Универсальный способ - для любого числа корзин
# def basket(arr, k):
#     if k <= 0:
#         return [[]]
    
#     b = [[] for _ in range(k)]
#     min_val = min(arr)
#     max_val = max(arr)
    
#     if min_val == max_val:
#         b[0] = arr.copy()
#         return b
    
#     interval_size = (max_val - min_val) / k
    
#     for num in arr:
#         index = min(int((num - min_val) / interval_size), k - 1)
#         b[index].append(num)
    
#     return b

def insertionSort(arr):
    for i in range(1, len(arr)):
        key = arr[i]
        j = i - 1
        while j >= 0 and arr[j] > key:
            arr[j+1] = arr[j]
            j -= 1
        arr[j+1] = key
    return arr

arr = [1, 3, 43, 54, 33, 22, 67, 90, 100, 2, 35, 26, 87, 75, 15, 23]
print('Исходный список',arr)

start_time = time.time()

k = 4
basket_z = basket(arr, k)
arr1 = [insertionSort(a) for a in basket_z]

end_time = time.time()
execution_time = end_time - start_time

print('Отсортированный список', sum(arr1, []))
print(execution_time) # Время, ушедшее на выполнение алгоритма

# Лучший случай: O(n + k) - когда элементы равномерно распределены

# Средний случай: O(n + n²/k + k)

# Худший случай: O(n²) - когда все элементы попадают в одну корзину
