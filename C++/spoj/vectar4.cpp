/* https://www.spoj.com/problems/VECTAR4/ */

#include <bits/stdc++.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>

using namespace std;

typedef unsigned long long int u64;

int main() {
  int t, i;
  u64 idx;
  u64 n;
  u64 sum = 0;

  cin >> t;
  for (int i = 0; i < t; i++) {
    cin >> n;

    idx = floor(sqrt(n));        
    /* Workaround for sqrt function - which is not precise enough 
       For instance:
       N 999999999999999999 result of sqrt 1000000000
    */
    if ((idx * idx) > n) {
      idx--;
    }

    sum = idx + (idx - 1);
    if (n != (idx * idx)) {
      if (n <= ((idx * idx) + idx)) 
        sum++;
      else
        sum += 2; 
    } 
    cout << sum << endl;
  }

  return 0;
}
