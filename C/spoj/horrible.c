#include <stdlib.h> 
#include <stdio.h> 
#include <limits.h>

#define DEBUG 0
 
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
 
struct tree {
   long long int l;
   long long int r;
   struct tree *left;
   struct tree *right;
   long long int sum;
   long long int postpone;
};
 
struct tree *create_node() {
  struct tree *root = (struct tree *) calloc(1, sizeof(struct tree));
 
  return root;
}
 
struct tree *buildTree(long long int l, long long int r) {
  struct tree *root = NULL;
  
  if (l <= r) {
    long long int m = l + (r - l) / 2;
    
    root = create_node();
    
    if (l < r) {
      root->left = buildTree(l, m);
      root->right = buildTree(m+1, r);
    } else 
      root->left = root->right = NULL;
 
    root->l = l;
    root->r = r;	
    root->sum = root->postpone = 0; 
  }
  
  return root;	
}
 
int *fillTree(struct tree *root, long long int p, long long int q, 
	       long long int val) {

  if (root == NULL) return 0;
 
  //outside range
  if (root->l > q || root->r < p) 
    return 0;
 
  //node is inside a query
  if (root->l >= p && root->r <= q) {
     root->sum += ((root->r - root->l + 1) * val);
     if (root->left != NULL) 
        root->left->postpone += val;
 
     if (root->right != NULL) 
        root->right->postpone += val;
 
     return 0;
  }
 
  //whole query inside a node?
  if (p >= root->l && q <= root->r) { 
    root->sum += (q - p + 1) * val; 
  } else {  
    if (root->l >= p) {
      root->sum += (q - root->l + 1) * val;
    } else {
      if (root->r >= p)   
        root->sum += (root->r - p + 1) * val;
    }
  }
 
  fillTree(root->left, p, q, val);
  fillTree(root->right, p, q, val);
 
  return 0;
}
 
long long int queryTree(struct tree *root, int p, int q) {
  long long int left, right; 
 
  if (root == NULL) return 0;
 
  //outside of range
  if (root->l > q || root->r < p) 
    return 0; 
 
  if (root->postpone) {
    root->sum += (root->r - root->l + 1)  * root->postpone;
    if (root->left != NULL) 
      root->left->postpone += root->postpone;
    if (root->right != NULL) 
      root->right->postpone += root->postpone;
    root->postpone = 0;
  }
 
  //node is inside a query
  if (root->l >= p && root->r <= q) 
     return root->sum; 
  
  left = queryTree(root->left, p, q);
  right = queryTree(root->right, p, q);
 
  return left + right;
}
 
void printTree(struct tree *root) {
 
   if (root != NULL) {
#ifdef DEBUG
     printf("L: %lld R: %lld sum %lld", root->l, root->r, root->sum);
     printf("\n");
#endif
     printTree(root->left);
     printTree(root->right);
   }
   return;
}
 
void treeFreeMem(struct tree *root) {
 
  if (root == NULL) return;
 
  treeFreeMem(root->left);
  treeFreeMem(root->right);
 
  free(root);
}
 
int main() 
{  
  int i, t, n, c, j, comm;
  long long int p, q;
  long long int val;
 
  scanf("%d", &t);
  
  for (i = 0; i < t; i++) {
    scanf("%d %d", &n, &c); 
    struct tree *root = buildTree(1, n);
 
    for (j = 0; j < c; j++) {
      scanf("%d", &comm); 
 
      if (!comm) {
	scanf("%lld %lld %lld", &p, &q, &val);
	fillTree(root, p, q, val);
      } else {
	scanf("%lld %lld", &p, &q);
	printf("%lld\n", queryTree(root, p, q));
      }
    }
    treeFreeMem(root);
  }
 
  return 0;	
} 
