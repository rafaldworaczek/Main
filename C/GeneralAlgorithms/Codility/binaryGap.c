/* Look at https://codility.com/demo/results/training2AU2ZK-3FT/ */

/* Solution 100% */

int solution(int N) {
    // write your code in C99 (gcc 4.8.2)
    int count = 0;
    int max = 0;
              
    while ((N & 0x1) == 0 && N) 
        N = N >> 1;
                            
    while (N > 0) {
                
        if ((0x01 & N) == 0)           
            count++;                    
        else
            count = 0;
         
        if (count > max) 
            max = count;
            
        N = N >> 1;    
    }
      
    return max;
}
