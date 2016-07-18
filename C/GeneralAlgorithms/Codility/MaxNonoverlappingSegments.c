/*
Look at https://codility.com/demo/results/trainingHJFJWQ-XFT/
*/

/* Solution 100% - Time complexity O(N) */

int checkOverlap(int x1, int x2, int y1, int y2) {
    
    if (x1 <= y2 && y1 <= x2) 
        return 1;
    return 0;
}


int solution(int A[], int B[], int N) {
    // write your code in C99 (gcc 4.8.2)
    int count = 1;
    int i = 0;
    int currS, currE;
    
    if (N <= 1) return N;

    currS = A[N - 1];
    currE = B[N - 1];
    for (i = N - 2; i >= 0; i--) { 
       
        if (checkOverlap(currS, currE, A[i], B[i])) {
            if(currS < A[i]) {
                currS = A[i];
                currE = B[i];
            }
        }
        else {
            count++;
            currS = A[i];
            currE = B[i];
        }
    }
        
    return count;
}
