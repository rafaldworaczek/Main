/*
Look at https://codility.com/demo/results/demoQD6SQT-KRJ/
*/

/* Solution 100% - Time complexity O(N) */

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
