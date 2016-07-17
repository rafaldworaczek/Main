/*
Look at https://codility.com/demo/results/demoQD6SQT-KRJ/
*/

/* Solution 100% - Time complexity O(N) */
/*Dynamic programming problem */

int solution(int A[], int N) {
  // write your code in C99 (gcc 4.8.2)
  int i = 0;
  long int rsum = 0, lsum = 0;
      
  if (N < 1)
    return -1;
  
  for (i = 0; i < N; i++) 
    rsum += A[i]; 
  
  for (i = 0; i < N; i++)  {
    rsum -= A[i];    
      
    if (lsum == rsum) 
      return i;      
      
    lsum += A[i];
  }   
  
  return -1;
}

// you can write to stdout for debugging purposes, e.g.
// printf("this is a debug message\n");
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

int solution(int A[], int N) {
    // write your code in C99 (gcc 4.8.2)
    int *res = (int *) calloc(N, sizeof(int));
    int i = 0, j = 0;

    res[0] = A[0];    
    for (i = 1; i < N; i++) {  
        res[i] = -0xFFFFFFF;
        for (j = 1; j <= 6; j++) {
            if ((i - j) < 0) 
                break;

            res[i] = MAX(res[i-j] + A[i], res[i]);   
        }               
    }
    
    return res[N - 1];
}
