/*Task description:
  This is solution for 2SAT problem.
  Program outputs whether 2SAT problem is solvable or not.
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

void initList(struct adj *A, int n) {
  int i;

  for (i = 0; i <= n; i++) {
    A[i].head = NULL;
    A[i].tail = NULL;	
  }
}

void addEdge(struct adj *A, int v, int w) {
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
         int compNr, int *SCC, int *idx) {

  struct node *curr = NULL;

  marked[v] = 1;
  if (fillComp) {
    SCC[v] = compNr;
  }

  for (curr = A[v].head; curr != NULL; curr = curr->next) {
    if (!marked[curr->nr]) {
      dfs(A, curr->nr, stack, fillStack, marked, 
	  fillComp, compNr, SCC, idx);
    } 
  }

  if (fillStack) 
    stack[(*idx)++] = v;
  
}

/*Input file format
[nr_variables]
[varNrXj] [-varNrXi] 
.
[varNrXk] [varNrXy] 

(-) dash before variable denotes logical not.

Example:
[var2000] [-var5001] means:
(var2000 or not var5001)
*/

int main() {
  int idx = 0;
  int n, i;
  int u, w, x1, x2;
  int size;
  int strongComponents = 1;
  scanf("%d", &n);
  size = n * 2; 
  struct adj *G = (struct adj *) malloc((size + 1) * sizeof(struct adj));
  struct adj *R = (struct adj *) malloc((size + 1) * sizeof(struct adj));
  int *SCC = (int *) malloc((size + 1) * sizeof(int));
  int *stack = (int *) malloc((size) * sizeof(int));
  int *marked = (int *) malloc((size + 1) * sizeof(int));
  initList(G, size);
  initList(R, size);
  
  for (i = 0; i < n; i++) {
    scanf("%d %d", &u, &w);
    if (u > 0) x1 = abs(u) + n; else x1 = abs(u);
    if (w < 0) x2 = abs(w) + n; else x2 = w;
    addEdge(G, x1, x2);
    addEdge(R, x2, x1);

    if (w > 0) x1 = abs(w) + n; else x1 = abs(w);
    if (u < 0) x2 = abs(u) + n; else x2 = u;
    addEdge(G, x1, x2);
    addEdge(R, x2, x1);
  }

  clear(marked, size);

  for (i = 1; i <= size; i++) {
    if (!marked[i]) 
      dfs(G, i, stack, 1, marked, 0, 0, NULL, &idx);
  }

  clear(marked, size);
  for (i = size - 1; i >= 0; i--) 
    if (!marked[stack[i]]) {
      dfs(R, stack[i], stack, 0, marked, 1, 
	  strongComponents, SCC, &idx);
      strongComponents++;
    }

  free(G);
  free(R);
  free(stack);
  free(marked); 

  for (i = 1; i <= n; i++) {
    if (SCC[i] == SCC[i + n]) {
      printf("not satisfiable.\n");  
      free(SCC);
      return 0;
    }
  }
 
  free(SCC); 
  printf("satisfiable\n");

  return 0; 
}
