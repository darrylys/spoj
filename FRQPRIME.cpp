#include<stdio.h>

#define N 105000
#define NOP 10010
#define ll long long

bool flag[N];
int prime[NOP];

int make_prime() {
    int cntr = 2;
    prime[0] = 1;       //fake prime (used for terminal reasons)
    prime[1] = 2;
    flag[2] = false;
    int i=0;
    for (i=3; i*i <= N; i+=2) {
        if (!flag[i]) {
            prime[cntr++] = i;
            for (int j=i*i; j<N; j+= (i<<1)) {
                flag[j] = true;
            }
        }
    }
    
    for ( ; i<N; i+=2) {
        if (!flag[i]) prime[cntr++] = i;
    }
    return cntr;
}

int main() {
    int num = make_prime();
    int test, n, k, start, np, end, diff;
    ll result;
    scanf("%d", &test);
    while (test--) {
        scanf("%d %d", &n, &k);
        
        if (k == 0) {
            printf("%lld\n", 99999*50000LL);
            continue;
        }
        
        result = 0;
        start = 1;
        end = k;
        for (int i=k; ; i++) {
            if (n - prime[i] + 1 < 0) break;
            
            //check behind
            diff = prime[start] - prime[start-1];
            result += diff * (n - prime[end] + 1);
                        
            end = i+1; //advance to next prime
            
            //erasing start prime;
            start++;
        }
        printf("%lld\n", result);
    }
    return 0;
}