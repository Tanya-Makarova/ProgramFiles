def bubbleSort(arr):
    n = len(arr)
    for i in range(n-1): # самый "тяжелый пузырек"
        for j in range(n-i-1): # после каждой итерации внешнего цикла i элемент уже находится в конце массива, и его не нужно проверять снова
            if arr[j] > arr[j+1]:
                arr[j], arr[j+1] = arr[j+1], arr[j]
    return arr

arr = [64, 34, 25, 12, 22, 11, 90]
print('Исходный массив: ', arr)
arr1 = bubbleSort(arr.copy())  # используем copy() чтобы не менять исходный массив
print('Отсортированный массив:', arr1)    
                        
