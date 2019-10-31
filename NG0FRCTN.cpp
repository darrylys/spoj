#include<cstdio>

#define ll long long int

ll gcd(ll a, ll b) {
    if (b == 0) return a;
    else return gcd(b, a%b);
}

void calc_abcd(ll n, ll& a, ll& b, ll& c, ll& d) {
    ll start = n;
    
    //inits
    a = 1; b = 0; c = 0; d = 1;
    
    while (start > 1) {
        if (start%2) { //right child
            a = a-c;
            b = b-d;
        } else {
            c = c-a;
            d = d-b;
        }
        
        start = start >> 1;
    }
}

void calc_VW(ll& a, ll& b, ll& c, ll& d, ll& V, ll& W) {
    V = (d-b) / (a*d - b*c);
    W = (c-a) / (b*c - a*d);
    
    //ll div = gcd(V,W);
    //V /= div;
    //W /= div;
}

int main() {
    ll n, a, b, c, d, V, W;
    while (scanf("%lld", &n) && n) {
        calc_abcd(n,a,b,c,d);
        
        //printf("%lld %lld %lld %lld %lld\n", n,a, b, c, d);
        
        calc_VW(a,b,c,d,V,W);
        
        printf("%lld/%lld\n", V, W);
    }
    return 0;
}