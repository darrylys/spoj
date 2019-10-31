#include<stdio.h>
#include<string.h>

#define ull unsigned long long

// autoinit all 0
ull dp[20][10][7776];
ull ff[20][7776];
ull sff[20];

/*
[   0  1   2  3   4  5   6  7   8  9 ]                          [   0   2   4   6   8  1  3  5  7  9 ]
[ 012 01 012 01 012 01 012 01 012 01 ] => all states. <=        [ 012 012 012 012 012 01 01 01 01 01 ]
[ 01  0  01  0  01  0  01  0  01  0  ] => correct states.    => [ 01  01  01  01  01  0  0  0  0  0  ]
*/

int CV(int a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7, int a8, int a9) {
    int odd = a9 + (a7<<1) + (a5<<2) + (a3<<3) + (a1<<4);
    int even = a8 + a6*3 + a4*9 + a2*27 + a0*81;
    
    return (even<<5) + odd;
}

int spi[10] = {
    CV(1, 0, 0, 0, 0, 0, 0, 0, 0, 0),
    CV(0, 1, 0, 0, 0, 0, 0, 0, 0, 0),
    CV(0, 0, 1, 0, 0, 0, 0, 0, 0, 0),
    CV(0, 0, 0, 1, 0, 0, 0, 0, 0, 0),
    CV(0, 0, 0, 0, 1, 0, 0, 0, 0, 0),
    CV(0, 0, 0, 0, 0, 1, 0, 0, 0, 0),
    CV(0, 0, 0, 0, 0, 0, 1, 0, 0, 0),
    CV(0, 0, 0, 0, 0, 0, 0, 1, 0, 0),
    CV(0, 0, 0, 0, 0, 0, 0, 0, 1, 0),
    CV(0, 0, 0, 0, 0, 0, 0, 0, 0, 1)
};

int CVA(int* a) {
    return CV(a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7], a[8], a[9]);
}

void clearbuf(int* buf) {
    for (int i=0; i<10; ++i) buf[i] = 0;
}

void ECV(int a, int* buf) {
    //memset(buf, 0, 10*sizeof(buf[0]));
    clearbuf(buf);
    
    int odd = a&31;
    int even = a>>5;
    
    int i = 9;
    while(odd) {
        buf[i] = odd&1;
        odd >>= 1;
        i-=2;
    }
    
    i=8;
    while(even) {
        buf[i] = even%3;
        even /= 3;
        i -= 2;
    }
}

void printFF() {
    printf("\nFF\n====================================\n");
    int buf[10];
    ull sum=0;
    for (int n=1; n<4; ++n) {
        printf("\nFF; n=%d\n======================================-----------------------------------------------\n", n);
        sum =0;
        for (int i=0; i<7776; ++i) {
            ECV(i, buf);
            printf("[");
            for (int j=0; j<10; ++j) {
                printf("%d ", buf[j]);
            }
            printf("] = %d\n", ff[n][i]);
            sum += ff[n][i];
        }
        printf("[SUM]=%llu\n", sum);
    }
    printf("=======================================\n");
}

void printDP() {
    printf("\nDP\n====================================\n");
    int buf[10];
    ull sum = 0;
    for (int n=1; n<4; ++n) {
        sum = 0;
        for (int d=9; d<=9; ++d) {
            //sum = 0;
            printf("\nd=%d\n=======================================\n", d);
            for (int i=0; i<7776; ++i) {
                ECV(i, buf);
                printf("[");
                for (int j=0; j<10; ++j) {
                    printf("%d ", buf[j]);
                }
                printf("] = %d\n", dp[n][d][i]);
                sum += dp[n][d][i];
            }
        }
        printf("[SUM]=%llu\n", sum);
    }
    printf("=======================================\n");
}

// ok!
void vDP1() {
    int did[10];
    
    // n==1
    for (int d=0; d<=9; ++d) {
        
        for (int dx=0; dx<=d; ++dx) {
            //memset(did, 0, 10*sizeof(did[0]));
            clearbuf(did);
            
            did[dx] = 1;
            
            int ec = CVA(did);
            dp[1][d][ec] = 1;
        }
    }
    
    // n>=2
    for (int n=2; n<=19; ++n) {
        
        //d==0;
        for (int i=0, vj; i<7776; ++i) {
            ECV(i, did);
            if (did[0] < 2) did[0]++;
            else did[0] = 1;
            dp[n][0][CVA(did)] += dp[n-1][9][i];
        }
        
        //d>=1;
        for (int d=1; d<=9; ++d) {
            
            for (int i=0; i<7776; ++i) {
                dp[n][d][i] = dp[n][d-1][i];
            }
            
            for (int i=0; i<7776; ++i) {
                ECV(i, did);
                if (d&1) {
                    did[d] = !did[d];
                } else {
                    if (did[d] < 2) did[d]++;
                    else did[d] = 1;
                }
                dp[n][d][CVA(did)] += dp[n-1][9][i];
            }
        }
    }
}

