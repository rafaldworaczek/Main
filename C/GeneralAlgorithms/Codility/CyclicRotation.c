/*
Look at https://codility.com/demo/results/trainingXQGUW3-W5F/
*/

/* Solution 100% - Time complexity O(N) */

struct Results solution(int A[], int N, int K) {
    struct Results result;
    int idx, i;
    int *res = (int *) malloc(sizeof(int) * N);
    // write your code in C99 (gcc 4.8.2)
    for (i = 0; i < N; i++) {
        idx = (i + K) % N;       
        res[idx] = A[i];
    }        
        
    result.A = res;
    result.N = N;
    return result;
}
