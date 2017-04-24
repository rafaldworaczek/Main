/* Task description:
http://main.edu.pl/en/archive/oi/4/lot
*/

#include <stdio.h>
#include <stdlib.h>

struct vertex {
  int nr;
  int val;   
};

int comparator(const void *p, const void *q) {
   if (((struct vertex *)p)->val < ((struct vertex *)q)->val)
      return -1;
   if (((struct vertex *)p)->val > ((struct vertex *)q)->val)
      return 1;

   return 0;
}

int main() {
  int n, i;
  int j;
  int val;
  int size = 0;
  scanf("%d", &n);
  struct vertex d[n];    

  for (i = 0; i < n; i++) {
    scanf("%d", &val);
    d[i].val = val;
    d[i].nr = i + 1;
  }

  for (i = n - 1; i >= 1; i--) {
    qsort(d, n - size, sizeof(d[0]), comparator);

    for (j = i - d[i].val; j < i; j++) {
      d[j].val--; 
      printf("%d %d\n", d[i].nr, d[j].nr);
    } 

    size++;
  }

  return 0;
} 
