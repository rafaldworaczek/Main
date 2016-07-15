/*
Look at https://codility.com/demo/results/training36E38H-87A/
Solution 100% - Time complexity O(N + M) 

The prefix sum is used in this algorithm. The main idea behind it 
is counting the number of A, C, T, G in each step and put
it into an array. 

*/

#define MIN(x, y) (((x) < (y)) ? (x) : (y))

int findCharIdx(char *c, char *chars, int n) {
    int i = 0;
    for (i = 0; i < n; i++)
        if (*c == chars[i])
            return i;
            
    return 0;    
}

struct Results solution(char *S, int P[], int Q[], int M) {
    struct Results result;
    // write your code in C99 (gcc 4.8.2)
    int i, j;
    int idx;
    int n = strlen(S);
    int letters = 4;
    char chars[] = {'A', 'C', 'G', 'T'};
    int *res = calloc(M, sizeof(int));
    int x;
    int **A = (int **) calloc(n, sizeof(int *));
    
    for (i = 0; i < n; i++) 
        A[i] = (int *) calloc(letters, sizeof(int));
        
    idx = findCharIdx(&S[0], chars, 4);    
    A[0][idx] = 1;    
    
    for (i = 1; i < n; i++) {        
        idx = findCharIdx(&S[i], chars, letters);
        A[i][idx]++;
        
        for (j = 0; j < letters; j++)             
            A[i][j] += A[i-1][j];                  
    }
            
    for (i = 0; i < M; i++) {
        idx = findCharIdx(&S[P[i]], chars, letters);
                
        for (j = 0; j < letters; j++) {                   
            if (j == idx) 
                x = A[P[i]][j] - 1;
            else    
                x = A[P[i]][j];
                
            if (A[Q[i]][j] - x > 0) {               
                res[i] = j + 1;
                break;
            }
        }
    } 
    
    result.A = res;
    result.M = M;
    return result;
}
