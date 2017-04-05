/* Task description:
http://main.edu.pl/en/archive/oi/2/obc
*/

#include <stdio.h>
#include <stdlib.h>

struct tree {
  struct tree *next;  
  int val;
};

struct adj {
  struct tree *head;
  struct tree *tail;
};

void initList(struct adj *A, int n) {
  int i;

  for (i = 0; i <= n; i++) {
    A[i].head = NULL;
    A[i].tail = NULL;
  }
}

void initMarked(int *marked, int n) {
  int i;

  for (i = 0; i <= n; i++) 
    marked[i] = 0;
}

void addAdj(struct adj *A, int v, int w) {
  struct tree *new = NULL;

  new = malloc(sizeof(struct tree));
  new->val= w;
  new->next = NULL;

  if (A[v].head == NULL) {
    A[v].head = new;
    A[v].tail = A[v].head;
  } else {
    A[v].tail->next = new;
    A[v].tail = new;
  }
}

void traverse(struct adj *A, int *marked, int level, int v) {
  struct tree *root = A[v].head;
  struct tree *curr;

  if (root == NULL || marked[v]) return;

  marked[v] = 1;

  if (level % 2 == 0) {
      printf("%d\n", v);      
    marked[v] = 1;
  }
  for (curr = root; curr != NULL; curr = curr->next) {
     if (!marked[curr->val])
       traverse(A, marked, level + 1, curr->val);
  }

  if (level % 2 != 0) {
       printf("%d\n", v);
     marked[v] = 1;
  }
}

int main() {
  int n;
  int i;
  int u, w;
  struct tree *curr;
  struct tree *next;

  scanf("%d", &n);
  if (n == 1) {
    printf("1\n"); 
    return 0;
  }

  struct adj A[n + 1]; 
  int marked[n + 1];
  initList(A, n);
  initMarked(marked, n);
  for (i = 0; i < n; i++) {
    scanf("%d %d", &u, &w);
    addAdj(A, u, w);
    addAdj(A, w, u);
  }

  traverse(A, marked, 0, 1);
  //cleanup
  for (i = 0; i <= n; i++) {
    curr = A[i].head;
    if (curr == NULL) continue;
    next = curr->next;
    
    while (1) {
      free(curr);
      curr = next;
      if (curr == NULL) break;

      next = curr->next;  
    }
  }	

  return 0;
 }
