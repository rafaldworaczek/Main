/*
Look at https://codility.com/demo/results/trainingE7KAZE-NH6/
*/

/* Solution 100% - Time complexity O(N) */
/* Binary search - max height */

#define MAX(x, y) (((x) > (y)) ? (x) : (y))

int traverse(struct tree *T) {
    int left = 0, right = 0;
    
    if (!T) 
        return 0; 

    if (T->l)
        left = traverse(T->l) + 1;
    
    if (T->r)    
        right = traverse(T->r) + 1;
    
    return MAX(left, right);
}


int solution(struct tree * T) {
    // write your code in C99 (gcc 4.8.2)
         
    return traverse(T);         
}
