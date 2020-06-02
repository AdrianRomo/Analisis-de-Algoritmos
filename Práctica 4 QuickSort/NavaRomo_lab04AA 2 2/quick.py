import random
import time
from numpy.random import seed
from numpy.random import randint

def quicksort(quicktype, array, i, j, comparisonCount):
    if i >= j:
        return array
    #First Pivot i
    if quicktype == 1:
        pivot, comps = partition(array, i, j, i)
        comparisonCount = comparisonCount + comps
    #Last Pivot j
    if quicktype == 2:
        pivot, comps = partition(array, i, j, j)
        comparisonCount = comparisonCount + comps
    #Random Pivot sending a number between i, j
    if quicktype == 3:
        pivot, comps = partition(array, i, j, random.randint(i, j))
        comparisonCount = comparisonCount + comps

    quicksort(quicktype, array, i, pivot - 1, comparisonCount)
    quicksort(quicktype, array, pivot + 1, j, comparisonCount)
    return comparisonCount

def partition(array, i, j, pivot):
    array[j], array[pivot] = array[pivot], array[j]
    stored_index = i
    comps = 0 #Initializating the comparisons
    for i in range(i, j):
        if array[i] < array[j]:
            #Couting the Comparisons
            comps += 1
            array[stored_index], array[i] = array[i], array[stored_index]
            stored_index += 1
    array[j], array[stored_index] = array[stored_index], array[j]
    return stored_index, comps

def quickchoose(Limit, InferiorRand, SuperiorRand):
    seed(1)
    A = randint(InferiorRand, SuperiorRand, Limit)
    B = C = A
    print("Original Array: ", A, "\n")
    for k in range (3):
        if k == 0:
            start = time.process_time()
            comps = quicksort(k + 1, A, 0, len(A) - 1, 0)
            print("Sorted Array with First Pivot: ", A, "\n", comps, "\n")
            print("Elapsed time: ",time.process_time() - start)

        if k == 1:
            print("Original Array: ", B, "\n")
            start = time.process_time()
            comps = quicksort(k + 1, B, 0, len(B) - 1, 0)
            print("Sorted Array with Last Pivot: ", B, "\n", comps, "\n")
            print("Elapsed time: ",time.process_time() - start)

        if k == 2:
            print("Original Array: ", C, "\n")
            start = time.process_time()
            comps = quicksort(k + 1, C, 0, len(C) - 1, 0)
            print("Sorted Array with Random Pivot: ", C, "\n", comps, "\n")
            print("Elapsed time: ",time.process_time() - start)

if __name__ == '__main__':
    Limit = int(input("Insert Limit of the Array:\t"))
    InferiorRand = int(input("Insert Inferior Limit:\t"))
    SuperiorRand = int(input("Insert Superior Limit:\t"))
    quickchoose(Limit, InferiorRand, SuperiorRand)
