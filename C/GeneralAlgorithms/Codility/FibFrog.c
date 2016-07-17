/*
Look at https://codility.com/demo/results/training32MF2R-TH4/
*/

/* Solution 100% - Time complexity O(N * log(N)) */

#define MIN(x, y) (((x) < (y)) ? (x) : (y))
#define INT_MAX 0xFFFFFFF

int *preallocateFib(int N) {
    int *res = (int *) malloc(N * sizeof(int));
    int i;
    
    res[0] = 1;
    res[1] = 2;
    
    for (i = 2; i < N; i++)
        res[i] = res[i - 1] + res[i - 2];
    
    return res;
}

int solution(int A[], int N) {
    // write your code in C99 (gcc 4.8.2)
    int i = 0, j = 0;
    //25 is enough since N is from 0 to 100,000
    int fibnr = 25;    
    int *fib = preallocateFib(fibnr);
    int *res = (int *) calloc(N + 1, sizeof(int));
       
    res[N] = -1;
    
    for (i = 0; i <= N; i++) {         
        if (i != N && A[i] == 0) continue;
       
        res[i] = INT_MAX;
         
        for (j = 0; j < fibnr; j++) {
            if ((i - fib[j]) < -1)
                break;        
                                                
            if ((i - fib[j]) == -1)               
                res[i] = 1;            
            else 
                if (A[i - fib[j]] != 0)
                    res[i] = MIN(res[i], res[i - fib[j]] + 1);          
        }               
    }
    
    return res[N] == INT_MAX ? -1 : res[N];
}
