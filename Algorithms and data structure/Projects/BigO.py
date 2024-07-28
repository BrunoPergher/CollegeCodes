from bigO import BigO
from random import randint

def quickSort(array):  # in-place | not-stable
    """
    Best : O(nlogn) Time | O(logn) Space
    Average : O(nlogn) Time | O(logn) Space
    Worst : O(n^2) Time | O(logn) Space
    """
    if len(array) <= 1:
        return array
    smaller, equal, larger = [], [], []
    pivot = array[randint(0, len(array) - 1)]
    for x in array:
        if x < pivot:
            smaller.append(x)
        elif x == pivot:
            equal.append(x)
        else:
            larger.append(x)
    return quickSort(smaller) + equal + quickSort(larger)


lib = BigO()
complexity = lib.test(quickSort, "random")
complexity = lib.test(quickSort, "sorted")
complexity = lib.test(quickSort, "reversed")
complexity = lib.test(quickSort, "partial")
complexity = lib.test(quickSort, "Ksorted")

''' Result
Running quickSort(random array)...
Completed quickSort(random array): O(nlog(n))

Running quickSort(sorted array)...
Completed quickSort(sorted array): O(nlog(n))

Running quickSort(reversed array)...
Completed quickSort(reversed array): O(nlog(n))

Running quickSort(partial array)...
Completed quickSort(partial array): O(nlog(n))

Running quickSort(Ksorted array)...
Completed quickSort(ksorted array): O(nlog(n))
'''