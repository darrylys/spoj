#include<cstdio>

#define ll long long int

int c[1005];

int main() {
    int n, k, x, cs = 1;
    ll sum;
    while (scanf("%d", &n) && n!=-1) {
        for (int i=n; i>=0; i--) {
            scanf("%d", &c[i]);
        }
        scanf("%d", &k);
        printf("Case %d:\n", cs++);
        while (k--) {
            sum = c[n];
            scanf("%d", &x);
            for (int i=n-1; i>=0; i--) {
                sum = c[i] + sum*x;
            }
            printf("%lld\n", sum);
        }
    }
    return 0;
}