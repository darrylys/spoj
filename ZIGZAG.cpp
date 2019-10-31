#include<stdio.h>

#define MAXN 100010
#define LL long long int

LL sv[2*MAXN];
int col[2*MAXN];

int abs(int a) {return (a<0)?-a:a;}

char getv() {
    
    char c;
    while (1) {
        c = getchar();
        if (c == '\n' || c == ' ' || c == '\r' || c == '\t') continue;
        return c;
    }
}

int main() {
    int n, k;
    int crow, ccol;
    char c;
    LL sum;
    
    scanf("%d %d", &n, &k);
    
    //precompute
    for (int i=1; i<=n; i+=2) {
        col[i] = 1;
    }
    
    for (int i=2; i<=n; i+=2) {
        col[i] = i;
    }
    
    if (n&1) {
        for (int i=n+1; i<n*2; i+=2) {
            col[i] = n;
        }
        
        int s = 3;
        for (int i=n+2; i<n*2; i+=2, s+=2) {
            col[i] = s;
        }
    } else {
        int s = 2;
        for (int i=n+1; i<n*2; i+=2, s+=2) {
            col[i] = s;
        }
        
        for (int i=n+2; i<n*2; i+=2) {
            col[i] = n;
        }
    }
    
    sv[1] = 1;
    for (int i=2; i<=n+1; ++i) {
        sv[i] = sv[i-1]+i-1;
    }
    
    for (int i=n+2, j=n-1; i<n*2; ++i, --j) {
        sv[i] = sv[i-1] + j;
    }
    
    crow = ccol = 1;
    sum = 1;
    
    while (k--) {
        c = getv();
        if (c == 'D') {
            ++crow;
        } else if (c == 'R') {
            ++crow; ++ccol;
        } else if (c == 'L') {
            --crow; --ccol;
        } else {
            --crow;
        }
        
        sum += sv[crow] + abs(col[crow] - ccol);
    }
    
    printf("%lld\n", sum);
    
    return 0;
}