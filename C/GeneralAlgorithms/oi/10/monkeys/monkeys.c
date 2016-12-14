/*Task description: 
http://main.edu.pl/en/archive/oi/10/mal
*/

#include <stdio.h>
#include <stdlib.h>

void calcCC(int *sizes, int **graph, int *cc, int *marked, int v, int num) {
  int i;
  int u;

  marked[v] = 1;   
  cc[v] = num;

  for (i = 0; i < sizes[v]; i++) {
    u = graph[v][i];
    if (u != -1 && !marked[u]) {
      calcCC(sizes, graph, cc, marked, graph[v][i], num);
    }
  } 

  return;
}

int main() {
  int n, m, i, j, u, v;
  int num, side;
  int **graph;
  int **buffV;
  int **buffD;
  int **buffS;
  int left, right;
  scanf("%d", &n);
  scanf("%d", &m); 
  int cc[n + 1]; 
  int ccnum = 1; 
  int time[m][3];
  int *marked = (int *) calloc(n + 1, sizeof(int));
  int res[n + 1];
  int *sizes = (int *) calloc(n + 1, sizeof(int));
  int *currOff = (int *) calloc (n + 1, sizeof(int));

  buffV = (int **) malloc((n + 1) * sizeof(int *));
  buffD = (int **) malloc((n + 1) * sizeof(int *));
  buffS = (int **) malloc((m + 1) * sizeof(int *));

  for (i = 1; i <= n; i++) {
    buffV[i] = (int *) malloc(2 * sizeof(int));
    buffD[i] = (int *) calloc(2, sizeof(int));
  }

  for (i = 0; i < m; i++) 
    buffS[i] = (int *) calloc(2, sizeof(int));

  //Pre processing
  for (i = 1; i <= n; i++) {
    scanf("%d %d", &left, &right); 
    buffV[i][0] = left; 
    buffV[i][1] = right;
    if (left != -1)  { 
      sizes[left]++; 
      sizes[i]++; 
    }

    if (right != -1) { 
      sizes[right]++; 
      sizes[i]++; 
    }
  }

  for (i = 0; i < m; i++) {
    scanf("%d %d", &num, &side);
    u = num;
    v = buffV[num][side-1];
    buffS[i][0] = u;
    buffS[i][1] = v;

    if (side == 1) 
      buffD[u][0] = -1;
    else
      buffD[u][1] = -1;
  }

  graph = (int **) malloc((n + 1) * sizeof(int *));
  for (i = 1; i <= n; i++) 
    graph[i] = (int *) malloc(sizes[i] * sizeof(int));

  for (i = 1; i <= n; i++) {
    if (sizes[i] == 0) continue;
    for (j = 0; j < 2 ; j++) {
      u = i;
      v = buffV[i][j];
      if (v != -1 && buffD[i][j] != -1) {
        graph[u][currOff[u]++] = v;
        graph[v][currOff[v]++] = u;
      }
    }
  }

  for (i = 1; i <= n; i++) {
    if (!marked[i]) {
      calcCC(sizes, graph, cc, marked, i, ccnum);
      ccnum++;
    }
  } 

  for (i = 1; i <= n; i++) 
    marked[i] = 0;

  //-2 fall
  //-1 not fall
  for (i = 1; i <= n; i++) {
    if (cc[i] == 1)  
      cc[i] = -1;
    else 
      cc[i] = -2; 
  }

  for (i = m - 1; i >= 0; i--) {
    u = buffS[i][0];
    v = buffS[i][1];
    if (cc[u] == -2 && cc[v] != -2) 
      calcCC(sizes, graph, cc, marked, u, i);
    if (cc[v] == -2 && cc[u] != -2)  
      calcCC(sizes, graph, cc, marked, v, i);
    graph[u][currOff[u]++] = v;
    graph[v][currOff[v]++] = u;
  }
 
  for (i = 0; i <= n; i++) {
    free(graph[i]);
  }

  for (i = 1; i <= n; i++) {
    free(buffV[i]);    
    free(buffD[i]); 
  }

  for (i = 0; i < m; i++) 
    free(buffS[i]);

  for (i = 1; i <= n; i++) {
    printf("%d\n", cc[i]);
  }
 
  free(graph);
  free(marked);
  free(sizes);
  free(currOff);
  free(buffV);
  free(buffD);
  free(buffS);

  return 0; 
}
