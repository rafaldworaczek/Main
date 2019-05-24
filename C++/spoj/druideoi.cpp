#include <iostream>
#include <stack>
#include <stdlib.h>
#include <stdio.h>
#include <vector> 
#include <algorithm> 

using namespace std;

bool cmp(int n, pair<int, int> const& p)
{
    return (p.first > n);
}

int main() {
  int t, n, j, id;

  scanf("%d", &t);

  for (int i = 0; i < t; i++) {
    scanf("%d", &n);
    int arr[n + 1];
    int outIdxR[n + 1], outIdxL[n + 1];

    stack < pair<int, int> > stack;
    vector < pair<int, int> > v;
    vector < pair<int, int> >::iterator idx;

    while (!stack.empty()) 
        stack.pop();

    v.clear();

    for (j = 1; j <= n; j++) {
      scanf("%d", &arr[j]);
      outIdxR[j] = outIdxL[j] = -1;
    }
  
    stack.push(make_pair(arr[n], n));
      
    /* go right */
    for (j = n - 1; j > 0; j--) {
      if (stack.top().first > arr[j]) {
        if (outIdxR[j] == -1)
          outIdxR[j] = stack.top().second;
       } else {
         while (stack.size() != 0) {
           if (stack.top().first <= arr[j])
             stack.pop();
           else {
             if (outIdxR[j] == -1)
     	       outIdxR[j] = stack.top().second;
               break;
            }
          }
        }
        stack.push(make_pair(arr[j], j));
      }

      v.push_back(make_pair(arr[1], 1));

      for (j = 2; j <= n; j++) {
        if (v.back().first > arr[j]) {
          id = upper_bound(v.begin(), v.end(), arr[j], cmp) - v.begin();
 
    	  if (outIdxR[j] == -1)
	    outIdxR[j] = v.at(id).second;
	} else
	  v.push_back(make_pair(arr[j], j));
      }

     while (!stack.empty()) 
       stack.pop();

     /* go left */
     stack.push(make_pair(arr[1], 1));

     for (j = 2; j <= n; j++) {
       if (stack.top().first > arr[j]) {
         if (outIdxL[j] == -1)
           outIdxL[j] = stack.top().second;
       } else {
         while (stack.size() != 0) {
           if (stack.top().first <= arr[j])
             stack.pop();
           else {
             if (outIdxL[j] == -1)
               outIdxL[j] = stack.top().second;
             break;
           }
         }
       }
       stack.push(make_pair(arr[j], j));
     }

     v.clear();
     v.push_back(make_pair(arr[n], n));

     for (j = n - 1; j > 0; j--) {
       if (v.back().first > arr[j]) {
	 id = upper_bound(v.begin(), v.end(), arr[j], cmp) - v.begin();
 
    	 if (outIdxL[j] == -1)
	   outIdxL[j] = v.at(id).second;
       } else
         v.push_back(make_pair(arr[j], j));
     }

     for (j = 1; j <= n; j++) 
       printf("%d %d\n", outIdxL[j], outIdxR[j]);
    
  }

  return 0;
}
