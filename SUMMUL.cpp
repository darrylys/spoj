#include<stdio.h>

#define ll long long
#define MOD 1000000007

typedef struct {
    int m[2][2];
} Box;

Box getID() {
    Box c;
    c.m[0][0] = c.m[1][1] = 1;
    c.m[0][1] = c.m[1][0] = 0;
    return c;
}

Box getBase() {
    Box c;
    c.m[0][0] = 3;
    c.m[1][0] = -1+MOD;
    c.m[0][1] = 1;
    c.m[1][1] = 0;
    return c;
}

Box multiply(Box &a, Box &b, int mod) {
    Box c;
    c.m[0][0] = (int)(((ll)a.m[0][0]*b.m[0][0] + (ll)a.m[0][1]*b.m[1][0])%((ll)mod));
    c.m[0][1] = (int)(((ll)a.m[0][0]*b.m[0][1] + (ll)a.m[0][1]*b.m[1][1])%((ll)mod));
    c.m[1][0] = (int)(((ll)a.m[1][0]*b.m[0][0] + (ll)a.m[1][1]*b.m[1][0])%((ll)mod));
    c.m[1][1] = (int)(((ll)a.m[1][0]*b.m[0][1] + (ll)a.m[1][1]*b.m[1][1])%((ll)mod));
    return c;
}

Box mexp(Box& base, int exp, int mod, Box& ID) {
    if (exp == 0) return ID;
    if (exp == 1) return base;
    Box half = mexp(base, exp>>1, mod, ID);
    Box half2 = multiply(half, half, mod);
    if (exp&1) {
        half2 = multiply(half2, base, mod);
    }
    return half2;
}   

int main() {
    Box ID = getID();
    Box base = getBase();
    int t, n;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        if (n ==1) {
            printf("0\n");
            continue;
        }
        Box r = mexp(base, n-2, MOD, ID);
        printf("%d\n", (int)(((3LL*r.m[0][0] + (ll)r.m[1][0]) - n + MOD)%MOD));
    }
}
