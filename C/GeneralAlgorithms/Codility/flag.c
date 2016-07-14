/*
Look at https://codility.com/demo/results/trainingDYRQDX-WCV/
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

int fillPeak(int *p, int *A, int N) {
        
    int i = 0, idx = 0;
    for (i = 1; i < N - 1; i++) 
        if (A[i] > A[i-1] && A[i] > A[i+1]) 
            p[idx++] = i;
    
    return idx;    
}

int check(int k, int *p, int nr) {
    int i = 0;
    int count = 1;
    int curr = p[0];

    if (k == 1) return 1;

    for (i = 1; i < nr; i++)  {
        if (p[i] - curr < k)
            continue;
            
        curr = p[i];    
        if (++count == k) {
            return 1;
        }
    }
    
    return -1;            
}

int solution(int A[], int N) {
    // write your code in C99 (gcc 4.8.2)
    int peaks[N];
    int k = 0;
    int nr = 0;
    int max = 0;
    int left, right;
    
    nr = fillPeak(peaks, A, N);
        
    left = 1;
    right = nr;
     
    //Binary search             
    while (left <= right) {
        k = (right + left) / 2;          
     
        if (check(k, peaks, nr) == 1) {          
            max = k;            
            left = k + 1;
        }
        else
            right = k - 1;        
    }
    
    return max;
}
