/*Task description: 
https://main.edu.pl/en/archive/oi/11/mos
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX(a,b) (((a)>(b))?(a):(b))

int main() {
  int n, i;
  scanf("%d", &n);
  int arr[n];
  int t1, t2;
  int change_cost = 0;
  int total = 0;
  int max = 0;

  for (i = 0; i < n; i++) 
    scanf("%d", &arr[i]);

  if (n == 1) 
    return printf("%d\n", arr[0]);

  if (n == 2) {
	max = MAX(arr[0], arr[1]);
	return printf("%d\n", max); 
  }

  t1 = arr[0];
  t2 = arr[1];

  change_cost = (2 * t2) + t1; 
  i = n - 1;

  while (i >= 0) {
     if (i < 2) {
	total += MAX(t1, t2);
	break;
     }

     if ((arr[i] + arr[i-1] + (2 * t1)) > (change_cost + arr[i])) {
	total += (change_cost + arr[i]); 
	i -= 2;	
     } else {
	total += (arr[i] + t1); 
	i -= 1;
     }
  }

  printf("%d\n", total); 
  return 0;
}
