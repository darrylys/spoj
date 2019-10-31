#include<stdio.h>

#define MX 10000000
//#define DEBUG

int fphi[MX];

void sieve() {
    int np = 3;
    int lpv = 0;
    for (np=3; np*np <= MX; np+=2) {
        if (!fphi[np]) {
            fphi[np] = ++lpv;
            
            for (int j=np*np; j<MX; j+=2*np) {
                if (!fphi[j]) {
                    fphi[j] = fphi[np];
                }
            }
        }
    }
    
    for (; np<MX; np+=2) {
        if (!fphi[np]) {
            fphi[np] = ++lpv;
        }
    }
    
    #ifdef DEBUG
    for (int i=1; i<10000; ++i) {
        printf("%d\n", fphi[i]);
    }
    #endif
}

int main() {
    sieve();
    
    int t, N, a, r;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &N);
        r = 0;
        while (N--) {
            scanf("%d", &a);
            r ^= fphi[a];
        }
        printf("%s\n", r ? "Bahl" : "Debnath");
    }   
}   