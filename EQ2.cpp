#include<stdio.h>
#include<string.h>

#define ull unsigned long long

inline int max(int a, int b) {
    return (a>b)?a:b;
}

inline int max3(int a, int b, int c) {
    return max(a, max(b, c));
}

ull comp(char var[3][11], int lenv[3]) {
    int mxlen = max3(lenv[0], lenv[1], lenv[2]);
    
    int pv[3] = {lenv[0]-1, lenv[1]-1, lenv[2]-1};
    int mnd[3], mxd[3];
    int fx[11][2][2];
    
    for (int n=mxlen-1; n>=0; --n) {
        for (int i=0; i<4; ++i) {
            fx[n][i&1][(i>>1)&1] = 0;
        }
        
        for (int t=0; t<3; ++t) {
            if (pv[t] < 0) {
                mnd[t] = mxd[t] = 0;
            } else {
                if (var[t][pv[t]] == '?') {
                    mxd[t] = 9;
                    mnd[t] = !pv[t] && lenv[t]>1;
                } else {
                    mnd[t] = mxd[t] = var[t][pv[t]]-'0';
                }
            }
            //printf("[t=%d, [%d TO %d]] ", t, mnd[t], mxd[t]);
            --pv[t];
        }
       // printf("\n");
        
        for (int a=mnd[0]; a<=mxd[0]; ++a) {
            for (int b=mnd[1]; b<=mxd[1]; ++b) {
                
                for (int cr = 0, ci, co; cr<4; ++cr) {
                    ci = cr&1;
                    co = (cr>>1)&1;
                    
                    if (mnd[2] == mxd[2]) {
                        fx[n][ci][co] += (ci+a+b == 10*co+mnd[2]);
                    } else {
                        fx[n][ci][co] += (ci+a+b >= 10*co+mnd[2] && ci+a+b <= 10*co+mxd[2]);
                    }
                    /*
                    if (!ci && co) {
                        printf("%d+%d,;;,fx[%d][%d][%d]=%d\n", a, b, n, ci, co, fx[n][ci][co]);
                    }
                    */
                }
            }
        }
        /*
        for (int i=0; i<4; ++i) {
            printf("n=%d fx[%d][%d][%d]=%d\n", n, n, i&1, (i>>1)&1, fx[n][i&1][(i>>1)&1]);
            //fx[n][i&1][(i>>1)&1] = 0;
        }
        */
    }
    
    ull sum = 0;
    ull tmpsum = 0;
    char dt[11];
    for (int i=0; i<(1<<(mxlen-1)); ++i) {
        int v = i;
        tmpsum = 1;
        for (int x=mxlen-1; x>=0; --x) {
            dt[x] = v&1;
            v>>=1;
        }
        int carryin = 0;
        for (int x=mxlen-1; x>=0; --x) {
            tmpsum *= fx[x][carryin][dt[x]];
            carryin = dt[x];
            if (!tmpsum) break;
        }
        sum += tmpsum;
    }
    return sum;
    
}

int main() {
    char varA[3][11];
    char vin[35];
    int lenvA[3], c=1;
    
    while (scanf("%s", vin) != -1) {
        int len = strlen(vin);
        vin[len++] = '=';
        
        for (int i=0, p=0, s=0; i<len; ++i) {
            if (vin[i] == '+' || vin[i] == '=') {
                varA[s][p++] = '\0';
                s++;
                p=0;
            } else {
                varA[s][p++] = vin[i];
            }
        }
       // printf("READ [%s] + [%s] = [%s]\n", varA[0], varA[1], varA[2]);
        
        for (int i=0; i<3; ++i) lenvA[i] = strlen(varA[i]);
        ull r = comp(varA, lenvA);
        printf("Case %d: %llu\n", c++, r);
    }
}
