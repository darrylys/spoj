#include<stdio.h>

#define ll long long
#define MOD 1000000007
#define INV 500000004

typedef struct {
    int m[2][2];
} Box;

Box multiply(Box &a, Box &b) {
    Box c;
    c.m[0][0] = (int)(((ll)a.m[0][0]*b.m[0][0] + (ll)a.m[0][1]*b.m[1][0])%((ll)MOD));
    c.m[0][1] = (int)(((ll)a.m[0][0]*b.m[0][1] + (ll)a.m[0][1]*b.m[1][1])%((ll)MOD));
    c.m[1][0] = (int)(((ll)a.m[1][0]*b.m[0][0] + (ll)a.m[1][1]*b.m[1][0])%((ll)MOD));
    c.m[1][1] = (int)(((ll)a.m[1][0]*b.m[0][1] + (ll)a.m[1][1]*b.m[1][1])%((ll)MOD));
    return c;
}

Box fibo(ll n, Box &base) {
    if (n == 1) {
        return base;
    }
    Box c = fibo(n>>1, base);
    if (n&1) { //odd
        Box mid = multiply(c, base);
        return multiply(c, mid);
    } else { //even
        return multiply(c,c);
    }
}

int int_fibo(ll n, Box &base) {
    Box c = fibo(n, base);
    return c.m[0][1];
}

int main() {
    Box base;
    base.m[0][0] = 1;
    base.m[0][1] = 1;
    base.m[1][0] = 1;
    base.m[1][1] = 0;
    
    int testcase;
    ll n;
    int f1, f2;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%lld", &n);
        if (n == 0) {
            printf("0\n");
        } else {
            f1 = int_fibo(n<<2, base);
            f2 = int_fibo(n<<1, base);
            f2 = (int)(((ll)f2 * f2 )% MOD);
            
            printf("%d\n", (int)(((ll)(INV)*((f1 + f2)%MOD))%MOD));
        }
    }
    return 0;
}