#include<stdio.h>

#define ll long long

int main() {
    
    ll N;
    ll sum;
    int c = 1;
    while (scanf("%lld", &N) != -1) {
        
        sum = 0;
        for (int a=1; (ll)a*a*a<=N; ++a) {
            
            // b==a
            sum += 1;
            sum += 3LL*(N/((ll)a*a)-a);
            
            // b>a
            for (int b=a+1; (ll)b*b<=N/a; ++b) {
                sum += 3;
                sum += 6LL*(N/((ll)a*b)-b);
            }
        }
        
        printf("Case %d: %lld\n", c++, sum);
    }
    return 0;
}
