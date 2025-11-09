def bead_sort(arr):
    if not arr:
        return arr    
    # Находим максимальное значение для определения размера "абаки"
    max_val = max(arr)
    
    # Создаем "абак" - матрицу, где каждая строка представляет число бусин
    beads = [[0] * len(arr) for i in range(max_val)]
    
    # Расставляем бусины (единицы) в соответствии с входным массивом
    for i in range(len(arr)):
        for j in range(arr[i]):
            beads[j][i] = 1
    
    print("Исходное расположение бусин:")
    print_beads(beads)
    
    # Моделируем "падение" бусин под действием гравитации
    for i in range(len(beads)):
        
        bead_count = sum(beads[i]) # Считаем количество бусин в каждом ряду
                
        for j in range(len(arr)): # "Сбрасываем" все бусины в ряду
            beads[i][j] = 0
        
        # Бусины оседают в начале ряда (левая сторона)
        for j in range(len(arr) - bead_count, len(arr)):
            beads[i][j] = 1
    
    print("После 'падения' бусин:")
    print_beads(beads)
    
    # Считываем результат - подсчитываем бусины в каждом столбце
    result = [0] * len(arr)
    for i in range(len(arr)):
        for j in range(max_val):
            result[i] += beads[j][i]
    
    return result

def print_beads(beads):
    """Вспомогательная функция для визуализации бусин"""
    for row in beads[::-1]:  # Выводим сверху вниз
        print(' '.join('●' if x else '○' for x in row))

# Тестирование
if __name__ == "__main__":
    # Примеры
    test_arrays = [
        [3, 1, 4, 1, 5],
        [2, 34, 5, 43, 55, 56, 74, 3, 4, 1, 5],
        [5, 3, 8, 1, 2],
        [1, 1, 1, 1],
        [7, 2, 0, 4]
    ]
    
    for i, arr in enumerate(test_arrays):
        print(f"\nПример {i+1}:")
        print(f"Исходный массив: {arr}")
        
        try:
            sorted_arr = bead_sort(arr)
            print(f"Отсортированный: {sorted_arr}")
            
            # Проверка корректности
            expected = sorted(arr)
            print(f"Корректность: {sorted_arr == expected}")
            
        except ValueError as e:
            print(f"Ошибка: {e}")