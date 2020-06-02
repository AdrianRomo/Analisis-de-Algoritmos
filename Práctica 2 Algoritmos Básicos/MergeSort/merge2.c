#include <stdio.h>
#include <stdlib.h>

//Complexity O(n1+n2)
void mergeArrays(int arr1[], int arr2[], int n1, int n2, int arr3[]){
  int i = 0, j = 0, k = 0;
  // Traverse both array
  /* Check if current element of first
  array is smaller than current element
  of second array. If yes, store first
  array element and increment first array
  index. Otherwise do same with second array*/
  while (i < n1 && j < n2){
    if (arr1[i] < arr2[j]) arr3[k++] = arr1[i++];
    else arr3[k++] = arr2[j++];
  }
  // Store remaining elements of first array
  while (i < n1)
  arr3[k++] = arr1[i++];
  // Store remaining elements of second array
  while (j < n2)
  arr3[k++] = arr2[j++];
}
int main(){
  FILE *file1 = fopen("A.txt", "r");
  FILE *file2 = fopen("B.txt", "r");

  int *arr1 = malloc(1000 * sizeof *arr1);
  int *arr2 = malloc(1000 * sizeof *arr2);
  int n1 = 0, n2 = 0;
  int num, num2;
  while(fscanf(file1, "%d,", &num) > 0) {
    arr1[n1] = num;
    n1++;
  }
  while (fscanf(file2, "%d,", &num2) > 0) {
    arr2[n2] = num2;
    n2++;
  }

  int arr3[n1+n2];

  mergeArrays(arr1, arr2, n1, n2, arr3);

  FILE *file3 = fopen("C.txt", "wb");
  fprintf(file3,"Array before Merging\n");
  fprintf(file3, "A: ");
  for (int i = 0; i < n1; i++){
    fprintf(file3, "%d, ", arr1[i]);
  }
  fprintf(file3, "\nB: ");
  for (int i = 0; i < n2; i++){
    fprintf(file3, "%d, ", arr2[i]);
  }
  fprintf(file3, "\nArray after merging\n");
  for (int i = 0; i < n1 + n2; i++){
    fprintf(file3, "%d, ", arr3[i]);
  }
  fclose(file1);
  fclose(file2);
  fclose(file3);
  printf("Check File C.txt\n");
  return 0;
}
