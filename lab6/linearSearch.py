def linearSearch(arr, n, target):
    for i in range(n):
        if arr[i] == target:
            return i
    return -1
arr = [3, 5, 2, 7, 9, 1, 4]
target = 7
res = linearSearch(arr, len(arr), target)
if res != -1:
    print('Искомое значение найдено на позиции:', res)
else:
    print('Искомое значение не найдено')
