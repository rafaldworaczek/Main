/* Task description:
http://main.edu.pl/en/archive/oi/12/ban

This algorithm solves typical change problem but with many coins (banknots)
of the same denomination. The unit array keeps the number of banknots of 
the same denomination. Apart from checking only coins
in [row-1][col] and [row-1][col-coin] algorithms also check, whether we 
can add coin with the same denomination ([row][col-coin]). 
This is only allowed when we still have coins available, for example: 

When we have 4 coins of value 3 and we want to get value 15 (k), then we do
15(col) - 3(coin) = 12 and we verify how many coins of value 3 were used 
to compose value 12. if all 4 coins of value 3 have been used than 
we cannot use [row][col-coin] in this case. 
Array called "used" keeps this information.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define MAX_DENOMINATION 20000

int main() {
  int n = 0, i = 0, k = 0;
  scanf("%d", &n);
  int m = MAX_DENOMINATION;
  int b[n];
  int units[m + 1];
  int num[m + 1];
  int amount;
  int coin = 1;
  int row = 1;
  int col;
  int min;
  int direction;
 
  for (i = 0; i <= m ; i++) {
    units[i] = INT_MAX; 
    num[i] = 0;
  }

  for (i = 0; i < n; i++) {
    scanf("%d", &b[i]);
  }

  for (i = 0; i < n; i++) {
    scanf("%d", &amount);
    units[b[i]] = amount;
  }

  scanf("%d", &k);
  int dp[n+1][k+1];
  int trace[n+1][k+1]; 
  int *used; 

  for (i = 1; i <= k; i++) {
    dp[0][i] = INT_MAX; 
    trace[0][i] = 0;
  }

  for (i = 0; i <= n; i++) {
    dp[i][0] = 0;
    trace[i][0] = 0;
  }

  while (coin <= m) {
   
    if (units[coin] == INT_MAX) { 
      coin++; 
      continue;
    }
 
    used = calloc(m+1, sizeof(int));

    for (i = 1; i <= k; i++) { 
      if (dp[row-1][i-coin] != INT_MAX && (i-coin) >= 0) {
        if (dp[row-1][i-coin] < dp[row-1][i]) {
	  min = dp[row-1][i-coin] + 1;
	  direction = -1;
	}
	else { 
	  direction = 1;
	  min = dp[row-1][i];
	}
      }
      else {
	min = dp[row-1][i];
	direction = 1;
      }

      if (dp[row][i-coin] != INT_MAX) {
        if ((i-coin) >= 0 && (dp[row][i-coin] + 1 < min))  {
          if (units[coin] > used[i-coin] + 1) {    	 	
	    used[i] = used[i-coin] + 1;  
	    min = dp[row][i-coin] + 1;
	    direction = 2;
 	  }
        }
      }
      dp[row][i] = min;
      trace[row][i] = direction;
    }
    free(used);
	
    coin++;
    row++;
  } 

  row = n;
  col = k;
  while (row != 0 && col != 0) {
    coin = b[row-1];
    if (trace[row][col] == 2) { 
      col = col - coin; 
      num[coin]++; 
      continue;
    }

    if (trace[row][col] == 1) { 
      row = row - 1; 
      continue;
    }

    if (trace[row][col] == -1) { 
      row = row - 1; 
      col = col - coin; 
      num[coin]++; 
    }
  }
 
  printf("%d\n", dp[n][k]);
  for (i = 0; i < n; i++) { 
     printf("%d ", num[b[i]]);
  }
  printf("\n");  
  return 0; 
}
 
