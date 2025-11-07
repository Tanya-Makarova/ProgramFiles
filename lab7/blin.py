def blin(arr):
    arr = arr.copy()

    for i in range(len(arr)-1, 0, -1): # Проходим по массиву от конца к началу
        max_idx = arr.index(max(arr[:i+1]))
        if max_idx != i:
            # Переворачиваем часть до максимального элемента, чтобы он оказался в начале
            if max_idx != 0:
                arr[:max_idx+1] = arr[:max_idx+1][::-1]

            arr[:i+1] = arr[:i+1][::-1]
    return arr
    

a = [2, 34, 5, 43, 55, 56, 74, 3, 4, 1, 5]
a1 = blin(a)
print(a1)
