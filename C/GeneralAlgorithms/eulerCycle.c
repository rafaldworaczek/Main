#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int idx = 0; 

struct EPath {
  struct EPath *next;
  struct EPath *neigh;
  unsigned int nr;
  unsigned short marked;
};

struct adj {
  struct EPath *head;
  struct EPath *tail;
};

void clearArray(int *array, int val, int n) {
  int i;

  for (i = 0; i <= n; i++) 
    array[i] = val;
}

void initList(struct adj *A, int n) {
  int i;

  for (i = 0; i <= n; i++) {
    A[i].head = NULL;
    A[i].tail = NULL;	
  }
}

int dfs(struct adj *A, int m, int v, int *path) {
  struct EPath *curr = NULL;
  int currV;
  int stack[m];
  int enter = 0;
  int idxP = 0;

  currV = v;

  do {

    for (curr = A[currV].head; curr != NULL; curr = curr->next) {	
      if (!curr->marked) {
        curr->marked = 1;
        curr->neigh->marked = 1;
	stack[idx++] = currV;
	currV = curr->nr;
	enter = 1;
	break;	
      } 
    }

    if (!enter) {
      path[idxP++] = currV;
      currV = stack[--idx]; 
    }
 
    enter = 0;
  } while (idx >= 0);

  return idxP;   
}

struct EPath *addAdjEdge(struct adj *A, int v, int w) {
  struct EPath *new = NULL;

  new = malloc(sizeof(struct EPath));
  new->nr = w;
  new->next = NULL;
  new->neigh = NULL;
  new->marked = 0;

  if (A[v].head == NULL) {
     A[v].head = new;
     A[v].tail = A[v].head;
  } else {
     A[v].tail->next = new;
     A[v].tail = new;
  }

  return new;
}

void print(int *tmp, int n) {
  int i = 0;
  for (i = 0; i < n; i++) 
     printf("%d ", tmp[i]);
  
  printf("\n");
}

int main() {
  int n, m, i;
  int v, w;
  int lines = 0, count = 0;
  int idxP = 0;
  struct EPath *node1, *node2;
  int startV = 0;
  scanf("%d %d", &n, &m);
   
  struct adj A[n + 2];
  int deg[n + 1];
  int virtVertex = n + 1;

  initList(A, n + 1);
  clearArray(deg, 0, n);

  for (i = 0; i < m; i++) {
    scanf("%d %d", &v, &w);
    deg[v]++;
    deg[w]++; 
    node1 = addAdjEdge(A, v, w);
    node2 = addAdjEdge(A, w, v);
    node1->neigh = node2;
    node2->neigh = node1;
  }

  for (w = 1; w <= n; w++) {
    //Add virtual vertex which connect to odd degrees vertexes
    if (deg[w] % 2 != 0) {
      node1 = addAdjEdge(A, virtVertex, w);
      node2 = addAdjEdge(A, w, virtVertex);
      node1->neigh = node2;
      node2->neigh = node1;
      lines++;
    }
  } 
  
  int size = m + lines;
  int path[size]; 
  int tmp[size];

  //Start from vertex 1 since graph has to have euler path now 
  //All degree of vertexes are even
  idxP = dfs(A, size, 1, path);

  startV = path[0]; 
  tmp[count++] = startV;

  for (i = 1; i < idxP; i++) {
     printf("Stack %d\n", path[i]); 
     
     if (path[i] == startV) {
       tmp[count++] = path[i];
       print(tmp, count);
       count = 0;
     }     
     else {
       if (path[i] != virtVertex)
         tmp[count++] = path[i];
     }
  }
  
  printf("count %d: ", count);
  print(tmp, count);
  
  if (lines == 0)  
    printf("Lines %d\n", 1);  
  else
    printf("Lines %d\n", lines / 2);  

  return 0; 
}
 
