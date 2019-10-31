#include<stdio.h>
#include<string.h>

#define N 505

typedef struct {
    char m[N];
} BM;

BM _base, _id, _fin, _buf1, _buf2;

void getID(BM& base, int dim) {
    memset (base.m, 0, sizeof(base.m));
    base.m[0] = 1;
}

void getBase(BM& base, int dim) {
    memset (base.m, 0, sizeof(base.m));
    base.m[0] = base.m[1] = base.m[dim-1] = 1;
}

void smul(BM& a, BM& b, int dim, BM& c) {
    //BM c;
    for (int j=1; j<dim; ++j) {
        c.m[j] = 0;
        for (int k=0; k<dim; ++k) {
            c.m[j] ^= (a.m[k] & b.m[(k-j+dim)%dim]); //symmetric
        }
    }
    
    c.m[0] = 1;
}

void printBM(BM& a, char* text, int dim) {
    printf("%s\n", text);
    for (int i=0; i<dim; ++i) {
        for (int j=0; j<dim; ++j) {
            printf("%d ", a.m[(j-i+dim)%dim]);
        }
        putchar('\n');
    }
    printf("=========================\n");
}

void sexp(int exp, BM& base, BM& id, int dim, BM& retbuf, BM& interbuf, BM& interbuf2) {
    if (exp == 0) {
        getID(retbuf, dim);
        return;
    }
    if (exp == 1) {
        getBase(retbuf, dim);
        return;
    }
    
    if (exp & 1) {
        sexp(exp>>1, base, id, dim, interbuf, interbuf2, retbuf);
        //cpbuf(retbuf, interbuf, dim);
        smul(interbuf, interbuf, dim, interbuf2);
        smul(interbuf2, base, dim, retbuf);
        //printf("exp=%d\n", exp);
        //printBM(retbuf, "retbuf", dim);
    } else {
        sexp(exp>>1, base, id, dim, interbuf, interbuf2, retbuf);
        //cpbuf(retbuf, interbuf, dim);
        smul(interbuf, interbuf, dim, retbuf);
        //printf("exp=%d\n", exp);
        //printBM(retbuf, "retbuf", dim);
    }
}



int main() {
    int t, n, k;
    
    int in[N];
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &k);
        for (int i=0; i<n; ++i) scanf("%d", &in[i]);
        
        getBase(_base, n);
        sexp(k, _base, _id, n, _fin, _buf1, _buf2);
        //printBM(_fin, "XXXXXXX_finXXXXXXXXX", n);
        for (int i=0; i<n; ++i) {
            int v = 0;
            for (int j=0; j<n; ++j) {
                v ^= (_fin.m[(j-i+n)%n]) ? in[j] : 0;
            }
            printf("%d ", v);
        }
        putchar('\n');
    }
}