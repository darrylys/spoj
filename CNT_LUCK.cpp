#include<stdio.h>

#define ull unsigned long long

ull aC[65][65];
int lucky[] = {4, 7, 44, 47};

void buildC() {
    aC[0][0] = 1;
    for (char i=1; i<=64; ++i) {
        aC[i][0] = aC[i][i] = 1;
        for (char j=1; j<i; ++j) {
            aC[i][j] = aC[i-1][j] + aC[i-1][j-1];
        }
    }
}

ull C(int n, int k) {
    if (k<0) return 0;
    else return aC[n][k];
}

ull calc(ull a) {
    
    
    /*
    int n = 63;
    
    while (!(a&(1LL<<n))) {
        n--;
    }
    */
    int n=0;
    ull ta = a;
    while (ta) {
        ta >>= 1;
        n++;
    }
    
    ull sum = 0;
    int uso = 0;
    
    for (;n>=0;n--) {
        
        if (a&(1LL<<n)) {
            sum += C(n,4-uso) + C(n,7-uso) + C(n,44-uso) + C(n,47-uso);
            uso++;
        }
    }
    
    return sum;
}

int main() {
    buildC();
    
    int t;
    ull a, b;
    scanf("%d", &t);
    while (t--) {
        scanf("%llu %llu", &a, &b);
        
        ull B = calc(b+1);
        ull A = calc(a);
        
        //printf("B=%llu - A=%llu = %llu\n", B, A, B-A);
        printf("%llu\n", B-A);
    }
    
}
