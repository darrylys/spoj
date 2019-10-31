#include<stdio.h>
#include<math.h>

#define ll long long

int main() {
    ll n, k;
    scanf("%lld %lld", &n, &k);
    
    ll restk;
    ll sum = 0;
    
    if (n>=k) {
        sum = k*(n-k);
    }
    
    ll begin=k+1, end, diff, ev, bv;
    ll rb;
    for (ll x=1; x*x<k; ++x) {
        
        end = (int)ceil((k+1.0)/(x+1.0));
        begin = begin-1;
        
        if (end <= n) {
        
            ev = k%end;
            if (begin > n) {
                bv = k%n;
                rb = n;
            } else {
                bv = k%begin;
                rb = begin;
            }
            
            //printf("end=%lld begin=%lld ev=%lld bv=%lld rb=%lld\n", end, begin, ev, bv, rb);
            
            if ((rb-end+1) % 2 == 0) {
                sum += (rb-end+1)/2*(ev+bv);
            } else {
                sum += (ev+bv)/2*(rb-end+1);
            }
            
        }
        
        begin = end;
    }
    
    for (ll z = begin-1; z>1; --z ) {
        sum += k%z;
    }

    
    printf("%lld\n", sum);
}