#include<stdio.h>

#define ull unsigned long long

// obtained from HALF bruteforce program..
// since array idxarrcmprsd has > quadratic growth, if N=e13, 
// we only need ~e6 for initial estimation
// and it turns out only need ~100000 elements.
#define MMAX 124392

ull idxarrcmprsd[MMAX];
int bfidx[MMAX];
ull idxh[MMAX];

void buildARR() {
    //part 1
    bfidx[1] = 1;bfidx[2] = 2;bfidx[3] = 2;
    
    int lf = 4;
    for (int i=3; lf < MMAX; ++i) {
        
        for (int j=0; lf < MMAX && j<bfidx[i]; ++j) {
            bfidx[lf] = i;
            ++lf;
        }
    }
    
    //make hidx
    idxh[1] = 1;
    for (int i=2; i<MMAX; ++i) {
        idxh[i] = idxh[i-1] + bfidx[i-1];
    }
    
    //make compressedidx
    idxarrcmprsd[1] = 1;
    idxarrcmprsd[2] = 2;
    
    for (int i=3, temp; i<MMAX; ++i) {
        idxarrcmprsd[i] = idxarrcmprsd[i-1] + ((ull)(i-1))*bfidx[i-1];
    }
}

int getidx(ull N) {
    int u = 1, v = MMAX, c;
    while (1) {
        c = (u+v)>>1;
        if (u>=v) {
            return c-1;
        }
        if (N > idxarrcmprsd[c]) {
            u = c+1;
        } else if (N < idxarrcmprsd[c]) {
            v = c;
        } else {
            return c;
        }
    }
}

int main() {
    buildARR();
    int t; ull N;
    scanf("%d", &t);
    while (t--) {
        scanf("%llu", &N);
        int id = getidx(N);
        int num = idxh[id];
        
        ull diff = N - idxarrcmprsd[id];
        printf("%d\n", num + diff/id);
    }
    return 0;
}
