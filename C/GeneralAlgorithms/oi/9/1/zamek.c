/* Problem statment 
* Solution - Rafal Dworaczek
* https://szkopul.edu.pl/problemset/problem/6rpUvcEi2h8ql4GqXo7cAXgo/site/?key=statement
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX_MONEY 1001

struct adj {
   struct vertex *head;
   struct vertex *tail;
};

struct vertex {
   struct vertex *next;
   unsigned int p;
   unsigned int nr;
};

struct ver {
  int money[MAX_MONEY];
  int prev[MAX_MONEY];
  int prevMoney[MAX_MONEY]; 
};

void initList(struct adj *A, int n) {
  int i;
 
  for (i = 0; i <= n; i++) {
    A[i].head = NULL;
    A[i].tail = NULL;
  }
}

int dfs(struct adj *A, struct ver *vert,
	int *cost, int prev, int v, int *marked, int moneyUsed, int maxMoney) {
  int i; 
  struct vertex *curr = NULL;

  int sumCost = cost[v] + moneyUsed;
 
  if (sumCost > maxMoney) 
    return 0;

  /* check if path with particular cost exists. it speeds up program a lot*/
  if (vert[v].money[sumCost] != 0) return 0;

  vert[v].money[sumCost] = 1;
  vert[v].prev[sumCost] = prev;
  vert[v].prevMoney[sumCost] = moneyUsed;
 
  for (curr = A[v].head; curr != NULL; curr = curr->next) {
    if (curr != NULL) 
      dfs(A, vert, cost, v, curr->nr, marked, sumCost, maxMoney);
  }
}

void addEdge(struct adj *A, int v, int w) {
  struct vertex *new = NULL;
  int i; 
  new = malloc(sizeof(struct vertex));
  new->nr = w;
  new->next = NULL;
 
  if (A[v].head == NULL) {
    A[v].head = new;
    A[v].tail = A[v].head;
  } else {
    A[v].tail->next = new;
    A[v].tail = new;
  }
}

void clearArray(int *arr, int size) {
  int i;

  for (i = 0; i <= size; i++) 
    arr[i] = 0; 
}

int main() {
  int n, m, w, s, k, i, u, v, j;
  scanf("%d %d %d %d %d", &n, &m, &w, &k, &s);
  struct adj G[n + 1];
  int marked[n + 1];
  int cost[n + 1];
  int out[n];
  struct ver money[n + 1];

  for (i = 0; i <= n; i++) {
    for (j = 0; j <= s; j++) {
      money[i].money[j] = 0;
      money[i].prev[j] = 0;
      money[i].prevMoney[j] = 0;
    }
  } 

  for (i = 1; i <= n; i++) {
    scanf("%d", &cost[i]);
  }

  initList(G, n);
  clearArray(marked, n);

  for (i = 0; i < m; i++) {
    scanf("%d %d", &u, &v);
    addEdge(G, u, v);
    addEdge(G, v, u);
  }

  dfs(G, money, cost, -1, w, marked, 0, s);
  
  int currV = k;
  int tmp;
  int idx = 0;

  if (money[currV].money[s] != 0) {
    while (currV != -1) {
      out[idx++] = currV;
      tmp = currV;
      currV = money[currV].prev[s];
      s = money[tmp].prevMoney[s]; 
    }
  }
 
  for (i = idx - 1; i >= 0; i--) {
    printf("%d\n", out[i]);
  }
 
  return 0; 
}
 

