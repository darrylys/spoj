#include<stdio.h>

#define ll long long

ll tsum[1<<20];
int phi[1<<20];
int mark[1<<20];

void build() {
    
    phi[1] = 1;
    
    for (int i=2; i<=1000; ++i) {
        if (!mark[i]) {
            for (int j=i*i; j<=1000000; j += i) {
                if (!mark[j]) {
                    mark[j] = i;
                }
            }
        }
    }
    
    for (int i=2; i<=1000000; ++i) {
        if (mark[i] == 0) {
            phi[i] = i-1;
        } else {
            if (i % (mark[i]*mark[i]) == 0) {
                phi[i] = mark[i] * phi[i/mark[i]];
            } else {
                phi[i] = (mark[i]-1) * phi[i/mark[i]];
            }
        }
    }
    
    for (int i=2; i<=1000000; ++i) {
        for (int j=i; j<=1000000; j+=i) {
            tsum[j] += (ll)i*phi[i];
        }
    }
}


int main() {
    build();
    
    int t, n;
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &n);
        //printf("tsum=%lld\n", tsum[n]);
        printf("%lld\n", n + tsum[n]/2*n);
    }
    
    return 0;
}