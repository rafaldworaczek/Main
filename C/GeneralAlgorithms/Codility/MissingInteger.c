/*
Look at https://codility.com/demo/results/trainingUKAEZR-43G/ 

There is N integers so if we take numbers smaller than N + 1, 
at least one has to be missing.       

Solution 100% - Time complexity O(N) 
*/

int solution(int A[], int N) {
    // write your code in C99 (gcc 4.8.2)
    int i = 0;

    unsigned int *res = calloc(N + 2, sizeof(int));

    for (i = 0; i < N; i++) {
        if (A[i] <= 0 || A[i] > N + 1) 
            continue;
        
        res[A[i]] = 1;
    }
    
    for (i = 1; i <= N + 1; i++)
        if (!res[i])
            return i;

    //This should be never reached            
    return 0;    
}
