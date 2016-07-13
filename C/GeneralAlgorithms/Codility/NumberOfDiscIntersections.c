/* Look at  https://codility.com/demo/results/training5GBSEK-P9D/ */

/* Solution 93% - Time complexity O(N*log(N)) */

int comparator (const void *p1, const void *p2) {
  const long long *a = (const long long *) p1;
  const long long *b = (const long long *) p2;
    
  if(a[0] == b[0]) {
    if (a[1] == b[1]) return 0; 
    if (a[1] < 0) return 1;    
      return -1;
  }
  else
    return a[0] - b[0];
}

int solution(int A[], int N) {
  long long P[N*2][2];
  int i, j;
  int count = 0;
  int inter = 0;
 
  for (i = 0, j = 0; i < N; i++, j += 2) {
    P[j][0] = i - A[i];
    P[j][1] = 1;
    P[j+1][0] = i + A[i];
    P[j+1][1] = -1;
  } 
    
  qsort(P, N * 2, sizeof P[0], comparator);

  for (i = 0; i < N * 2; i++) {
    if (P[i][1] == 1)
      inter += count;

      count += P[i][1];

    if (inter > 10E6)
      return -1;	
  }
 
  return inter;
}

