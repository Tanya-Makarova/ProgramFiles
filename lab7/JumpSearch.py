import math

def JumpSearch(arr, x):
    n = len(arr)
    step = int(math.sqrt(n))
    pred = 0 # предыдущий индекс
    while pred < n and arr[min(step, n) - 1] < x:
        print(f"Прыгаем на индекс {min(step, n) - 1}, значение {arr[min(step, n) - 1]}")
        pred = step
        step += int(math.sqrt(n))
        if pred >= n:
            return -1 # eсли выходим за границы — не найден
    
    print(f"Выполняем линейный поиск от {pred} до {min(step, n) - 1}")
    for i in range(pred, min(step, n)):
        print(f"Проверяем индекс {i}, значение {arr[i]}")
        if arr[i] == target:
            return i
    return -1

# Демонстрация работы
arr = [1, 3, 4, 64, 65, 76, 86, 88, 99, 123]
target = 123
print("Исходный массив:", arr)
print("Искомое значение:", target)

result = JumpSearch(arr, target)

if result != -1:
    print(f"Элемент найден: индекс = {result}, значение = {arr[result]}")
else:
    print("Элемент не найден")
