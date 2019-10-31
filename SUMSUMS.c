// impl : Mathematical formula: Extended-Euclid + Inverse Modulo + Recusive to Direct formula + BigMod

#include<stdio.h>
#define ll unsigned long long int
#define MOD 98765431

int varx, vary, gcda;

void extended_euclid(int a, int b) {
    int x = 0, lastx = 1;
    int y = 1, lasty = 0;
    int c, cd;
    while (b != 0) {
        int quotient = a / b;
        c = a%b;
        a=b;
        b=c;
        cd = x;
        x = lastx - quotient*x;
        lastx = cd;
        cd = y;
        y = lasty - quotient*y;
        lasty = cd;
    }
    varx = lastx; vary = lasty; gcda = a;
}

int big_mod(int base, int exp, int mod) {
    if (exp == 0) return 1;
    if (exp == 1) return base%mod;
    else {
        if (exp%2 == 0) {
            int res = big_mod(base, exp/2, mod);
            return (int)((((ll)res%mod)*((ll)res%mod))%mod);
        } else {
            int res = big_mod(base, exp/2, mod);
            return (int)((((((ll)res%mod)*((ll)res%mod))%mod)*((ll)base%mod))%mod);
        }
    }
}

int main() {
    int n, t, i, j, k, l, res;
    scanf("%d%d", &n, &t);
    int cow[n];
    ll sum = 0;
    for (i=0;i<n;i++) {
        scanf("%d", &cow[i]);
        sum = sum + cow[i];
    }
    //printf("sum=%llu\n", sum);
    extended_euclid(n,MOD);
    //printf("varx=%d vary=%d\n", varx, vary);
    int x = varx;
    if (x < 0) x += MOD;

    int a = big_mod(n-1, t, MOD);
    if (t%2) a++;
    else a--;
    if (a<0) a+= MOD;
    a %= MOD;
    int gmodm = (int)((((ll)a%MOD)*((ll)x%MOD))%MOD);

    a = big_mod(n-1, t-1, MOD);
    if (t%2) a--;
    else a++;
    if (a<0) a+= MOD;
    a %= MOD;
    int gprevmodm = (int)((((ll)a%MOD)*((ll)x%MOD))%MOD);

    int fmodm = (int)((((ll)(n-1)%MOD)*((ll)gprevmodm%MOD))%MOD);
    //printf("f%%m=%d, g%%m=%d\n", fmodm, gmodm);
    for (i=0;i<n;i++) {
        res = (int)( ( ((fmodm*(ll)cow[i])%MOD) + ((gmodm*((sum-cow[i])%MOD))%MOD)%MOD) %MOD);
        printf("%d\n", res);
    }
    return 0;
}
