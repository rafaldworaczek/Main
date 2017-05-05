/* Task description:
http://main.edu.pl/pl/archive/oi/2/slo
*/

#include <stdio.h>
#include <stdlib.h>

#define FALSE 0 
#define TRUE 1
#define MAX_VALUE 999999

int main() {
  int k, idx = 1;
  int maxLength = 150; 
  char w[maxLength]; 
  int wLength;
  char c;
  int i, j;
  int x;
  int match = FALSE;
  int offset;
  int count = 0;

  while (1) {
    scanf("%c", &c); 
    if (c == '\n') break;
    w[idx++] = c;
  } 
 
  wLength = idx - 1;
  w[idx] = '\0';
  scanf("%d\n", &k);

  long long int dp[wLength + 1][k + 1];
  long long int trace[wLength + 1][k + 1];
  char chain[k + 1][maxLength];
  int *cLength = (int *) calloc(k + 1, sizeof(int));
  int res[k];
  
  for (i = 1; i <= k; i++) {
    idx = 0;
    while (1) {
      scanf("%c", &c); 
      if (c == '\n') break;
      chain[i][idx++] = c;
    }   

    chain[i][idx] = '\0';
    cLength[i] = idx;
  } 

  for (i = 0; i <= wLength; i++) 
    dp[i][0] = 0;
 
  for (i = 0; i <= k; i++) 
    dp[0][i] = 1;
  

  for (i = 1; i <= wLength; i++) {
    for (j = 1; j <= k; j++) {
      offset = 0;
      match = TRUE; 
      for (x = cLength[j] - 1; x >= 0; x--) {
        if (chain[j][x] != w[i - offset]) { 
          match = FALSE;
          break;
        }
        offset++;
      } 	

      if (match) {
        dp[i][j] = dp[i][j-1] + dp[i-cLength[j]][j-1];
	if (dp[i][j-1] != 0)	
          trace[i][j] = -1; 
	else
	  trace[i][j] = cLength[j];
	
	if (dp[i][j] >= MAX_VALUE) 
	  dp[i][j] = 1000000;
      }
      else {
        dp[i][j] = dp[i][j-1];
	trace[i][j] = -1;
      }
    }
  }

  if (dp[wLength][k] == 0) {
    printf("NIE\n");
    return 0;
  }

  printf("%lld\n", dp[wLength][k]);
  i = wLength;
  j = k; 

  while (j > 0 && i > 0) {
    if (trace[i][j] == -1) { 
      j--; 
      continue; 
    }

    res[count++] = j;
    i -= trace[i][j];
    j--;
  }  

  for (i = count - 1; i >= 0; i--) 
    printf("%d\n", res[i]); 

  free(cLength); 
  return 0;
}
