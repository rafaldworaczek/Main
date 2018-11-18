#include<queue>
#include<algorithm>
#include <iostream> 

using namespace std;

int main() {
  int n, i, val, k;
  deque<int> q;
 
  cin >> n;
  for (i = 0; i < n; i++) {
    cin >> val;
    q.push_back(val); 
  }

  cin >> k;
  for (i = 0; i <= n - k; i++) {
    cout << *max_element(q.begin(), q.begin() + k) << " ";
    q.pop_front();
  }

  cout << "\n";

  return 0;
} 
