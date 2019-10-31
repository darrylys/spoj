#include<stdio.h>
#include<string.h>

#define MOD 1000000007
#define ll long long

char N[1<<10];
char K[1<<10];

int bigexpmod(int base, int exp, int mod) {
    if (exp == 0) return 1;
    if (exp == 1) return base%mod;
    
    int a = bigexpmod(base, exp>>1, mod);
    if (exp&1) {
        return (int)((( ((ll)a*a)%mod )*base)%mod);
    } else {
        return (int)(((ll)a*a)%mod);
    }
}

int singlemod(char* bignum, int len, int mod) {
/*
    int sum = 0;
    for (int i=0; i<len; i+=9) {
        
        int tsum=0;
        for (int j=0; j<9 && j+i<len; ++j) {
            tsum = tsum*10 + bignum[j+i]-'0';
            printf("\ttsum=%d\n", tsum);
        }
        
        //batch mod
        sum = (int)((sum*1000000000LL + tsum)%mod);
        
    }
    
    */
    
    int sum=0;
    for (int i=0; i<len; ++i) {
        sum = (int)((sum*10LL + bignum[i]-'0')%mod);
        
    }
    
    return sum;
}

int main() {
    int t;
    
    scanf("%d", &t);
    
    while (t--) {
        scanf("%s %s", N, K);
        int ln = strlen(N), kn = strlen(K);
        int _n = singlemod(N, ln, MOD-1);
        //printf ("_n=%d\n", _n);
        int _k = singlemod(K, kn, MOD);
        //printf ("_k=%d\n", _k);
        
        int r = (int)(((1LL-_k+MOD)*(1LL-bigexpmod(1-_k+MOD, _n-1, MOD)+MOD))%MOD);
        //if (r < 0) printf("neg %d\n", (int)(((ll)-r * (MOD-1))%MOD));
        //else printf("pos %d\n", r);
        
        if ((N[ln-1]-'0')%2 == 0) {
            r = (int)(((ll)r * (MOD-1))%MOD);
        }
        
        printf ("%d\n", r);
        
    }
    
    return 0;
}