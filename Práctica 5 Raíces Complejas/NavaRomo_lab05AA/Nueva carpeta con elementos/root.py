import cmath

def nth_root(num, r):
    print("\n")
    base = num ** (1.0/r)
    roots = [base]
    for i in range(0, r):
        rooot = complex(base * cmath.cos(2*cmath.pi * i / r), base * cmath.sin(2*cmath.pi * i / r,))
        if i == 0: print("Principal Root: ", rooot)
        else: roots.append(print(i+1,rooot))
    print("\n")
    power(roots)

def power(roots):
    rais = []
    pow = int(input("Insert power: "))
    for i in range(1, pow+1):
        rais.append(print(roots[0],"^",i,"=",complex(roots[0] ** i)))
    print("\n")

if __name__ == '__main__':
    num = int(input("Insert Number "))
    root = int(input("Insert Root "))
    nth_root(num,root)

    # TODO Join Fourier.py with Root.py
    #      Accept Documents
    #      Have more Fun
