/*Task description:
http://main.edu.pl/en/archive/oi/19/bon
*/

#define MAX_COUPON_SIZE 1000000 + 1
#define MAX_COUPON_NR 1000000 

#include <stdio.h>
#include <stdlib.h>

int main() {
  int i = 0, m, n, k, j, l;
  long long int guestNr = 1;
  int idx = 0;
  int num = 0;
  scanf("%d", &m);
  int *coupon = (int *) calloc(MAX_COUPON_SIZE, sizeof(int));
  int *packs = (int *) calloc(MAX_COUPON_SIZE, sizeof(int));
  int *cache = (int *) calloc(MAX_COUPON_SIZE, sizeof(int));
  long long int res[MAX_COUPON_SIZE];
  long long int user = 0;

  for (i = 0; i < m; i++) {
    scanf("%d", &num);
    coupon[num] = 1; 
  } 

  scanf("%d", &n); 
  for (i = 0; i < n; i++) {
    scanf("%d", &k);

    if (cache[k]) 
      l = cache[k];
    else { 
      l = k;
    }

    user = guestNr;
    for (j = 1; j <= k; j++) {	   
      while (l <= (MAX_COUPON_NR)) { 
	if (!packs[l]) { 
	  packs[l] = 1;
  	  if (coupon[l]) res[idx++] = user;
	  l += k;
	  user++;
	  break;
   	}
	l += k; 	
      }
      if (l > MAX_COUPON_NR) break;
    }
    guestNr += k; 
    cache[k] = l;
  } 

  printf("%d\n", idx);
  for (i = 0; i < idx; i++) 
    printf("%lld\n", res[i]);
 
  return 0;
}
