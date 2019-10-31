#include<stdio.h>
#include<string.h>

//char primeflag[100];

int dp[13][13][110];
int res[110];
int primes[26] = {2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97};
/*
int buildflag() {
    
    primeflag[0] = primeflag[1] = 1;
    int f = 0;
    primes[f++] = 2;
    
    for (int i=3; i*i<100; i+= 2) {
        if (!primeflag[i]) {
            primes[f++] = i;
            for (int j=i*i; j<100; j+=i) {
                primeflag[j] = 1;
            }
        }
    }
    
    for (int i=4; i<100; i+=2) {
        primeflag[i] = 1;
    }
    
}
*/
void buildDP() {
    //init
    for (int i=0; i<10; ++i) {
        for (int j=0; j<=i; ++j) {
            dp[1][i][j] = 1;
        }
    }
    
    //rec
    for (int n=2; n<=10; ++n) {
        for (int j=0; j<=9*(n-1); ++j) {
            dp[n][0][j] = dp[n-1][9][j];
        }
        
        for (int i=1; i<10; ++i) {
            for (int j=0; j<i; ++j) {
                dp[n][i][j] = dp[n][i-1][j];
            }
            
            for (int j=0; j<=9*(n-1); ++j) {
                dp[n][i][i+j] = dp[n-1][9][j] + dp[n][i-1][i+j];
            }
        }
    }
}

int look(char* n) {
    int len = strlen(n);
    memset(res, 0, sizeof (res));
    
    int app = 0;
    for (int i=0; i<len; ++i) {
        
        if (n[i] > '0') {
        
            for (int j=0; dp[len-i][n[i]-'0'-1][j]!=0; ++j) {
                res[j+app] += dp[len-i][n[i]-'0'-1][j];
            }
        }
        app += n[i]-'0';
    }
    
    int sum = 0;
    for (int i=0; i<25; ++i) {
        sum += res[primes[i]];
    }
    return sum;
}

int recfill(char* buf, int n) {
    if (n) {
        int fi = recfill(buf, n/10);
        buf[fi] = n%10+'0';
        return fi+1;
    }
    return 0;
}

void printdp() {
    for (int n=1; n<=10; ++n) {
        for (int i=0; i<10; ++i) {
            for (int j=0; j<=9*n; ++j) {
                printf("%d ", dp[n][i][j]);
            }
            printf("\n---------------------------------\n");
        }
        printf("\n+++++++++++++++++++++++++++++++++\n");
    }
}

int main() {
    //buildflag();
    buildDP();
    
    //printdp();
    char ca[13];
    char cb[13];
    
    int t, a, b;
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &a, &b);
        
        int la = recfill(ca, a);
        int lb = recfill(cb, b+1);
        ca[la] = '\0';
        cb[lb] = '\0';
        
        printf("%d\n", look(cb) - look(ca));
    }
    return 0;
}
