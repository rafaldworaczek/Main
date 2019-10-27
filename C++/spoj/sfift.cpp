/* https://www.spoj.com/problems/SGIFT/ */

#include<bits/stdc++.h>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
  int val, n, i, q;
  int a, b;
  long long int sum = 0;
 
  cin >> n;  
  long long int arr[n];
  long long int prefixSum[n];

  for (int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  sort(arr, arr + n); 
  cin >> q;
  
  for (int i = 0; i < n; i++) {
     sum += arr[i];
     prefixSum[i] = sum;
  }

  int lower, upper;
  for (int i = 0; i < q; i++) {
     cin >> a >> b;
     lower = lower_bound(arr, arr + n, a) - arr;
     upper = upper_bound(arr, arr + n, b) - arr - 1;

     if ((lower - 1) >= 0) 
        cout << prefixSum[upper] - prefixSum[lower-1] << endl;
     else 
        if (upper >= 0)  
           cout << prefixSum[upper] << endl;
	else 
	   cout << "0" << endl;
  }

  return 0;
}
