#include<stdio.h>
#include<string.h>

#define MOD 1000000007
#define ll long long

int prime[503];
char flag[503];

int buf[502][502];

void buildprime() {
    prime[1] = 2;
    int f = 2;
    int lasti;
    for(int i=3; i*i <= 3571; i+=2) {
        if (!flag[i]) {
            prime[f++] = i;
            for (int j=i*i; j<=3571; j+=i) {
                flag[j] = 1;
            }
        }
        lasti = i;
    }
    
    for (int i=lasti+2; i<=3571; i+=2) {
        if (!flag[i]) prime[f++] = i;
    }
}

int dof(int K, int P) {
    if (buf[K][P] != -1) {
        return buf[K][P];
    }
    
    if (K<P) {
        return buf[K][P] = 0;
    }
    
    if (P == 0) {
        return buf[K][P] = 0;
    }
    
    if (K == P) {
        ll mul = 1;
        for (int i=1; i<=P; ++i) {
            mul = (mul*(prime[i]-1))%MOD;
        }
        return buf[K][P] = (int)mul;
    }
    
    return buf[K][P] = (int)(((ll)(prime[P]-1)*dof(K-1,P-1) + (ll)(prime[P])*dof(K-1,P))%MOD);
}

int main() {
    int t, K, P, c=1;
    buildprime();
    //printf("prime[500] = %d\n", prime[500]);
    memset(buf, -1, sizeof(buf));
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &K, &P);
        printf("Case %d: %d\n", c++, dof(K,P));
    }
    return 0;
}
