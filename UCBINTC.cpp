/*

AC 0.00s 3.3M SPOJ

Algo: ad-hoc

for each index i, keep an array which index identifies whether it is possible to sum 2 numbers
to equal to index.
    i.e. MAP[i] = true if there exists j, k | 0 <= j,k < i and A[j] + A[k] == i, false otherwise

the MAP can be constructed in O(N^2). The space to keep this array is O(N^3) which is impossible.
However, the complete MAP is not needed, just the MAP needed for particular index i in array A.
Moreover, MAP for index i contains MAP for index (i-1). This allows for incremental building
while removing useless MAP and maintain memory requirement in O(N^2)
    
for each index i, find out whether there MAP[A[i] - A[j]] == true | 0 <= j < i.

Space: O(600000)
Time: O(N^2)

*/

#include <stdio.h>  

#define MAXA (600005)
#define MAXN (5005)
#define DX (300000)

char flag[MAXA];
int A[MAXN];

inline void set(int x) {
    flag[x+DX] = 1;
}

inline char get(int x) {
    return flag[x+DX];
}

int main() {
    int N;
    
    scanf("%d", &N);
    
    for (int i=0; i<N; ++i) {
        scanf("%d", &A[i]);
    }
    
    int sum=0;
    set(2*A[0]);
    for (int i=1; i<N; ++i) {
        for (int j=0; j<i; ++j) {
            if (get(A[i]-A[j])) {
                sum++;
                break;
            }
        }
        
        // update flags
        for (int j=0; j<i; ++j) {
            set(A[i]+A[j]);
        }
        set(2*A[i]);
    }
    
    printf("%d\n", sum);
    
    return 0;
}
