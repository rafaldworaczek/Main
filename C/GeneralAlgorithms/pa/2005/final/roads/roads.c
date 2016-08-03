/*Task description:
http://main.edu.pl/en/archive/pa/2005/dro

This is practical example using of strongly connected component.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct node {
  struct node *next;
  unsigned int nr;	
};

struct adj {
  struct node *head;
  struct node *tail;
};

void clear(int *marked, int n) {
  int i;

  for (i = 0; i <= n; i++) 
    marked[i] = 0;
}

void clearNeg(int *arr, int n) {
  int i;

  for (i = 0; i <= n; i++) 
    arr[i] = -1;
}

void initList(struct adj *A, int n) {
  int i;

  for (i = 0; i <= n; i++) {
    A[i].head = NULL;
    A[i].tail = NULL;	
  }
}

void addAdj(struct adj *A, int v, int w) {
  struct node *new = NULL;

  new = malloc(sizeof(struct node));
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

void dfs(struct adj *A, int v, int *stack, 
	 int fillStack, int *marked, int fillComp, 
         int j, int *SCC, struct adj *C, int *idx) {

  struct node *curr = NULL;

  marked[v] = 1;
  if (fillComp) {
    SCC[v] = j;
    addAdj(C, j, v);
  }

  for (curr = A[v].head; curr != NULL; curr = curr->next) {
    if (!marked[curr->nr]) {
      dfs(A, curr->nr, stack, fillStack, marked, fillComp, j, SCC, C, idx);
    } 
  }

  if (fillStack) 
    stack[(*idx)++] = v;
  
}

int main() {
  int idx = 0;
  int n, m, i;
  int v, w;
  int strongComponents = 1;
  struct node *currA = NULL;
  struct node *currC = NULL;
  int indeg = 0, outdeg = 0;
 
  scanf("%d %d", &n, &m);

  struct adj A[n + 1];
  struct adj B[n + 1];
  struct adj C[n + 1];
  int SCC[n + 1];
  int stack[n]; 
  int marked[n + 1];
  initList(A, n);
  initList(B, n);
  initList(C, n);

  clear(marked, n);
  
  for (i = 0; i < m; i++) {
    scanf("%d %d", &v, &w);
    addAdj(A, v, w);
    addAdj(B, w, v);
  }

  for (i = 1; i <= n; i++) {
    if (!marked[i]) 
      dfs(A, i, stack, 1, marked, 0, 0, NULL, NULL, &idx);
  }

  clear(marked, n);

  for (i = n - 1; i >= 0; i--) 
    if (!marked[stack[i]]) {
      dfs(B, stack[i], stack, 0, marked, 1, strongComponents, SCC, C, &idx);
      strongComponents++;
    }

  if (strongComponents <= 2) {
    printf("%d\n", 0);
    return 0;
  } 

  int resIn[strongComponents];
  int resOut[strongComponents];
  clear(resIn, n);
  clear(resOut, n);

  for (i = 1; i < strongComponents; i++) {
    for (currC = C[i].head; currC != NULL; currC = currC->next) {
      for (currA = A[currC->nr].head; currA != NULL; currA = currA->next) {
        if (SCC[currC->nr] != SCC[currA->nr]) {
          resOut[SCC[currC->nr]]++; 
          resIn[SCC[currA->nr]]++; 
        } 
      } 
    }
  }

  for (i = 1; i < strongComponents; i++) {
    if (resIn[i] == 0)
      indeg++;

    if (resOut[i] == 0)
      outdeg++; 
  }

  if (indeg >= outdeg)
    printf("%d\n", indeg);
  else
    printf("%d\n", outdeg); 

  return 0; 
}
 
