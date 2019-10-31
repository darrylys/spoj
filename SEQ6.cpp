#include<stdio.h>

#define ull unsigned long long

char flag[3600];
int prime[3500];


int getint() {
    int x=0; char c;
    while ((c=getchar())<'0' || c>'9');
    do {
        x = x*10+c-'0';
    } while ((c=getchar())>='0' && c<='9');
    return x;
}

int buildprime() {
    prime[0] = 2;
    int f = 1;
    for (int i=3; i*i<=10000000; i+=2) {
        if (!flag[i]) {
            prime[f++] = i;
            for (int j=i*i; (ull)j*j<=10000000; j+=i) {
                flag[j]=1;
            }
        }
    }
    return f;
}

int calcv(int dN, int nprimes) {
    int N = dN;
    
    while (!(N&1)) {
        N>>=1;
    }
    
    int r = 1, k;
    for (int i=1; i<nprimes && N>1; ++i) {
        
        k=0;
        while (N%prime[i] == 0) {
            N/=prime[i];
            k++;
        }
        r *= (k+1);
    }
    
    if (N>1) {
        r <<= 1;
    }
    
    return r;
}

int main() {
    int N, re, nprimes;
    nprimes = buildprime();
    //printf("nprimes=%d\n", nprimes);
    while (1) {
        N = getint();
        if (N==0) break;
        
        printf("%d\n", calcv(N, nprimes)<<1);
    }
    return 0;
}