void vDP2() {
    int did[10];
    int cpat[10];
    
    int dix[10];
    int bin[10];
    int dx;
    
    //n=0
    for (int i=0, v, c; i<32; ++i) {
        //memset(did, 0, 10*sizeof(did[0]));
        clearbuf(did);
        
        v = i;
        c = 0;
        while (v) {
            did[c] = v&1;
            v>>=1;
            c+=2;
        }
        
        ff[0][CVA(did)] = 1;
    }
    
    for (int n=1; n<=19; ++n) {
        
        for (int i=0; i<7776; ++i) {
            ECV(i, did);
            
            clearbuf(cpat);
            
            dx=0;
            for (int x=1; x<=9; x+=2) cpat[x] = did[x];
            for (int x=0; x<9; x+=2) {
                switch (did[x]) {
                    case 0:
                        dix[dx++] = (x+1);
                    break;
                    
                    case 1:
                        dix[dx++] = -(x+1);
                    break;
                    
                    case 2:
                        cpat[x] = 1;
                    break;
                }
            }
            
            for (int dc=0, dv,c,k; dc<(1<<dx); ++dc) {
                
                dv = dc;
                c=0;
                //memset(bin, 0, 10*sizeof(bin[0]));
                clearbuf(bin);
                
                while (dv) {
                    bin[c++] = dv&1;
                    //bin[c++] = (dv&1) ? 2 : 0;
                    dv >>= 1;
                }
                
                for (int dd=0; dd<dx; ++dd) {
                    if (dix[dd]<0) {
                        int jx = -dix[dd]-1;
                        if (bin[dd]==1) cpat[jx] = 2;
                        else cpat[jx] = 0;
                    } else {
                        int jx=dix[dd]-1;
                        cpat[jx]=bin[dd];
                    }
                }
                
                // did = used digits
                // cpat = such that did+cpat=balanced
                /*
                if (n==1 && i==40) {
                    if (dp[n][9][CVA(cpat)]) {
                        printf("<<");
                        for (int uu=0; uu<10; ++uu) printf("%d ", cpat[uu]);
                        printf(">>, dc=%d\n", dc);
                    }
                }*/
                ff[n][i] += dp[n][9][CVA(cpat)];
            }
        }
    }
}

void vDP3() {
    for (int n=1; n<=19; ++n) {
        sff[n] = sff[n-1];
        for (int d=(n==1)?0:1; d<=9; ++d) {
            sff[n] += ff[n-1][spi[d]];
        }
    }
}

int recfill(char* buf, ull n) {
    if (n) {
        int fi = recfill(buf, n/10);
        buf[fi] = n%10+'0';
        return fi+1;
    }
    return 0;
}


int fill(char* buf, ull num) {
    int x = recfill(buf, num);
    buf[x] = '\0';
    return x;
}

ull calc(ull num) {
    
    char snum[25];
    int used[10];
    int temp[10];
    
    //memset(used, 0, 10*sizeof(used[0]));
    //memset(temp, 0, 10*sizeof(temp[0]));
    clearbuf(used);
    clearbuf(temp);
    
    int len = fill(snum, num);
    //printf("len=%d, snum=%s\n", len, snum);
    ull res = sff[len-1];
    //printf("BEGIN:res=%llu\n", res);
    
    for (int n=0; n<len; ++n) {
        
        for (int i=0; i<10; ++i) temp[i] = used[i];
        
        int spt;
        if (len==1) spt = 0;
        else if (n==0) spt = 1;
        else spt = 0;
        
        for (int d=spt; d<snum[n]-'0'; ++d) {
            
            if (d&1) {
                temp[d] = !temp[d];
                res += ff[len-n-1][CVA(temp)];
                
                //printf("<<");
                //for (int p=0;p<10;++p) printf("%d ", temp[p]);
               // printf(">>\n");
                
                
                temp[d] = !temp[d];
            } else {
                int o = temp[d];
                if (temp[d]<2) temp[d]++;
                else temp[d]=1;
                
                //printf("<<");
                //for (int p=0;p<10;++p) printf("%d ", temp[p]);
                //printf(">>\n");
                
                res += ff[len-n-1][CVA(temp)];
                temp[d] = o;
            }
            
            
            //printf("res=%llu\n", res);
            
        }
        
        int d=(snum[n]-'0');
        if (d&1) {
            used[d] = !used[d];
        } else {
            if (used[d]<2) used[d]++;
            else used[d]=1;
        }
        
    }
   // printf("END\n");
    return res;
}

int main() {
    vDP1();
    vDP2();
    vDP3();
    
    //printFF();
    //printDP();
    //for (int i=1; i<10; ++i) printf("sff[%d]=%llu\n", i, sff[i]);
    
    //printf("%d\n",calc(1));
    
    int t; ull a, b;
    scanf("%d", &t);
    while (t--) {
        scanf("%llu %llu", &a, &b);
        printf("%llu\n", calc(b+1) - calc(a));
    }
    return 0;
    
}
