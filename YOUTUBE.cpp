#include<stdio.h>

#define MAXN 100010
#define MAXK 100010

int ID[MAXK]; // identity matrix
int AN[MAXN];
int AK[MAXK]; // this is the base!

int hsqr[MAXK];
int extra[MAXK];
int fin[MAXK];

void fillID() {
    for (int i=0; i<MAXK; ++i) {
        ID[i]=  i;
    }
}

// axb=c
void permMulMtrv1(int* a, int* b, int* c, int k) {
    for (int i=0; i<k; ++i) {
        c[i] = a[b[i]];
    }
}

int* mtrexpv1(int exp, int k) {
    if (exp==0) return ID;
    if (exp==1) return AK;
    int* hs = mtrexpv1(exp>>1, k);
    if (exp&1) {
        permMulMtrv1(hs, hs, hsqr, k);
        permMulMtrv1(hsqr, AK, fin, k);
        return fin;
    } else {
        permMulMtrv1(hs, hs, extra, k);
        for (int i=0; i<k; ++i) fin[i]=extra[i];
        return fin;
    }
}

int main() {
    int n, k, m;
    fillID();
    scanf("%d %d %d", &n, &k, &m);
    for (int i=0; i<n; ++i) {
        scanf("%d", &AN[i]);
    }
    for (int i=0; i<k; ++i) {
        scanf("%d", &AK[i]);
        --AK[i];
    }
    int* r = mtrexpv1(m-1, k);
    for (int i=0; i<n; ++i) {
        printf("%d ", r[AN[i]-1]+1);
    }
    putchar('\n');
    return 0;
}

