#include<stdio.h>
#include<string.h>

#define BUF 90
#define _(a) ((a)+BUF)

int dp[11][11][200];

inline int max(int a, int b) {
    return (a>b)?a:b;
}

void printdp() {
    for (int n=1; n<=10; ++n) {
        for (int i=0; i<10; ++i) {
            for (int j=0; j<200; ++j) {
                printf("%9d\t", dp[n][i][j]);
            }
            printf("\n---------------------------------\n");
        }
        printf("\n+++++++++++++++++++++++++++++++++\n");
    }
}

void buildDP() {
    //n=1
    
    int prev;
    //d=0;
    for(int i=-1; i>=-BUF; --i) {
        dp[1][0][_(i)] = 1;
    }
    prev = -1;
    
    //d=1-9
    for(int d=1; d<=9; ++d) {
        if (d&1) {
            for (int i=-d-1; i>=-BUF; --i) {
                dp[1][d][_(i)] = 1 + dp[1][d-1][_(i)];
            }
            for (int i=prev; i>-d-1; --i) {
                dp[1][d][_(i)] = dp[1][d-1][_(i)];
            }
            
        } else {
            for (int i=d-1; i>=-BUF; --i) {
                dp[1][d][_(i)] = 1 + dp[1][d-1][_(i)];
            }
            prev = d-1;
        }
    }
    
    //printdp();
    
    //n=2-9
    for (int n=2; n<=9; ++n) {
        //printf("prev=%d, n=%d\n", prev, n);
        //d=0
        for (int i=prev; i>=-BUF; --i) {
            dp[n][0][_(i)] = dp[n-1][9][_(i)];
        }
        
        //d=1-9
        for (int d=1; d<=9; ++d) {
            //printf("prev=%d, n=%d, d=%d\n", prev, n, d);
            
            if (d&1) {
                for (int i=prev-d; i>=-BUF; --i) {
                    dp[n][d][_(i)] = dp[n][0][_(i)+d] + dp[n][d-1][_(i)];
                }
                for (int i=prev; i>prev-d; --i) {
                    dp[n][d][_(i)] = dp[n][d-1][_(i)];
                }
                
                //n=7,d=5_(i)=195??
                
                
            } else {
                for (int i=prev+d; i>=-BUF; --i) {
                    if (_(i)-d >= 0) { 
                        dp[n][d][_(i)] = dp[n][0][_(i)-d] + dp[n][d-1][_(i)];
                    } else {
                        dp[n][d][_(i)] = dp[n][0][0] + dp[n][d-1][_(i)];
                    }
                }
                
                prev += 2;
            }
            
        }
    }
    
    //printdp();
}

int look(char* num) {
    int len = strlen(num);
    
    int res = 0;
    int prevsum = 0;
    for (int i=0; i<len; ++i) {
        
        if (num[i] > '0') {
            res += dp[len-i][num[i]-'0'-1][_(0)-prevsum];
        }
        
        if ((num[i]-'0')&1) {
            prevsum -= num[i]-'0';
        } else {
            prevsum += num[i]-'0';
        }
        
    }
    return res;
}

int recfill(char* buf, int n) {
    if (n) {
        int fi = recfill(buf, n/10);
        buf[fi] = n%10+'0';
        return fi+1;
    }
    return 0;
}

void fill(char* buf, int n) {
    int x = recfill(buf, n);
    buf[x]='\0';
}

int main() {
    buildDP();
    //printf("%d %d\n", -62, _(-62));
    
    int t, a, b;
    char ca[12];
    char cb[12];
    
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &a, &b);
        fill(ca, a);
        fill(cb, b+1);
        
        printf("%d\n", look(cb)-look(ca));
    }
    return 0;
}
