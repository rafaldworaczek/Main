/*Task description: 
http://main.edu.pl/en/archive/oi/10/mas
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_CHARS 10

void printBuff(int *buff, int size) {
  int i;
  for (i = 0; i < size; i++) 
    printf("%d ", buff[i]);
  printf("\n");
}

int checkDigits(int *buff, int size, int c, int **digits) {
  int i, k, row;
  int *mark = calloc(MAX_CHARS, sizeof(int));
  int A, B; 
  int sumA = 0;
  int sumB = 0;

  for (i = 0; i < size; i++) {
    mark[buff[i]] = i + 1;
  }

  for (row = 0; row < c; row++) {
    A = digits[row][0];
    B = digits[row][1];

    for (k = 2; k < c + 2; k++) {
      if (!mark[digits[row][k]]) continue;
      if (mark[digits[row][k]] == k - 1) 
	sumA += digits[row][k]; 
      else 
	sumB += digits[row][k];
    }

    if (sumA != A || sumB != B) {
      free(mark);
      return -1;
    }

    sumA = sumB = 0;
  }

  free(mark);
  return 1;
}

int permute(int size, int *marked, int *buff, int idx, int c, int **digits) {
  int i; 

  if (idx == size) {
     if (checkDigits(buff, size, c, digits) == 1) {
	printBuff(buff, size); 
	return 1;
     }
     return 0;
  }

  for (i = 1; i < MAX_CHARS; i++) {
     if (!marked[i]) {
       marked[i] = 1;
       buff[idx++] = i;
       if (permute(size, marked, buff, idx, c, digits))
	 return 1;
       idx--;
       marked[i] = 0;
     }
  }

  return 0;
}


int main() {
  int c, i, j;
  scanf("%d", &c);
  int *marked = calloc(MAX_CHARS, sizeof(int));
  int *buff = calloc(c, sizeof(int));
  int idx = 0;
  int **digits;
  digits = (int **) malloc(c * sizeof(int *));

  for (i = 0; i < c; i++) 
    digits[i] = (int *) malloc((c + 2) * sizeof(int));   

  for (i = 0; i < c; i++) 
    for (j = 0; j < c + 2; j++) 
      scanf("%d", &digits[i][j]);

  permute(c, marked, buff, idx, c, digits); 

  for (i = 0; i < c; i++)
    free(digits[i]);
  free(digits);
  free(marked);
  free(buff);

  return 0; 
}
