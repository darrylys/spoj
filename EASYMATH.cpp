#include<stdio.h>

#define ull unsigned long long
#define ui unsigned int

ull gcd(ull a, ull b){
    if (b == 0) return a;
    else return gcd(b, a%b);
}

ull lcm(ull a, ull b){
    return a/gcd(a,b)*b;
}

ull myc(ull n, ull* div) {
    ull count2=0;
    
    for (int i=0; i<32; ++i) {
        //printf("i=%d\n", i);
        int v = i;
        int zc = 0;
        int act=0;
        ull xval = 1;
        while (v) {
            if (v&1) {
                xval = lcm(xval, div[zc]);
                act++;
            }
            zc++;
            v>>=1;
        }
        if (act&1) {
            count2 -= n/xval;
        } else {
            count2 += n/xval;
        }
    }
    return count2;
}

int main() {
    ull div[5];
    int t; ull n, m, a, d;
    scanf ("%d", &t);
    while (t--) {
        scanf("%llu %llu %llu %llu", &n, &m, &a, &d);
        div[0] = a;
        for (int i=1; i<5; ++i) {
            div[i] = div[i-1]+d;
        }
        //printf("sss\n");
        ull res = myc(m, div) - myc(n-1, div);
        printf("%llu\n", res);
    }
}
