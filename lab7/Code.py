def binarySearch(arr, start, end, x):
    while start <= end:
        mid = start + (end - start) // 2 # находим середину диапазона
        print(f"Проверим индекс {mid}, значение которого {arr[mid]}")
        if arr[mid] == x:  # если нашли — возвращаем индекс
            return mid
        if arr[mid] < x:  # если значение меньше — идём вправо
            start = mid + 1
        else:
            end = mid - 1  # иначе — влево
    return -1   

def exponentialSearch(arr, x):
    n = len(arr)    
    if n == 0:
        return -1
    if arr[0] == x:
        return 0
    
    step = 1
    while step < n and arr[step] <= x:
        print(f"Расширяем экспоненциально диапазон: i = {step}, значение = {arr[step]}")
        step *= 2   # увеличиваем шаг экспоненциально, пока не превысим элемент
        if step >= n:  # защита от выхода за границы
            break
            
    # безопасные границы:
    left = step // 2
    right = min(step, n - 1)  # гарантированно находимся в пределах [0, n-1]
    
    print(f"Выполняем бинарный поиск от {left} до {right}")
    return binarySearch(arr, left, right, x)

# демонстрация работы
arr = [1, 3, 4, 15, 23, 44, 64, 65, 76, 86, 88, 99, 123]
target = 123
print("Исходный массив:", arr)
print("Искомое значение:", target)

result = exponentialSearch(arr, target)

if result != -1:
    print(f"Элемент найден: индекс = {result}, значение = {arr[result]}")
else:
    print("Элемент не найден")