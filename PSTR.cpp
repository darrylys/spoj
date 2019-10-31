#include<stdio.h>

#define MOD 1000000007
#define ll long long

int vstc[200];
int vnnv[200];
char sgn[200];

char flag[1010];
int prime[1010];

int factor[15];

int getprimes() {
    prime[0] = 2;
    int f=1;
    for (int i=3; i*i<=1000000; i+=2) {
        if (!flag[i]) {
            prime[f++] = i;
            for (int j=i*i; j<=1000; j+=i) {
                flag[j] = 1;
            }
        }
    }
    return f;
}

int bigmod(int base, int exp, int mod) {
    if (exp==0) return 1;
    if (exp==1) return base;
    int half = bigmod(base, exp>>1, mod);
    if (exp&1) {
        return (int)((((ll)half * half)%mod * (ll)base)%mod);
    } else {
        return (int)(((ll)half * half)%mod );
    }
}

int factorize(int n, int* fac, int nprimes) {
    
    int val = n;
    int i = 0;
    int fc = 0;
    while (i<nprimes) {
        
        if (val < prime[i]) {
            break;
        }
        
        if (val%prime[i] == 0) {
            fac[fc++] = prime[i];
            do { 
                val /= prime[i];
            } while (val%prime[i] == 0);
        }
        i++;
    }
    if (val > 1) {
        fac[fc] = val;
        fc++;
    }
    return fc;
}

int main() {
    
    int nprimes = getprimes();
    
    int t, K,N, nfacs;
    scanf("%d", &t);
    while(t--){
        scanf("%d %d", &K, &N);
        
        if (N == 1) {
            printf("%d\n", K);
            continue;
        }
        
        nfacs = factorize(N, factor, nprimes);
        
        int bexp = N;
        for (int i=0; i<nfacs; ++i) {
            bexp /= factor[i];
        }
        
        if (nfacs&1) {
            sgn[0] = -1;
        }else {
            sgn[0] = 1;
        }
        
        int base = bigmod(K, bexp, MOD);
        
        vstc[0] = base;
        vnnv[0] = 0;
        
        int top = 1;
        int sum = 0;
        while (top) {
            
            int cval = vstc[top-1];
            int vnv = vnnv[top-1];
            char sign = sgn[top-1];
            
            --top;
            
            sum = sum + sign*cval;
            if (sum >= MOD) sum -= MOD;
            if (sum < 0) sum += MOD;
            
            if (vnv < nfacs) {
                for (int i=vnv; i<nfacs; ++i) {
                    vstc[top] = bigmod(cval, factor[i], MOD);
                    vnnv[top] = i+1;
                    sgn[top] = -sign;
                    ++top;
                }
            }
        }
        
        printf("%d\n", sum);
    }
    return 0;
}
