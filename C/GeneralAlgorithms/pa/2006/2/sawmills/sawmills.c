/* Task description: 
http://main.edu.pl/en/archive/pa/2006/tar
*/

#include <stdio.h>
#include <stdlib.h>

struct building {
  int nr;
  char type; 
};

int main() {
  int n, i;
  scanf("%d\n", &n);
  struct building stack[n * 2];
  int res[n][2];
  int millNr = 1; 
  int houseNr = 1; 
  int nr;
  int idx = 0;
  int resIdx = 0;
  char c;
  
  for (i = 0; i < 2 * n; i++) {
    scanf("%c", &c);

    if (c == 'g')  {
      nr = houseNr++;
    } else 
      if (c == 't') {
        nr = millNr++; 
      } else break; 

    if (idx > 0) { 
      if (stack[idx - 1].type != c) {
 	if (c == 't') {
          res[resIdx][0] = stack[idx - 1].nr; 
	  res[resIdx][1] = nr;
	} else {
	  res[resIdx][0] = nr; 
	  res[resIdx][1] = stack[idx - 1].nr;
        }
	  
        resIdx++;
	idx--;
	continue;
      }
    } 

    stack[idx].nr = nr;
    stack[idx].type = c;  
    idx++; 
  }

  if (idx != 0) {
    printf("NIE");
    return 0;
  } 

  for (i = 0; i < n; i++)
    printf("%d %d\n", res[i][0], res[i][1]);

  return 0; 
}
 

