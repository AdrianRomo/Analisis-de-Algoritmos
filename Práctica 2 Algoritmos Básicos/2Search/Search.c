#include <stdio.h>
#include <stdlib.h>

int findMaxBinary(int numbers[], int first, int last){ //Complexity O(log n)
  if (first == last) return numbers[first];
  /* If there are two elements and first is greater then the first element is Max */
  if ((last == first + 1) && numbers[first] >= numbers[last])   return numbers[first];
  /* If there are two elements and second is greater then the second element is Max */
  if ((last == first + 1) && numbers[first] < numbers[last])    return numbers[last];
  int mid = (first + last)/2;   /*first + (last - first)/2;*/
  /* If we reach a point where numbers[mid] is greater than both of its adjacent elements numbers[mid-1] and numbers[mid+1], then numbers[mid] is the Max element*/
  if (numbers[mid] > numbers[mid + 1] && numbers[mid] > numbers[mid - 1]) return numbers[mid];
  /* If numbers[mid] is greater than the next element and smaller than the previous element then Max lies on left side of mid */
  if (numbers[mid] > numbers[mid + 1] && numbers[mid] < numbers[mid - 1])   return findMaxBinary(numbers, first, mid - 1);
  /* when numbers[mid] is greater than numbers[mid-1] and smaller than numbers[mid+1]*/
  else return findMaxBinary(numbers, mid + 1, last);
}

int findMaxLinear(int numbers[], int first, int last){ //Complexity O(n)
  int max = numbers[first], i;
  /* break when once an element is smaller than the max then it will go on
  decreasing and no need to check after that*/
  for (i = first + 1; i <= last; i++){
    if (numbers[i] > max) max = numbers[i];
    else break;
  }
  return max;
}
int main(){
  FILE *file = fopen("Search.txt", "r");
  int *numbers = malloc(4000 * sizeof *numbers);
  int i = 0;
  int num;
  while(fscanf(file, "%d, ", &num) > 0) {
    numbers[i] = num;
    i++;
  }
  fclose(file);
  printf("\nThe Max element with Linear Search is %d\n", findMaxLinear(numbers, 0, i - 1));
  printf("\nThe Max element with Binary Search is %d\n", findMaxBinary(numbers, 0, i - 1));
  return 0;
}
