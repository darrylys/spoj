#include<stdio.h>

#define ull unsigned long long

int phi[10010];
ull sphi[10010];
int prime[10010];
char flag[10010];

int makePrime() {
    prime[0]=2;
    int f=1;
    for (int i=3; i<=100; i+=2) {
        if (!flag[i]) {
            prime[f++] = i;
            for (int j=i*i; j<=100; j+=i) {
                flag[j] = 1;
            }
        }
    }
    return f;
}

void make() {
    int nprime = makePrime();

    phi[1] = 1;
    for (int i=2; i<=10000; ++i) {
        phi[i] = -1;
        for (int j=0; j<nprime; ++j) {
            int p2 = prime[j]*prime[j];
            if (i%p2 == 0) {
                phi[i] = prime[j]*phi[i/prime[j]];
                break;
            }
            if (i%prime[j] == 0) {
                phi[i] = (prime[j]-1)*phi[i/prime[j]];
                break;
            }
        }
        if (phi[i] == -1) {
            phi[i] = i-1;
        }
    }
    
    sphi[0] = 0;
    for (int i=1; i<=10000; ++i) {
        sphi[i] = sphi[i-1] + phi[i];
    }
}

int main() {
    make();
    int t, N;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &N);
        printf("%llu\n", sphi[N]*sphi[N]);
    }
    return 0;
}
