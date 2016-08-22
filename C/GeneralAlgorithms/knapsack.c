/*Task description: 
  This is solution for knapsack problem using dynamic programming.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

unsigned long int knapsack(unsigned long int size,
			    unsigned long int n,
	     		    unsigned long int *val,
	      		    unsigned long int *w) 
{
  unsigned long int kp[n+1][size+1];
  unsigned long int i, j;

  for (i = 0; i <= size; i++)
    kp[0][i] = 0;    

  for (i = 0; i <= n; i++)
    kp[i][0] = 0;    

  for (i = 1; i <= n; i++) {
    for (j = 1; j <= size; j++) {
      kp[i][j] = MAX((j - w[i-1] >= 0)? (kp[i-1][j-w[i - 1]] + val[i-1]):0, 
		      kp[i-1][j]); 
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
  unsigned long int n, size, i;
  scanf("%lu %lu", &size, &n);
  unsigned long int val[n];
  unsigned long int weight[n];
  for (i = 0; i < n; i++) 
    scanf("%lu %lu", &val[i], &weight[i]);

  printf("Max val: %lu\n", knapsack(size, n, val, weight));
  return 0; 
}
 

