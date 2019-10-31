#include<stdio.h>

#define MAXK 20
#define ll long long
#define LIMIT 1000000000

int sum[MAXK];
int num[MAXK];

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    else return gcd(b, a%b);
}

void getsum(int x, int N) {
    int st = x;
    int cntr = 0;
    int p = 0;
    ll n = 1;
    
    while (st) {
        if (st&1) {
            n = n/gcd(n, num[p])*num[p];
            if (n > N) { //if divided by this = 0 == USELESS
                break;
            }
            cntr++;
        }
        p++;
        st >>= 1;
    }
    
    sum[cntr] += N/n;
}

void fillsum(int k, int N) {
    
    for (int i=1; i<(1<<k); i++) {
        getsum(i, N);
    }
}

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    
    for (int i=0; i<k; i++) {
        scanf("%d", &num[i]);
    }
    
    fillsum(k, n);
    
    int m = -1;
    for (int i=1; i<=k; i++) {
        n = n + m*sum[i]; 
        m = -m;
    }
    
    printf("%d\n", n);
    return 0;
}