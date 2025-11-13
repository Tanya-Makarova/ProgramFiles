def TernarySearch(arr, start, end, x):
    while end - start > 2:  # пока в интервале больше 3 элементов
        mid1 = start + (end - start) // 3
        mid2 = end - (end - start) // 3
        
        if arr[mid1] < arr[mid2]:
            start = mid1
        else:
            end = mid2
    
    # Поиск максимума среди оставшихся элементов
    max_val = arr[start]
    max_index = start
    for i in range(start + 1, end + 1):
        if arr[i] > max_val:
            max_val = arr[i]
            max_index = i
    return max_index

# демонстрация работы
arr = [1, 3, 4, 15, 23, 44, 64, 65, 76, 86, 88, 99, 123]
target = 123
print("Исходный массив:", arr)
print("Искомое значение:", target)

result = TernarySearch(arr, 0, len(arr)-1, target)

if result != -1:
    print(f"Элемент найден: индекс = {result}, значение = {arr[result]}")
else:
    print("Элемент не найден")