def Insertion_Sort(arr):
    for i in range(1, len(arr)):
        j = i -1
        key = arr[i]
        while j >= 0 and arr[j] > key:
            arr[j + 1] = arr[j]
            j = j - 1
        arr[j + 1] = key
    return arr

arr = [12, 11, 13, 5, 6]
arr1 = Insertion_Sort(arr)
print('Исходный массив:', arr)
print('Отсортированный массив:', arr1)
