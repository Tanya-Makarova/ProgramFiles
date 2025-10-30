def Shellsort(arr):
    n = len(arr)
    gap = n//2
    while gap > 0:
        for i in range(gap, n):
            temp = arr[i]
            j = i
            while j >= gap and arr[j - gap] > temp: # проверка что индекс не отрицательный и в начале массива стоит число больше, чем исходное
                    arr[j] = arr[j - gap]
                    j -= gap
            arr[j] = temp
        gap //= 2
    return arr

arr = [12, 34, 54, 2, 3]
print('First array:', arr)
arr1 = Shellsort(arr.copy())
print('Sorted array:', arr1)