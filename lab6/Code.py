def quick_sort(array, low, high):
    if low < high:
        
        pi = partition(array, low, high) # Индекс разбиения, array[pi] находится на своем месте
        
        # Отсортировать элементы до и после разбиения
        quick_sort(array, low, pi - 1)
        quick_sort(array, pi + 1, high)

def partition(array, low, high):
    # Последний элемент в качестве опорного
    pivot = array[high]
    i = low - 1  # Индекс меньшего элемента
    
    for j in range(low, high):
        # Если текущий элемент меньше или равен опорному
        if array[j] <= pivot:
            i += 1
            # Поменять местами array[i] и array[j]
            array[i], array[j] = array[j], array[i]
    
    # Поменять местами array[i+1] и array[high] (опорный элемент)
    array[i + 1], array[high] = array[high], array[i + 1]
    
    return i + 1

arr = [10, 7, 8, 9, 1, 5]
    
print("Исходный массив:", arr)
    
quick_sort(arr, 0, len(arr) - 1)
    
print("Отсортированный массив:", arr)