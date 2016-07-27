/* Task description:
http://main.edu.pl/en/archive/oi/2/drz
*/

#include <stdlib.h>
#include <stdio.h>

struct tree {
  int nr;
  int parentNr;
  struct tree *l;
  struct tree *r; 
}; 

int traverseCheck(struct tree *node) {
  int retl = 0;
  int retr = 0;

  if (node == NULL) return 0;

  if (node->l && node->r == NULL) return -1; 
  if (node->r && node->l == NULL) return -1;
  retl = traverseCheck(node->l);
  if (retl == -1) return -1;
  retr = traverseCheck(node->r);
  if (retr == -1) return -1; 
  
  return 0;
}

void printGenealogical(struct tree *node) {
  if (node == NULL) return;
 
   printf("%d ", node->parentNr);
   printGenealogical(node->l);
   printGenealogical(node->r);
}

void printBracket(struct tree *node) {
  if (node == NULL) return;
 
  printf("(");
  printBracket(node->l);
  printBracket(node->r);
  printf(")");
}

void treePreorder(struct tree *node, int *levels, int *idx, int currLevel, int n, int *currNr) {
  
  if ((*idx) >= n) return;

  if (currLevel < levels[*idx]) {
    node->l = (struct tree *) calloc(1, sizeof(struct tree));
    node->l->nr = (*currNr)++;
    node->l->parentNr = node->nr;
    treePreorder(node->l, levels, idx, currLevel + 1, n, currNr);
  } else {
    if (currLevel == levels[*idx] && node->r == NULL && node->l == NULL) {
      (*idx)++;
       node->l = NULL;
    }
    return;
  }	

  if ((*idx) >= n) return;

  if (currLevel < levels[*idx]) {
    node->r = (struct tree *) calloc(1, sizeof(struct tree));
    node->r->nr = (*currNr)++;
    node->r->parentNr = node->nr;
    treePreorder(node->r, levels, idx, currLevel + 1, n, currNr);
  } else {
    if (currLevel == levels[*idx] && node->r == NULL && node->l == NULL) {
      (*idx)++;
       node->r = NULL;
     }
    return;
  }
}

int main() {
  int i;
  int n;
  scanf("%d", &n);
  int l[n];
  int idx = 0, currNr = 2;
  for (i = 0; i < n; i++)
    scanf("%d", &l[i]);

  struct tree *root = (struct tree *) calloc(1, sizeof(struct tree));    
  root->nr = 1;
  root->parentNr = 0;
    
  treePreorder(root, l, &idx, 0, n, &currNr);

  if (idx < n || traverseCheck(root) == -1) {
     printf("NIE\n"); 
     return 0;
  }

  printGenealogical(root); 
  printf("\n");
  printBracket(root); 
  printf("\n");
  return 0;
}
