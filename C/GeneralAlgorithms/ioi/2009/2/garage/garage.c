/*Task description: 
http://main.edu.pl/en/archive/ioi/2009/gar
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

struct pq {
  int size;
  int count;
  int *items;
  int (*insert) (struct pq *q, int nr);
  int (*delete) (struct pq *q);
  void (*print) (struct pq *q);
}; 

struct car {
  struct car *next;
  unsigned int num;
};

int pqInsert(struct pq *q, int nr) {
  int i, pos = 0;

  if (q->count >= q->size) 
    return -1;
    
  if (q->count == 0) {
    q->items[q->count] = nr;
  } else {
    for (i = 0; i < q->count; i++) {
      if (q->items[i] <= nr) { 
        pos = i + 1;
      } else {
	break;
      }
    }

    for (i = q->count; i > pos; i--) {
      q->items[i] = q->items[i - 1];
    }
    q->items[pos] = nr;
  } 

  q->count++;
  return 0;
}

int pqDelete(struct pq *q) {
  int i;
  int res;

  if (q->count == 0) return -1;

  res = q->items[0];
  if (q->count > 1) {
    for (i = 0; i < q->count - 1; i++)  
      q->items[i] = q->items[i+1]; 
  }

  q->count--; 
  return res; 
}

void pqPrint(struct pq *q) {
  int i;

  for (i = 0; i < q->count; i++) {
    printf("%d\n", q->items[i]);
  }  
}
 
struct pq *initPrioList(int size) {
  struct pq *q;
  q = (struct pq *) calloc(1, sizeof(struct pq)); 
  q->items = (int *) calloc(size, sizeof(int)); 
  q->size = size;
  q->count = 0;
  q->insert = &pqInsert;
  q->delete = &pqDelete; 
  q->print = &pqPrint;
  return q;
}

int main() {
  int n, m, i;
  scanf("%d %d", &n, &m);
  int rate[n + 1];
  int weight[m + 1];
  int place[m + 1];
  long long int sum = 0;
  int veh, num;
  struct car *qHead = NULL, *qTail = NULL, *qNew = NULL;
  struct pq *pq = initPrioList(n);

  for (i = 1; i <= n; i++)  
    scanf("%d", &rate[i]);

  for (i = 1; i <= m; i++) {
    place[i] = -1;
    scanf("%d", &weight[i]);
  }

  for (i = 1; i <= m; i++) 
    pq->insert(pq, i);

  for (i = 0; i < 2 * m; i++) {
    scanf("%d", &veh);
    if (veh > 0) {
      if ((num = pq->delete(pq)) != -1) {
	sum += weight[veh] * rate[num];
        place[veh] = num;
      } 
      else {
	qNew = (struct car *) malloc(sizeof(struct car));
	qNew->num = veh;
	qNew->next = NULL;

        if (qHead == NULL) {
	  qHead = qTail = qNew;
	  qHead->next = NULL;
	}
	else {
	  qTail->next = qNew;
	  qTail = qNew;
	}	
	qTail->next = NULL;
      }
    } else {
      pq->insert(pq, place[abs(veh)]);

      if (qHead != NULL) {
        if ((num = pq->delete(pq)) != -1) {
  	  sum += weight[qHead->num] * rate[num];
          place[qHead->num] = num;
	  if (qHead == qTail) 
	    qTail = NULL;
	  qHead = qHead->next;
        } 
      }
    }
  } 

  printf("%lld\n", sum);
  return 0; 
}
 

