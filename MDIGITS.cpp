#include<stdio.h>
#include<string.h>

int dp[10][10][10];

int makedp() {
    //n=1
    for (int d=0; d<=9; ++d) {
        for (int i=0; i<=d; ++i) {
            dp[1][d][i] = 1;
        }
    }
    
    //n>2
    for (int n=2, mul=10; n<=9; ++n, mul*=10) {
        //d==0
        for (int i=0; i<=9; ++i) {
            if (i==0) {
                dp[n][0][i] = dp[n-1][9][i] + mul;
            } else {
                dp[n][0][i] = dp[n-1][9][i];
            }
        }
        
        //d>0
        for (int d=1; d<=9; ++d) {
            for (int i=0; i<=9; ++i) {
                if (i==d) {
                    dp[n][d][i] = dp[n-1][9][i] + dp[n][d-1][i] + mul;
                } else {
                    dp[n][d][i] = dp[n-1][9][i] + dp[n][d-1][i];
                }
            }
        }
    }
}

int tochar(int a, char* buf) {
    if (a) {
        int n = tochar(a/10, buf);
        buf[n] = a%10+'0';
        return n+1;
    }
    return 0;
}

void clearbuf(int* buf) {
    for (int i=0; i<=9; ++i) buf[i]=0;
}

void dcalc(int A, int* buf) {
    clearbuf(buf);
    
    char aBuf[13];
    int aLen = tochar(A, aBuf);
    aBuf[aLen] = '\0';
    //printf("aBuf=%s\n", aBuf);
    
    int texp=1;
    buf[0] = 1; //force zero-in
    for (int i=1; i<aLen; ++i, texp*=10) {
        for (int d=0; d<=9; ++d) {
            buf[d] += dp[i][9][d] - dp[i][0][d];
        }
    }
    
    int cert[10];
    clearbuf(cert);
    //printf("texp=%d\n", texp);
    
    for (int n=0; n<aLen; ++n) {
        if (n==0) {
            if (aBuf[n]-'0' > 1) {
                for (int i=0; i<=9; ++i) {
                    buf[i] += dp[aLen-n][aBuf[n]-'0'-1][i] - dp[aLen-n][0][i] + (aBuf[n]-'0')*cert[i]*texp;
                }
            }
        } else {
            if (aBuf[n]-'0') {
                for (int i=0; i<=9; ++i) {
                    buf[i] += dp[aLen-n][aBuf[n]-'0'-1][i] + (aBuf[n]-'0')*cert[i]*texp;
                }
            }
        }
        texp/=10;
        cert[aBuf[n]-'0']++;
    }
}

int main() {
    makedp();
    int a, b, ra, rb;
    int reA[10], reB[10];
    while (1) {
        scanf("%d%d", &a, &b);
        if (a|b) {
            if (a>b) {
                rb=a+1; ra=b;
            } else {
                rb=b+1; ra=a;
            }
            dcalc(ra, reA);
            dcalc(rb, reB);
            for (int i=0; i<=9; ++i) {
                printf("%d ", reB[i] - reA[i]);
            }
            printf("\n");
        } else {
            break;
        }
    }
}
