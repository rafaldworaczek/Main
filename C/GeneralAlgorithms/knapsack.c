/*Task description: 
  This is solution for knapsack problem using dynamic programming.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

int knapsack(int size,
 		    	   int n,
  	     		   int *v,
	      		   int *w) 
{
  int kp[n+1][size+1];
  int i, j;

  for (i = 0; i <= size; i++)
    kp[0][i] = 0;    

  for (i = 0; i <= n; i++)
    kp[i][0] = 0;    

  for (i = 1; i <= n; i++) {
    for (j = 1; j <= size; j++) {
      if ((j - w[i-1]) >= 0) 
        kp[i][j] = MAX(kp[i-1][j-w[i - 1]] + v[i-1], kp[i-1][j]); 
      else
        kp[i][j] = kp[i-1][j]; 
    }
  }

  return kp[n][size];
}

/*Input file format
[knapsack_size] [nr_of_items]
[val_of_item_1] [weight_of_item_1]
[val_of_item_2] [weight_of_item_2]
.
.
.
[val_of_item_n] [weight_of_item_n]
*/
 
int main() {
  int n, size, i;
  scanf("%d %d", &size, &n);
  int val[n];
  int weight[n];
  for (i = 0; i < n; i++) 
    scanf("%d %d", &val[i], &weight[i]);

  printf("Max val: %d\n", knapsack(size, n, val, weight));
  return 0; 
}
 

