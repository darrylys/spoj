#include<stdio.h>

#define MAXN 100010
#define ll long long int

int sells[MAXN][2];
int buys[MAXN][2];
int data[MAXN];

int abs(int a) {return (a<0)?-a:a;}
int min(int a, int b) {return (a<b)?a:b;}

ll run(int n) {
    int topsell=0, topbuy=0;
    ll cost = 0;
    
    for (int i=0; i<n; ++i) {
        if (data[i] >= 0) {
            buys[topbuy][0] = i;
            buys[topbuy][1] = data[i];
            ++topbuy;
        } else {
            sells[topsell][0] = i;
            sells[topsell][1] = data[i];
            ++topsell;
        }
        
        while (topsell > 0 && topbuy > 0) {
            //process top of stacks.
            int m = min(buys[topbuy-1][1], -sells[topsell-1][1]);
            cost += m * (ll)(abs(buys[topbuy-1][0] - sells[topsell-1][0]));
            
            buys[topbuy-1][1] -= m;
            sells[topsell-1][1] += m;
            
            if (buys[topbuy-1][1] == 0) --topbuy;
            if (sells[topsell-1][1] == 0) --topsell;
        }
    }
    
    return cost;
}

int main() {
    int n;
    
    while (scanf("%d", &n) && n) {
        for (int i=0; i<n; ++i) {
            scanf("%d", &data[i]);
        }
        
        printf("%lld\n", run(n));
    }
    return 0;
}