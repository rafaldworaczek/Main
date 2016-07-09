/*
##########################################################################
# This program shows all permutations of given array (arr).		 #   
# You can modify arr and nr variables. The number of permutations is nr! #
##########################################################################
*/

#include <stdio.h>
#include <stdlib.h>

//Variables to modify
int arr[] = {3, 5, 8, 4};
int nr = 4;

void printfStack(int *stack, int nr) {
  int i;

  for (i = 0; i < nr; i++)
     printf("%d", stack[i]);
  printf("\n");
}

void perm(int *a, int nr, int *stack, int *marked, int idx) {
  int i; 

  if (idx == nr) {
    printfStack(stack, nr);
    return;
  }

  for (i = 0; i < nr; i++) {
    if (!marked[i]) {
      marked[i] = 1;
      stack[idx++] = a[i];
      perm(a, nr, stack, marked, idx);
      idx--;
      marked[i] = 0;
    }  
  }
}

int main() {
  int i;
  int idx;
  int marked[nr];
  int stack[nr];

  for (i = 0; i < nr; i++)
    marked[i] = stack[i] = 0;

  perm(arr, nr, stack, marked, idx);
}
