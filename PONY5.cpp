#include<stdio.h>

#define ull unsigned long long

ull gcd(ull a, ull b) {
    if (b) return gcd(b, a%b);
    else return a;
}

inline ull sub(ull a, ull b) {
    return (a>b)?a-b : b-a;
}

inline ull mx(ull a, ull b) {
    return (a>b)?a:b;
}

ull getx() {
    char c;
    ull s=0;
    while ((c=getchar())<'0' || c >'9');
    do {
        s = s*10 + (ull)c-'0';
    } while ((c=getchar())>='0' && c <= '9');
    return s;
}

int main() {
    int t, n, c;
    ull a1, an, gcda = 0;
    t = (int) getx();
    while (t--) {
        c= (int)getx();
        n = (int)getx();
        int mxdif=0;
        
        gcda = 0;
        a1 = getx();
        //printf("a1=%llu\n", a1);
        for (int i=1; i<n; ++i) {
            an = getx();
            
            ull ss = sub(a1,an);
            //printf("ss=%llu\n", ss);
            mxdif = mx(mxdif, ss);
            if (mxdif) {
                gcda = gcd(gcda, ss);
            }
        }
        if (mxdif) {
            printf("Case #%d: %llu\n", c, gcda);
        } else {
            printf("Case #%d: I can\'t count that high\n", c);
        }
    }
}