#include<stdio.h>

#define ull unsigned long long
//#define DEBUG

int phimod[50];

int bigmod(int base, ull exp, int mod) {
    if (exp==0) return 1;
    if (exp==1) return base;
    int half = bigmod(base, exp>>1, mod);
    ull res = (ull)half * half;
    if (exp&1) {
        res %= mod;
        res *= base;
    }
    return (int)(res%mod);
}

int buildphimod() {
    phimod[0] = 1000000000;
    int L = 1;
    for (L=1; ; ++L) {
        if (phimod[L-1]%5 == 0) {
            phimod[L] = phimod[L-1]/5*2;
        } else {
            break;
        }
    }
    for (;;++L) {
        if (!(phimod[L-1]&1)) {
            phimod[L] = phimod[L-1]>>1;
        } else {
            break;
        }
    }
    return L;
}

int domath(int base, int tower) {
    int lexp = 0;
    for (int i=0; i<tower && phimod[i] > 1; ++i) {
        lexp++;
    }
    
    ull aexp = base % phimod[lexp-1];
    for (int i=lexp-2; i>=0; --i) {
        #ifdef DEBUG
        printf("base=%d, aexp=%llu, phimod=%d\n", base, aexp, phimod[i]);
        #endif
        
        aexp = (ull)bigmod(base, aexp, phimod[i]);
        aexp += phimod[i];
        // phimod[i] IFF threshold > 100
        // actually < 100, don't add!
        
    }
    return (int)(aexp%phimod[0]);
}

int main() {
    int t, e, a;
    buildphimod();
    
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &e, &a);
        #ifdef DEBUG
        printf("e=%d, a=%d\n", e, a);
        #endif
        if (a == 0 || e == 1) {
            printf("1\n");
            continue;
        }
        
        if (e == 0) {
            printf("%d\n", !(a&1));
            continue;
        }
        
        if (e == 2 && a == 3) {
            printf("16\n");
            continue;
        }
        
        int res = domath(e, a);
        if (e == 2 && a > 4) printf("...%09d\n", res);
        else if (e > 2 && e <= 9 && a > 2) printf("...%09d\n", res);
        else if (e > 9 && e < 1000000000 && a > 1) printf("...%09d\n", res);
        else if (e >= 1000000000 && a >= 1) printf("...%09d\n", res);
        else printf("%d\n", res);
        #ifdef DEBUG
        printf("========================================\n");
        #endif
    }
}
