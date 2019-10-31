#include<stdio.h>

#define ull unsigned long long

ull gcd(ull a, ull b) {
    if (b == 0) return a;
    else return gcd(b, a%b);
}

int main() {
    int t;
    
    ull x1, x2, x3;
    scanf("%d", &t);
    while (t--) {
        scanf("%llu %llu %llu", &x1, &x2, &x3);
        
        ull a = gcd(x3, x1);
        ull r = (x3-a)/(x3-x1/a*x2);
        
        int id;
        ull s=0;
        ull el=a;
        for (id=0; s<x3; ++id) {
            s += el;
            el *= r;
        }
        
        printf("%d\n", id);
        printf("%llu", a);
        el=a*r;
        for (int i=1; i<id; ++i) {
            printf(" %llu", el);
            el *= r;
        }
        putchar('\n');
    }
    return 0;
}
