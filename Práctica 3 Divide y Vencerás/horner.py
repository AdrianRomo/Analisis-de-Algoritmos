def horner(poly, n, x):
    result = poly[0]
    for i in range(1, n):
        result = result*x + poly[i]
    return result

if __name__ == "__main__":
	poly = list(map(int, input().split(",")))
	x = int(input("Insert X value: "))
	n = len(poly)
	print("Value of polynomial is " , horner(poly, n, x))
