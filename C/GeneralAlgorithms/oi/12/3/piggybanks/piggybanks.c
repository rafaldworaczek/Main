/* Task description:
http://main.edu.pl/en/archive/oi/12/ska
*/

#include <stdio.h>
#include <stdlib.h>

int main() {
  int n = 0, i = 0,  v, oldv;
  int key;
  scanf("%d", &n);
  int *graph = (int *) calloc(n + 1, sizeof(int));
  int *cnt = (int *) calloc(n + 1, sizeof(int));
  int res  = 0;

  for (i = 1; i <= n; i++) {
    scanf("%d", &key);
    graph[i] = key;
    cnt[key]++;
  }

  for (i = 1; i <= n; i++) {
    if (cnt[i] == 0 && graph[i] != 0) {
      v = i;
      do {
        oldv = v; 
        v = graph[v];	
        graph[oldv] = 0;	
        cnt[v]--;
      } while (cnt[v] == 0); 	
    }
  }

  //Couting of cycles
  for (i = 1; i <= n; i++) {
   if (cnt[i] != 0) {
     res++;
     v = i;
     while (graph[v] != 0) {
        oldv = v; 
        v = graph[v];	
        graph[oldv] = 0;	
	cnt[v]--;
     }
   }
  }

  printf("%d\n", res);
  free(graph);
  free(cnt);
  return 0; 
}
 
