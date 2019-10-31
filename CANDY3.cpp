#include<cstdio>
#define ll long long
int main() {
    int t;
    scanf("%d",&t);
    while (t--) {
        ll sum = 0;
        ll temp;
        int n;
        scanf("%d", &n);
        for (int i=0; i<n; i++) {
            scanf("%lld", &temp);
            sum = sum%n;
            temp = temp%n;
            sum = (sum+temp)%n;
        }
        if (sum%n == 0) printf("YES\n");
        else printf("NO\n");
    }
}
