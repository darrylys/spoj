#include<stdio.h>

#define INV 250000001
#define MOD 1000000003

int F[1000005];

int main() {
    F[0] = 0;
    for (int i=1, i2;i<=1000000; ++i) {
        i2 = (int)(((long long)i*i)%MOD);
        F[i] = (int)(((i + (2*i2)%MOD + ((long long)i*((2*i2)%MOD-1))%MOD 
            + ((long long)i2*((long long)i2-1))%MOD) * INV + (long long)F[i-1]) % MOD);
    }
    
    int t, n;
    
    scanf("%d", &t);
    
    while (t--) {
        scanf("%d", &n);
        printf("%d\n", F[n]);
    }
    return 0;
}