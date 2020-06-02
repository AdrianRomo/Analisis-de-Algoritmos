#include <stdio.h>
#include <stdlib.h>
int multiply(int, int);
int main() {
  int x = 0, y = 0;
  scanf("%d",&x);
  scanf("%d",&y);
  printf("%d\n",multiply(x,y));
  return 0;
}

int multiply(int x, int y){
  int z;
  if (y == 0) return 0;
  z = multiply(x,abs(y/2));
  if (y % 2 == 0) return 2 * z;
  else return x + (2 * z);
}
