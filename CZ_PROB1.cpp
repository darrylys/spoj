#include<cstdio>
#include<algorithm>

using namespace std;

bool flag[7994];
int prime[1010];
int sqprime[510];
int table[7994][4];

int main() {
    // begin precomputation
    //sieve
    flag[0] = flag[1] = true;
    int np = 0, i, sqp = 0;
    prime[0] = 2;
    for (i=3; i*i < 7994; i+=2) {
        if (!flag[i]) {
            prime[np++] = i;
            for (int j=i*i; j<7994; j+=2*i) {
                flag[j] = true;
            }
        }
    }
    
    for (; i<7994; i+=2) {
        if (!flag[i]) prime[np++] = i;
    }
    //printf("np=%d\n", np);
    
    //get square primes
    sqprime[0] = 2;
    sqp = 1;
    for (i=2; i*i<7994; i+=2) {
        for (int j=1; j*j<7994; j+=2) {
            if (i*i + j*j >= 7994) break;
            if (!flag[i*i + j*j]) {
                sqprime[sqp++] = i*i+j*j;
            }
        }
    }
    
    // sort it
    sort (sqprime, sqprime + sqp);
    
    //printf("sqp = %d\n", sqp);
    //printf("largest sqprime = %d\n", sqprime[sqp-1]);
    
    //building the table
    table[2][1] = 1; table[2][2] = 1; table[2][3] = 0;
    table[3][1] = 1; table[3][2] = 1; table[3][3] = 1;
    table[4][1] = 1; table[4][2] = 2; table[4][3] = 1;
    
    for (i=5; i<=sqprime[sqp-1]; i++) {
        table[i][1] = 1;
        table[i][2] = table[i-2][2] + 1;
        table[i][3] = table[i-3][2] + table[i-3][3] + 1;
    }
    
    // end precomputation, main program runs now
    int t, n, k;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &k);
        n--;
        int sum = 0;
        for (int l = 1; l<=k; l++) {
            sum += table[sqprime[n]][l];
        }
        printf("%d\n", sum);
    }
    
    return 0;
}