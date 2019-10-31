#include<stdio.h>

#define ull unsigned long long

ull e10[20];

void makeE10() {
    e10[0] = 1;
    for (int i=1; i<20; ++i) {
        e10[i] = e10[i-1]*10LL;
    }
}

int compressnumlen(ull N) {
    ull v = N;
    int pd = -1;
    int ctr = 0;
    
    while (v) {
        if (pd != v%10) {
            pd = v%10;
            ctr++;
        }
        v /= 10;
    }
    
    return ctr;
}

int main() {
    makeE10();
    
    ull M, N = 0;
    scanf("%llu", &M);
    
    //printf("M=%llu\n", M);
    
    ull nu = 9;
    int n = 1; //num of digits
    ull multipl = 1;
    
    while (1) {
        if (M > nu) {
            M -= nu;
            n++;
            nu = n*81*e10[n-2];
            multipl *= 10;
        } else {
            break;
        }
    }
    //printf("1.M=%llu\n", M);
    //printf("n=%d, multipl=%llu\n", n, multipl);
    
    ull lnu;
    ull tval;
    int cmpnl=0;
    
    int lfd; //fixed digits
    int fflfd;
    for (int xn = n; xn >= 2; --xn) {
        
        if (xn == n) {
            ull dec = 9LL*xn*e10[xn-2];
            for (int d=1; d<=9; ++d) {
                lnu = dec;
                if (M > lnu) {
                    M -= lnu;
                } else {
                    N = N*10+d;
                    lfd = d;
                    fflfd = lfd;
                    cmpnl++;
                    //printf("lfd=%d\n", lfd);
                    break;
                }
            }
        } else {
            for (int d=0; d<=9; ++d) {
                lnu = 9LL*xn*e10[xn-2] + multipl*(cmpnl-(d==lfd));
                //printf("N=%llu, M=%llu, d=%d, lnu=%llu, n=%d, xn=%d, lfd=%d, 10mltp=%llu, cmpnl=%d\n", N, M, d, lnu, n, xn, lfd, multipl, cmpnl);
                if (M > lnu) {
                    M -= lnu;
                } else {
                    cmpnl += (N%10 != d);
                    N = N*10+d;
                    lfd = d;
                    break;
                }
            }
        }
        multipl/=10;
    }
    
    //xn=1 (just brute force it)
    //printf("fN=%llu, fM=%llu\n", N, M);
    int lastdigit = 9;
    int dec;
    ull chn = N*10;
    int firstdigit = fflfd;
    for (int d=0; d<=9; ++d) {
        dec = compressnumlen(chn+d);
        if (lastdigit == firstdigit) {
            --dec;
        }
        if (M>dec) {
            M -= dec;
        } else {
            N = N*10+d;
            break;
        }
        lastdigit = d;
    }
    
    printf("%llu\n", N);
}
