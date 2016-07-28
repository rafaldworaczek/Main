/*
Task:
  Imagine a robot sitting on the upper left hand corner of an NxM grid. 
The robot can only move in two directions: right and down. How many possible paths are there for the robot?

Input: 
 first line: N
 second line: M

Output: Programs print all paths, and number of paths
*/

#include <stdio.h>
#include <stdlib.h>

void printPath(int idx, int *stack) {
  int i;
  for (i = 0; i < idx; i++) 
    printf("%d ", stack[i]);
  printf("\n");
}

//robot can only move down or right
void Paths(int nr, int w, int h, int idx, int *stack, int *countp) {
  int i;

  stack[idx++] = nr;

  if ((nr % w) != 0) {
    Paths(nr + 1, w, h, idx, stack, countp);
  }

  if (nr <= (w * (h - 1))) 
    Paths(nr + w, w, h, idx, stack, countp);
  
  if ((idx) == w + h - 1) {
    printPath(idx, stack); 
    *countp += 1;
  }

  idx--;
}

int main() {
  int w, h, idx = 0;
  int countp = 0;
  
  printf("Type size of grid: \n");
  printf("Width: ");
  scanf("%d", &w);
  printf("Height: ");
  scanf("%d", &h);
  int stack[w + h -1];

  Paths(1, w, h, idx, stack, &countp);
  printf("Number of paths %d\n", countp);  
	
  return 0; 
}
 
