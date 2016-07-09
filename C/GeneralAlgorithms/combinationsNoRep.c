#include <stdio.h>
#include <stdlib.h>

//Number of combinations without repetition: n! / k! (n - k)!

void printCombination(int idx, int *tmpA) {
   int i;
   for (i = 0; i < idx; i++) 
     printf("%d", tmpA[i]);
   printf("\n"); 
}

int permute(int s, int k, int n, int idx, int *tmpA) {
  int i;
  int nr = 0;

  if (idx == k) {
    printCombination(idx, tmpA);
    return 1; 
  } 

  for (i = s; i <= n; i++) {
     tmpA[idx++] = i;
     nr += permute(i + 1, k, n, idx, tmpA);
     idx--;
  }
  
  return nr;
}

int main() {
  int k, n;

  printf("Enter k: ");
  scanf("%d", &k);

  printf("Enter n: ");
  scanf("%d", &n);

  if (k <= 0) {
     printf("Wrong k value\n");
     return 0;
  }

  if (n <= 0) {
     printf("Incorrect n value\n");
     return 0;
  }

  if (k > n) {
     printf("Incorrect k value\n"); 
     return 0;
  }

  int tmpA[k];

  printf("Number of combinations: %d\n", permute(1, k, n, 0, tmpA));
}
