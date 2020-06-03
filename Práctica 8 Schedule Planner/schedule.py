# -*- coding: utf-8 -*-
import sys

def ScheduleSelect(a, s, f, n):
  A = [0] * n
  A[1] = a[1]
  k = 1
  iter = 1
  for i in range(2, n+1):
    if(s[i] >= f[k]):
      #appending list A
      iter = iter + 1
      A[iter] = a[i]
      k = i
  # A[0] = iter just to know the length of the list when used in different function.
  A[0] = iter;
  return A
"""
The algorithm is taking a theta(n) running time, where n is the number of activities.
Also if the arrays passed to the function are not sorted, we can sort them in O(nlgn) time.
"""
if __name__ == '__main__':
    a = s = f = []
    fp = open("schedule.txt")
    for i, line in enumerate(fp,1):
        if i == 3:
            a = line.split(', ')
        elif i == 5:
            s = line.split(', ')
        elif i == 7:
            f = line.split(', ')
        elif i > 8:
            break
    fp.close()

    p = ScheduleSelect(a, s, f, len(a) - 1)

    original_stdout = sys.stdout # Save a reference to the original standard output
    with open('Output.txt', 'w') as file:
        sys.stdout = file # Change the standard output to the file we created.
        print('Best Schedule: ')
        print('Activity','\t:   ','Beggining',' -    ','End')
        #p[0] is the length upto which activities are stored
        for i in range(1, p[0]+1):
            print('\t',int(p[i]), '\t:\t', int(s[int(p[i])]), '\t-\t' + f[int(p[i])], end = '\n')
        sys.stdout = original_stdout # Reset the standard output to its original value
        fp.close()
