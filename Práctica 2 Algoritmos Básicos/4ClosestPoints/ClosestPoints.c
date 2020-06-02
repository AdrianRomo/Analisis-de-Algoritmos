#include <float.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

struct Point{
  int x, y;
};

//Complexity O(n^2)
struct Point * ClosestPoints(struct Point P[], int n){
  float currClo = FLT_MAX, dist = 0.0;
  int i, j;
  if ((n < 2) || (P == NULL)){
    fprintf(stderr, "Error: not enough points to find closest pair");
    exit(EXIT_FAILURE);
  }
  struct Point * closestPair = (struct Point *)malloc(2 * (sizeof(struct Point)));
  if (closestPair == NULL){
    fprintf(stderr, "Error: memory allocation failed");
    exit(EXIT_FAILURE);
  }
  for (i = 0; i < n; ++i){
    for (j = i + 1; j < n; ++j){  //sqrt (px - qx)^2 + (py - qy)^2
      dist = sqrt( (P[i].x - P[j].x)*(P[i].x - P[j].x) +
      (P[i].y - P[j].y)*(P[i].y - P[j].y));
      if (dist < currClo){
        currClo = dist;
        closestPair[0] = P[i];
        closestPair[1] = P[j];
      }
    }
  }
  return closestPair;
}

int main(){
  FILE *file = fopen("Coordinates.txt", "r");
  struct Point *coordinates = malloc(4000 * sizeof *coordinates);
  int i = 0;
  int numx, numy;
  while(fscanf(file, " [%d,%d] ,", &numx, &numy) > 0) {
    coordinates[i].x = numx;
    coordinates[i].y = numy;
    i++;
  }
  fclose(file);
  printf("Total coordinates: %d\n", i);
  struct Point *closest = ClosestPoints(coordinates,i) ;
  printf( "Closest Pairs: \n X1[%i] Y1: [%i]\nX2: [%i] Y2: [%i]\n", closest[0].x, closest[0].y, closest[1].x, closest[1].y);
  return 0;
}
