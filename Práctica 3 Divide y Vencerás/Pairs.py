# Return count of pair in given array
# such that i*arr[i] > j*arr[j]
def CountPair(arr , n ):
    # Initialize result
    result = 0;
    for i in range (0, n):
        # Generate all pair and increment
        # counter if the hold given condition
        j = i + 1
        while(j < n):
            if (arr[i] > (2 * arr[j])):
                result = result +1
            j = j + 1
    return result;

if __name__ == "__main__":
    arr = list(map(int, input().split(",")))
    n = len(arr)
    print("Count of Pairs : " , CountPair(arr, n))
