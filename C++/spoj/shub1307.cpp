/* https://www.spoj.com/problems/SHUB1307/ */

#include <bits/stdc++.h>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int data[100][100];
int dp[100][100][501];

void clearArray(int n, int m, int k) {
  for (int x = 0; x < n; x++) {
   for (int y = 0; y < m; y++) 
     for (int z = 0; z <= k; z++) 
       dp[x][y][z] = 0;
  }
}

int main() {
  int n, m, k, t;
  int sum = 0;

  cin >> t;
  for (int i = 0; i < t; i++) {
    cin >> n >> m >> k;
    for (int x = 0; x < n; x++) 
      for (int y = 0; y < m; y++) 
        cin >> data[x][y];
     
    clearArray(n, m, k);    
 
    dp[0][0][data[0][0]] = 1;

    for (int x = 0; x < n; x++) {
      for (int y = 0; y < m; y++) { 
        for (int z = 0; z <= k; z++) {

 	   if ((x - 1 >= 0) && (y - 1) >= 0) {
             if ((z - data[x][y] >= 0) && dp[x-1][y-1][z-data[x][y]])
    	       dp[x][y][z] = 1;
	   }
	
 	   if ((x - 1) >= 0) { 
             if ((z - data[x][y] >= 0) && dp[x-1][y][z-data[x][y]])
    	       dp[x][y][z] = 1;
	   }

	   if ((y - 1) >= 0) {
             if ((z - data[x][y] >= 0) && dp[x][y-1][z-data[x][y]])
    	        dp[x][y][z] = 1;
	   }
        }
      } 
    }
  
    bool enter = false; 
    for (int x = k; x >= 0; x--) {
      if (dp[n-1][m-1][x]) {
	cout << x << endl;
	enter = true;
	break;
      }
    }

    if (!enter) 
      cout << "-1" << endl; 
  }

  return 0;
}
