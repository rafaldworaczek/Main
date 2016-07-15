/*
Look at https://codility.com/demo/results/trainingB69KK7-FTP/
*/

/* Solution 100% - Time complexity O(N) */

int comparator(const void *a, const void *b)
{
   return (*(int *)a - *(int *)b);
}

int solution(int A[], int N) {
    // write your code in C99 (gcc 4.8.2)
    int i = 0;
    qsort(A, N, sizeof(int), comparator);
            
    for (i = 0; i < N; i++) 
        if (A[i] != (i + 1))
            return 0;
            
    return 1;
}


