/*Task description: 
http://main.edu.pl/en/archive/oi/3/fib
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))
#define MAX_LENGTH 30

int ConvertIntToCharArray(int num, char *res) {
  int size = 0; 
  int val;

  val = num; 
  if (!val) return size + 1;

  while (val) {
    res[size++] = (val % 10) + '0';
    val = val / 10;  
  }

  return size;
}

int addLarge(char *num1, int sizeNum1, char *num2, int sizeNum2, char *res) {
  int size = MAX(sizeNum1, sizeNum2);       
  int i;
  int n1, n2;  
  int carry = 0;
  int c;
  int val;
  int len = 0;

  for (i = 0; i < size; i++) {
    n1 = n2 = 0;

    if (sizeNum1 > i)
      n1 = (int) num1[i] - '0';

    if (sizeNum2 > i) 
      n2 = (int) num2[i] - '0';
   
    val = n1 + n2 + carry;      
    carry = val / 10;
    c = (char) (val % 10) + '0';    
    res[i] = c; 
    len++;
  } 

  if (carry) {
    res[len] = carry + '0';
    len++;
  }

  return len;
}

int copyMessage(char *start, int sizeStart, char *end, int sizeEnd, char *message, int n) {
  int i; 
  int idx;
  int curridx = 0;

  idx = sizeStart;
  if (sizeStart > n - 1) 
    sizeStart = n - 1;

  for (i = 0; i < sizeStart; i++) 
    message[curridx++] = start[idx - sizeStart + i]; 

  if (sizeEnd > n - 1) 
    sizeEnd = n - 1;

  for (i = 0; i < sizeEnd; i++) 
    message[curridx++] = end[i]; 
  
  message[curridx] = '\0';

  return sizeStart + sizeEnd;
}



long long int FindNumOccur(char *message, int size, char *pattern, int sizeP) {
  int occur = 0;
  int i, j;
  int currIdx = 0;

  if (size < sizeP) return 0;
  
  for (i = 0; i <= size - sizeP; i++) {
    for (j = i; j < i + sizeP; j++) {
      if (j >= size) break;

      if(message[j] != pattern[currIdx]) break; 
      currIdx++;
    }
    
    if (currIdx == sizeP) occur++;
    currIdx = 0;
  }

  return occur;
}

struct node {
  char start[MAX_LENGTH];
  char end[MAX_LENGTH]; 
  int sizeStart;
  int sizeEnd;
  char occur[MAX_LENGTH*10];
  int occurSize;
};

void initData(struct node *arr, int size) {
  int i = 0;
  for (i = 0; i < size; i++) 
    memset(&arr[i].occur, '0', sizeof(arr[i].occur));
}

int main() {
  int i = 0, n;
  int j;
  char c;
  int psize = 0;
  long long int middle = 0;
  char pattern[MAX_LENGTH];
  char message[MAX_LENGTH * 2];
  char res[MAX_LENGTH * 10];
  char resTwo[MAX_LENGTH * 10];
  char mid[MAX_LENGTH * 10];
  int size, sizeMid;

  int bytes;
  char *offset;

  while (1) {
    scanf("%c", &c);  
    pattern[i++] = c;
    if (c == '\n') break;
    psize++;
  }
  pattern[psize] = '\0';

  scanf("%d", &n);
  struct node fib[n];
  initData(fib, n);

  if (n <= 2) {
    if (psize == 1) {
      if((n == 1 && pattern[0] == 'b') || n == 2) {
        printf("1\n");
        return 0;
      }
    }

    printf("0\n");
    return 0;
  }

  fib[0].start[0] = 'b';
  fib[0].end[0] = 'b';
  fib[0].end[1] = '\0';
  fib[0].sizeStart = fib[0].sizeEnd = 1;
  if (psize == 1 && pattern[0] == 'b')
    fib[0].occur[0] = '1';
  else
    fib[0].occur[0] = '0';
  fib[0].occurSize = 1;
  
  fib[1].start[0] = 'a';
  fib[1].end[0] = 'a';
  fib[1].end[1] = '\0';
  fib[1].sizeStart = fib[1].sizeEnd = 1;
  if (psize == 1 && pattern[0] == 'a')
    fib[1].occur[0] = '1';
  else
    fib[1].occur[0] = '0';
  fib[1].occurSize = 1;

  for (i = 2; i < n; i++) {
    size = copyMessage(fib[i-1].end, fib[i-1].sizeEnd, fib[i-2].start, fib[i-2].sizeStart, message, psize);	
    if (size != 0)
      middle = FindNumOccur(message, size, pattern, psize);

    strncpy(fib[i].start, fib[i-1].start, fib[i-1].sizeStart);
    fib[i].sizeStart = fib[i-1].sizeStart;
    fib[i].start[fib[i].sizeStart] = '\0';

    if (fib[i].sizeStart < psize - 1) {
      bytes = psize - 1 - fib[i].sizeStart;
      if (fib[i-2].sizeEnd < bytes) bytes = fib[i-2].sizeEnd;
      strncat(fib[i].start, fib[i-2].end, bytes);
      fib[i].sizeStart += bytes;
    } 

    if (fib[i-2].sizeEnd < psize - 1) {
      bytes = psize - 1 - fib[i-2].sizeEnd;
      if (fib[i-1].sizeStart < bytes)
	bytes = fib[i-1].sizeStart;

      offset = fib[i-1].start + fib[i-1].sizeStart - bytes;
      strncpy(fib[i].end, offset, bytes);

      fib[i].sizeEnd = bytes;
      fib[i].end[fib[i].sizeEnd] = '\0';
      strcat(fib[i].end, fib[i-2].end);
      fib[i].sizeEnd += fib[i-2].sizeEnd;

    } else {
      strncpy(fib[i].end, fib[i-2].end, fib[i-2].sizeEnd + 1);
      fib[i].sizeEnd = fib[i-2].sizeEnd;
    }

    memset(mid, '0', sizeof(mid));
    size = addLarge(fib[i-1].occur, fib[i-1].occurSize, fib[i-2].occur, fib[i-2].occurSize, resTwo);
    sizeMid = ConvertIntToCharArray(middle, mid);

    size = addLarge(resTwo, size, mid, sizeMid, res);
    strncpy(fib[i].occur, res, size); 
    fib[i].occurSize = size;
  }  

  size = fib[n-1].occurSize - 1;
  for (j = size; j >= 0; j--) 
    printf("%c", fib[n-1].occur[j]);
  printf("\n");

  return 0;
}
