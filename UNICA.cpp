#include<stdio.h>

#define ull unsigned long long
#define C(a) (a-'a')
#define MXN 66

ull dp[MXN][7][7][2];
ull sumdp[MXN];
ull dsum[MXN];

int getdp(int n, int _max, int _min, char fr) {
    return dp[n][_max+3][_min+3][fr-'a'];
}

inline int min(int a, int b) {
    return (a<b)?a:b;
}

inline int max(int a, int b) {
    return (a>b)?a:b;
}

void build() {
    sumdp[0] = 0;
    sumdp[1] = 2;
    sumdp[2] = 4;
    sumdp[3] = 8;
    dsum[0] = dsum[1] = dsum[2] = dsum[3] = 0;
    
    for (int i=4; i<MXN; ++i) {
        if (i&1) {
            dsum[i] = dsum[i-1] + dsum[i-2];
        } else {
            dsum[i] = sumdp[i-3];
        }
        sumdp[i] = 2LL*sumdp[i-1] - dsum[i];
    }


    dp[1][4][4][0] = 1;
    dp[1][2][2][1] = 1;
    
    for (int n=2; n<MXN; ++n) {
        
        // LHS
        for (int mxv = -3; mxv<=3; ++mxv) {
            for (int mnv = -3; mnv <= mxv; ++mnv) {
                
                // 'a'
                if (mxv + 1 < 4) {
                    int nmx = max(1, mxv+1);
                    int nmn = min(1, mnv+1);
                    
                    dp[n][nmx+3][nmn+3][0] += dp[n-1][mxv+3][mnv+3][0] + dp[n-1][mxv+3][mnv+3][1];
                }
                
                // 'b'
                if (mnv - 1 > -4) {
                    int nmx = max(-1, mxv-1);
                    int nmn = min(-1, mnv-1);
                    
                    dp[n][nmx+3][nmn+3][1] += dp[n-1][mxv+3][mnv+3][0] + dp[n-1][mxv+3][mnv+3][1];
                }
            }
        }
    }
}

int main() {
    build();
    ull N;
    scanf("%llu", &N);
    ull nN = N;
    int dn = 0;
    while (nN > sumdp[dn]) {
        nN -= sumdp[dn];
        dn++;
    }
    
    int a = 0;
    int b = 0;
    int maxv = 0, minv = 0;
    bool allowa, allowb;
    char buf[100];
    for (int n=0; n<dn; ++n) {
        allowa = maxv+1 < 4;
        allowb = minv-1 > -4;
        //printf("n=%d, a=%d, b=%d, maxv=%d, minv=%d, allowa=%d, allowb=%d\n", n, a, b, maxv, minv, allowa, allowb);
        
        if (allowa && allowb) {
            // check a
            ull tsum = 0;
            
            if (dn-n-1) {
                for (int mxv = -3; mxv<=3; ++mxv) {
                    for (int mnv = -3; mnv <= mxv; ++mnv) {
                        
                        bool success = true;
                        buf[n] = 'a';
                        int tmxv = mxv, tmnv = mnv;
                        for (int backn = n; success && backn >= 0; --backn) {
                            if (buf[backn] == 'a') {
                                if (tmxv + 1 < 4) {
                                    tmxv = max(1, tmxv+1);
                                    tmnv = min(1, tmnv+1);
                                } else {
                                    success = false;
                                }
                            } else {
                                if (tmnv - 1 > -4) {
                                    tmxv = max(-1, tmxv-1);
                                    tmnv = min(-1, tmnv-1);
                                } else {
                                    success = false;
                                }
                            }
                        }
                        
                        tsum += success ? (dp[dn-n-1][mxv+3][mnv+3][0] + dp[dn-n-1][mxv+3][mnv+3][1]) : 0;
                        
                    }
                }
            } else {
                tsum = 1;
            }
            
            //printf("\tdiv=%d tsum=%llu, nN=%llu\n", div, tsum, nN);
            
            if (nN > tsum) { //pick b
                nN -= tsum;
                maxv = max(-1, maxv-1);
                minv = min(-1, minv-1);
                buf[n] = 'b';
                putchar('b');
                b++;
                
            } else { //pick a
                maxv = max(1, maxv+1);
                minv = min(1, minv+1);
                buf[n] = 'a';
                putchar('a');
                a++;
            }
            
        } else if (allowa) {
            putchar('a');
            maxv = max(1, maxv+1);
            minv = min(1, minv+1);
            buf[n] = 'a';
            a++;
        } else if (allowb) {
            putchar('b');
            maxv = max(-1, maxv-1);
            minv = min(-1, minv-1);
            buf[n] = 'b';
            b++;
        } else {
            printf("BUG IN SYSTEM! DN=%d, n=%d, maxv=%d, minv=%d, nN=%llu, N=%llu\n", dn, n, maxv, minv, nN, N);
            return 1;
        }
        //printf("\n");
    }
    putchar('\n');
}
