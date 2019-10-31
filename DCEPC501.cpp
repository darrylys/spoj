#include<stdio.h>

#define ll long long

ll dp[100010][3];
int pc[100010];

ll max(ll a, ll b) {
    return (a>b)?a:b;
}

ll max3(ll a, ll b, ll c) {
    return max(a, max(b,c));
}

ll getdp(int n, int k) {
    if (n<0) return 0;
    else return dp[n][k];
}

int main() {
    int t, n;
    scanf("%d", &t);
    while(t--){
        scanf("%d", &n);
        for (int i=0; i<n; ++i) {
            scanf("%d", &pc[i]);
        }
        
        dp[0][0] = pc[0];
        if (1<n) {
            dp[0][1] = pc[0]+pc[1];
        } else {
            dp[0][1] = 0;
        }
        if (2<n) {
            dp[0][2] = pc[0]+pc[1]+pc[2];
        } else {
            dp[0][2] = 0;
        }
        //printf("%d] %lld %lld %lld\n", 0, dp[0][0], dp[0][1], dp[0][2]);
        
        ll _max=max3(dp[0][0], dp[0][1], dp[0][2]);
        
        for (int i=2; i<n; i+=2) {
            ll amax = max3(getdp(i-2, 0), getdp(i-4, 1), getdp(i-6, 2));
            dp[i][0] = pc[i] + amax;
            _max=max(dp[i][0], _max);
            
            if (i+1<n) {
                dp[i][1] = pc[i] + pc[i+1] + amax;
                _max=max(dp[i][1], _max);
            }
            
            if (i+2<n) {
                dp[i][2] = pc[i] + pc[i+1] + pc[i+2] + amax;
                _max=max(dp[i][2], _max);
            }
            
            //printf("%d] %lld %lld %lld\n", i, dp[i][0], dp[i][1], dp[i][2]);
        }
        
        printf("%lld\n", _max);
        /*if (n&1) {
            printf("%lld\n", max3(dp[n-1][0], dp[n-1][1], dp[n-1][2]));
        } else {
            printf("%lld\n", max3(dp[n-2][0], dp[n-2][1], dp[n-2][2]));
        }*/
    }
}