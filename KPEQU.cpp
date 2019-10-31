#include<stdio.h>

#define MAXN 10015
#define NUM 0
#define EXP 1
#define ll long long int

int prime[MAXN];
bool flag[MAXN];

int sieve(int n) {
    
    int c = 0, i;
    prime[c++] = 2;
    
    for (i=3; i*i <= n; i +=2) {
        if (!flag[i]) {
            prime[c++] = i;
            for (int j=i*i; j<n; j+=2*i) flag[j] = true;
        }
    }
    
    for (; i<n; i+=2) {
        if (!flag[i]) prime[c++] = i;
    }
    
    return c;
}

ll solve(int n) {
    int ori, exp; 
    ll mul = 1;
    
    for (int i=0; prime[i] <= n; ++i) {
        ori = n;
        exp = 0;
        
        while (ori) {
            exp += ori/prime[i];
            ori /= prime[i];
        }
        
        mul *= (2LL*exp + 1);
    }
    
    return mul;
}

int main() {
    int nop = sieve(MAXN);
    
    int n;
    while (scanf("%d", &n) && n) {
        printf("%lld\n", solve(n));
    }
    return 0;
}