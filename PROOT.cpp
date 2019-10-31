#include<stdio.h>
#define ll unsigned long long int

bool flag[50000];
int prime[7000];
int factor[7000];

int factorize(int k, int muchprime) {
    
    int num = k;
    int c = 0;
    int pl = 0;
    while (num>1 && c < muchprime) {
        
        int div = prime[c];
        if (num%div == 0) {
            factor[pl] = div;
            while (num%div == 0) {
                num /= div;
            }
            pl++;
        }
        c++;
    }
    if (num > 1) factor[pl++] = num;
    return pl;
}

int big_mod(int base, int exp, int mod) {
    if (exp == 0) return 1;
    if (exp == 1) return base%mod;
    else {
        int res = big_mod(base, exp>>1, mod);
        if (exp%2 == 0) {
            return (int)((((ll)res%mod)*((ll)res%mod))%mod);
        } else {
            return (int)((((((ll)res%mod)*((ll)res%mod))%mod)*((ll)base%mod))%mod);
        }
    }
}

int make_prime() {
    int cntr = 0, i;
    prime[cntr++] = 2;
    flag[0] = flag[1] = true;
    
    for (i=3; i*i <= 50000; i+=2) {
        if (!flag[i]) {
            prime[cntr++] = i;
            for (int j=i*i; j<50000; j+=(i<<1)) {
                flag[j] = true;
            }
        }
    }
    
    for (; i<50000; i+=2) {
        if (!flag[i]) prime[cntr++] = i;
    }
    
    return cntr;
}

int main() {
    int p, n, r;
    int much = make_prime();
    while (scanf("%d %d", &p, &n) && p) {
        if (p == 2) {
            while (n--) {
                scanf("%d", &r);
                printf("YES\n");
            }
            continue;
        }
        int m = factorize(p-1, much);
        bool result;
        while (n--) {
            scanf("%d", &r);
            result = true;
            if (r == 0 || r == 1) result = false;
            for (int i=0; result && i<m; i++) {
                result &= (big_mod(r,(p-1)/factor[i], p) != 1);
            }
            
            if (result) printf("YES\n");
            else printf("NO\n");
        }
    }
    return 0;
}