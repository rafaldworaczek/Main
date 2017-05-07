/* Task description:
http://main.edu.pl/en/archive/oi/4/liz

set: ulimit -s 65535 before execution
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 50
#define MAX(a,b) (((a)>(b))?(a):(b))

struct node {
  char val[MAX_LENGTH];
  int size;
};

int addLarge(char *num1, int sizeNum1, char *num2, int sizeNum2, char *res) {
  int size = MAX(sizeNum1, sizeNum2);       
  int i;
  int n1, n2;  
  int carry = 0;
  int c;
  int val;
  int len = 0;

  for (i = 0; i < size; i++) {
    n1 = n2 = 0;

    if (sizeNum1 > i)
      n1 = (int) num1[i] - '0';

    if (sizeNum2 > i) 
      n2 = (int) num2[i] - '0';
   
    val = n1 + n2 + carry;      
    carry = val / 10;
    c = (char) (val % 10) + '0';    
    res[i] = c; 
    len++;
  } 

  if (carry) {
    res[len] = carry + '0';
    len++;
  }

  return len;
}

int main() {
  int k; 
  int i, j;
  unsigned long long int max = 0;
  int n;
  char addRes[MAX_LENGTH * 2];
  char sumNum[MAX_LENGTH * 2];
  int addSize;
 
  scanf("%d %d", &n, &k);

  for (i = n; i > 0 ; i -= 2) 
    max += i;

  struct node dp[n + 1][max + 1];
  
  for (i = 0; i <= max; i++) {
    dp[0][i].val[0] = '0';
    dp[0][i].size = 1;
    dp[1][i].val[0] = '0';
    dp[1][i].size = 1;
  }
 
  for (i = 0; i <= n; i++) {
    dp[i][0].val[0] = '1'; 
    dp[i][0].size = 1;
  }

  dp[1][1].val[0] = '1';

  for (i = 2; i <= n; i++) {
    for (j = 1; j <= max; j++) {
      if (j - i >= 0) {
	addSize = addLarge(dp[i-2][j-i].val, dp[i-2][j-i].size, dp[i-1][j].val, dp[i-1][j].size, addRes);
	strncpy(dp[i][j].val, addRes, addSize); 
        dp[i][j].size = addSize;
      }
      else {
        strncpy(dp[i][j].val, dp[i-1][j].val, dp[i-1][j].size); 
        dp[i][j].size = dp[i-1][j].size;
      }
    }
  }

  sumNum[0] = '0';
  addSize = 1; 

  for (i = k + 1; i <= max; i++) {
    addSize = addLarge(sumNum, addSize, dp[n][i].val, dp[n][i].size, addRes);
    strncpy(sumNum, addRes, addSize); 
  }

  for (i = addSize - 1; i >= 0; i--) 
    printf("%c", sumNum[i]); 
  printf("\n");

  return 0;
}
