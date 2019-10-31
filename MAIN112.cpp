#include<stdio.h>
#include<string.h>

#define MAXN 20
#define BIG 1<<30
//#define DEBUG

int C[MAXN];
int N[MAXN];
int dp[MAXN][1<<17];
char flag[MAXN][1<<17];

inline int abs(int a) {
    return (a<0)?-a:a;
}

#ifdef DEBUG
void printbinary(int x) {
    if (x) {
        printbinary(x>>1);
        putchar((x&1) + '0');
    }
}

void printspace(int z) {
    while (z--) {
        putchar('\t');
    }
}
#endif

int calc(int dNz, int udd, int NT, int rn) {
    if (flag[dNz][udd]) return dp[dNz][udd];
    
    flag[dNz][udd] = 1;
    
    if (rn == 0) {
        return dp[dNz][udd] = 0;
    }
    
    int minv = BIG;
    int nudd = udd&(~(1<<dNz));
    
    #ifdef DEBUG
    printspace(NT-rn);
    printf("udd=");printbinary(udd);printf("nudd=");printbinary(nudd);
    putchar('\n');
    printspace(NT-rn);printf("{");
    putchar('\n');
    #endif
    
    for (int iz=0, tv=0; iz<NT; ++iz) {
        if ((1<<iz)&nudd) {
            tv = abs(N[dNz] - N[iz]) * C[rn] + calc(iz, nudd, NT, rn-1);
            #ifdef DEBUG
            printspace(NT-rn);
            printf("tv=%d | N[dNz]=%d, N[iz]=%d, rn=%d, C[rn]=%d, dp[iz][nudd]=%d\n", tv, N[dNz], N[iz], rn, C[rn], dp[iz][nudd]);
            #endif
            if (tv < minv) minv = tv;
        }
    }
    
    #ifdef DEBUG
    printspace(NT-rn);
    printf("}\n");
    #endif
    
    return dp[dNz][udd] = minv;
}

int main() {
    int t, NT;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &NT);
        for (int i=0 ;i<NT; ++i) {
            scanf("%d", &N[i]);
        }
        N[NT] = 0;
        
        for (int i=0; i<NT; ++i) {
            scanf("%d", &C[i]);
        }
        C[NT] = 0;
        
        if (NT == 1) {
            printf("0\n");
            continue;
        }
        
        memset(flag, 0, sizeof(flag));
        
        printf("%d\n", calc(NT, (1<<(NT+1))-1, NT+1, NT));
        
    }
    
}

