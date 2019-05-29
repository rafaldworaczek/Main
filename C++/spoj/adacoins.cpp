#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <bitset>
 
using namespace std;
 
int main() {
  int n, q, i, b, e;
  int count = 0;

  int coin; 
  const int maxSum = 100000;
  int prefixSum[maxSum + 1];

  scanf("%d %d\n", &n, &q);
 
  std::bitset<maxSum + 1> bit1;

  bit1.set(0);
  for (i = 0; i < n; i++) {
    scanf("%d", &coin);
    bit1 |= (bit1 << coin);
  } 
 
  prefixSum[0] = 0;

  for (i = 1; i <= maxSum; i++) {
     if (bit1.test(i)) 
       count++;
     
     prefixSum[i] = count;
  }
 
  for (i = 0; i < q; i++) {
     scanf("%d %d\n", &b, &e);
     printf("%d\n", prefixSum[e] - prefixSum[b-1]);
  }
 
 
  return 0;
}
 
