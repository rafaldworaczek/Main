/* Task description:
http://main.edu.pl/en/archive/pa/2006/lot
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

long long int count(int n) {
  if (n <= 9) return n;

  long long int sum = 0;
  int i = 0;
  while (n > 0) {
    sum += (n % 10);
    n /= 10;
  }

  return count(sum);
}

int main() {
  int n, i, j;
  scanf("%d", &n);
  long long int sum = 1;
  long long int nr;
  long long int res = 0;
  long long int val;
  int el = 10; 
  long long int A[el];
  long long int tmp[el];
 
  for (i = 0; i < el; i++) 
    A[i] = tmp[i] = 0;

  for (i = 0; i < n; i++) {
    scanf("%lld", &nr);

    val = count(nr);
    for (j = 0; j < el; j++) {
      if (A[j] != 0) 
        tmp[count(val * j)] += A[j]; 
    }

    for (j = 0; j < el; j++) {
      if(tmp[j]) 
        A[j] = count(A[j] + tmp[j]);
      
      tmp[j] = 0;
    }

    A[val] += 1;
  }

  for (i = 0; i < el; i++) {
    if (A[i]) 
      res += count(A[i] * i); 
  }

  printf("%lld\n", count(res));

  return 0;
}
