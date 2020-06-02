import sys
import cmath
import numpy
import pandas as pd
from pandas import *

def Vandermonde(vector_x):
    vector_x
    vandermonde_matrix = []
    pow = len(vector_x) -1
    for element in vector_x:
        vandermonde_matrix.append([])
        for index in range(pow+1):
            vandermonde_matrix[-1].append(element[0]**index)
    return vandermonde_matrix

def MatrixInverse(m):
    determinant = Determinant(m)
    #special case for 2x2 matrix:
    if len(m) == 2:
        return [[complex(numpy.around(m[1][1]/determinant,4)), complex(numpy.around(-1*m[0][1]/determinant,4))],
		[complex(numpy.around(-1*m[1][0]/determinant,4)), complex(numpy.around(m[0][0]/determinant,4))]]
    #find matrix of cofactors
    cofactors = []
    for r in range(len(m)):
        cofactorRow = []
        for c in range(len(m)):
            minor = MinorMatrix(m,r,c)
            cofactorRow.append(   complex(numpy.around(((-1)**(r+c)) * Determinant(minor), 4))   )
        cofactors.append(cofactorRow)
    cofactors = Transpose(cofactors)
    for r in range(len(cofactors)):
        for c in range(len(cofactors)):
            cofactors[r][c] = cofactors[r][c]/determinant
    return cofactors

def Transpose(original_matrix):
    n_rows = len(original_matrix)
    n_columns = len(original_matrix[0])
    transposed_matrix = []
    # Given a matrix of n x m dimensions, creates a null matrix with m x n dimensions
    for column in range(n_columns):
        transposed_matrix.append([])
        for row in range(n_rows):
            transposed_matrix[column].append(0)
    # Fills the new empty transposed matrix
    for i in range(n_rows):
        for j in range(n_columns):
            transposed_matrix[j][i] = original_matrix[i][j]
    return transposed_matrix

def MinorMatrix(m,i,j):
    return [row[:j] + row[j+1:] for row in (m[:i]+m[i+1:])]

def Determinant(matrix):
    determinant = 0
    # Calculate determinant with LaPlace method
    indices = list(range(len(matrix)))
    if len(matrix) == 2 and len(matrix[0]) == 2:
        determinant = complex(numpy.around((matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]), 4))
        return determinant
    for fc in indices:
        As = matrix.copy()
        As.pop(0)
        height = len(As)
        for i in range(height):
            As[i] = As[i][0:fc] + As[i][fc+1:]
        signal = (-1) ** (fc % 2)
        sub_det = Determinant(As)
        determinant += complex(numpy.around(signal * matrix[0][fc] * sub_det, 4))
    return determinant

def Mult_Matrix(matrix1, matrix2):
    matrix1_n_rows = len(matrix1)
    matrix1_n_columns = len(matrix1[0])
    matrix2_n_rows = len(matrix2)
    matrix2_n_columns = len(matrix2[0])
    if matrix1_n_columns != matrix2_n_rows:
        print("{} vs {}".format(matrix1_n_columns, matrix2_n_columns))
        print("Not compatible Matrix\n")
        sys.exit()
    result_matrix = []
    # Creates a null matrix with the resultant dimensions
    for column in range(matrix1_n_rows):
        result_matrix.append([])
        for row in range(matrix2_n_columns):
            result_matrix[column].append(0)
    # Mult_Matrix
    for i in range(matrix1_n_rows):
        for k in range(matrix2_n_columns):
            for j in range(matrix2_n_rows):
                result_matrix[i][k] += complex(numpy.around(matrix1[i][j] * matrix2[j][k] , 4))
    return result_matrix

if __name__ == '__main__':
	x = [] #Vandermonde
	with open('Factors.txt', 'r') as f:
		y = [[complex(digit) for digit in line.split()] for line in f]
	#print(y)
	n = int(1 << (len(y) - 2).bit_length())
	for i in range(0 , n):
		x.append([complex(cmath.cos(2*cmath.pi * i / n), cmath.sin((2*cmath.pi * i) / n))])
	pd.DataFrame(y).to_excel('Matrix2.xlsx', header='Matrix2')

	p = Vandermonde(x)
	pd.DataFrame(p).to_excel('Vandermonde.xlsx', header='Vandermonde')
	print("Vandermonde is Ready!\n")

	pIn = MatrixInverse(p)
	pd.DataFrame(pIn).to_excel('Inverse.xlsx', header='Inverse')
	print("Inverse is Ready!\n")

	pId = Mult_Matrix(pIn,p)
	pd.DataFrame(pId).to_excel('Identity.xlsx', header='Identity')
	print("Identity is Ready!\n")

	coeficients = Mult_Matrix(p, y)
	pd.DataFrame(coeficients).to_excel('Coeficients.xlsx', header='Coeficients')
	print('Coefficients Ready!\t')

	excel_names = ["Matrix2.xlsx", "Vandermonde.xlsx", "Inverse.xlsx", "Identity.xlsx",
	"Coeficients.xlsx"]
	# read them in
	excels = [pd.ExcelFile(name) for name in excel_names]
	# turn them into dataframes
	frames = [x.parse(x.sheet_names[0], header=None,index_col=None) for x in excels]
	# delete the first row for all frames except the first
	# i.e. remove the header row -- assumes it's the first
	frames[1:] = [df[1:] for df in frames[1:]]
	# concatenate them..
	combined = pd.concat(frames)
	# write it out
	combined.to_excel("Final.xlsx", index = None)
