#include<stdio.h>

#define N 10010
#define MAX (1LL<<62)
#define ll long long

ll sum_road[N];
ll sum_beer[N];
ll scf[N];
ll scb[N];
int beer[N];
int road[N];

ll max(ll a, ll b) {
    if (a > b) return a;
    else return b;
}

ll sum(int a, int b, int n, ll* arr) {
    if (a <= b) {
        return arr[b] - arr[a-1];
    } else {
        return arr[n]-arr[a-1] + arr[b];
    }
}

ll getcost(int a, int b, int n, bool forward) {
    if (forward) {
        if (a <= b) {
            ll f = sum(a+1,b,n,sum_beer);
            return max(0LL, scf[b-1] - scf[a-1] - sum_road[a-1]*f);
        } else {
            return getcost(a,n,n,forward) //+ beer[1]*(sum_road[n]-sum_road[a-1]) 
                + getcost(1,b,n,forward) + (sum_beer[b])*(sum_road[n]-sum_road[a-1]);
        }
    } else {
        if (a >= b) {
            ll f = sum(b,a-1,n,sum_beer);
            return max(0LL, scb[n-b] - scb[n-a] - (sum_road[n-1] - sum_road[a-1])*f);
        } else {
            return getcost(a,1,n,forward) //+ beer[n]*(road[n]+sum_road[a-1]) 
                + getcost(n,b,n,forward) + (sum_beer[n]-sum_beer[b-1])*(road[n]+sum_road[a-1]);
        }
    }
}

int main() {
    int test, n, min;
    scanf("%d", &test);
    while (test--) {
        scanf("%d", &n);
        sum_road[0] = sum_beer[0] = 0;
        for (int i=1; i<=n; i++) {
            scanf("%d %d", &beer[i], &road[i]);
            sum_road[i] = sum_road[i-1] + road[i];
            sum_beer[i] = sum_beer[i-1] + beer[i];
        }
        
        scf[0] = 0;
        for (int i=1; i<n; i++) {
            scf[i] = scf[i-1] + beer[i+1]*sum_road[i];
        }
        scf[n] = scf[n-1] + beer[1]*sum_road[n];
        
        scb[0] = 0;
        for (int i=n-1; i>=1; i--) {
            scb[n-i] = scb[n-i-1] + beer[i]*(sum_road[n-1]-sum_road[i-1]);
        }
        scb[n] = scb[n-1] + beer[n]*sum_road[n];
        
        int lo, hi, c, a, b, dex, dex2;
        ll min = MAX, v, x, y;
        for (int start = 1; start < n; start++) {
            lo = 1; hi = n;
            while (1) {
                c = (lo+hi)>>1;
                dex = (start+c-1)%n;
                if (dex==0) dex = n;
                a = sum(start, dex, n, sum_road);
                
                dex = (start+c)%n;
                if (dex==0) dex=n;
                
                dex2 = (start+n-1)%n;
                if (dex2==0) dex2=n;
                b = sum(dex, dex2, n, sum_road);
                
                if (hi == lo) break;
                
                if (a <= b) {
                    lo = c+1;
                } else {
                    hi = c;
                }
            }
            
            int dex1;
            if (a <= b) {
                dex1 = (start+c)%n;
                if (dex1==0) dex1=n;
//                printf("dex1=%d <=", dex1);
            } else {
                dex1 = (start+c-1)%n;
                if (dex1==0) dex1=n;
//                printf("dex1=%d  >", dex1);
            }
            
            x = max(0, getcost(start, dex1, n, true));
//            printf("----");
            
            dex1 = (dex1+1)%n;
            if (dex1==0)dex1=n;
            y = max(0, getcost(start, dex1, n, false));
//            printf("++++");
            v = x+y;
//            printf("test2=%d\n", getcost(5, 4, n, true));
            //printf("test1 = %d\n", getcost(26, 77, n, true) + getcost(26, 78, n, false));
//            printf("start=%d, dex1=%d, v = %lld, c=%d, x=%lld, y=%lld\n",start, dex1, v, c, x, y);
            if (v < min) {
                min = v;
            }
        }
        printf("%lld\n", min);
    }
    return 0;
}