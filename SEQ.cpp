#include<stdio.h>
#include<string.h>

#define MAXK 11
#define ll long long
#define MOD 1000000000

typedef struct {
    int dimension;              //using square matrix ONLY
    int matrix[MAXK][MAXK];
} Matrix;

int b[MAXK];
Matrix mul;

void init(Matrix &c) {
    for (int i=0; i<c.dimension; i++) {
        memset(c.matrix[i], 0, c.dimension*sizeof(int));
    }
    for (int i=1; i<c.dimension; i++) {
        c.matrix[i-1][i] = 1;
    }
}

Matrix multiply(Matrix &a, Matrix &b) { //axb
    Matrix c;
    c.dimension = a.dimension;
    
    for (int i=0; i<c.dimension; i++) {
        for (int j=0; j<c.dimension; j++) {
            c.matrix[i][j] = 0;
            for (int k=0; k<a.dimension; k++) {
                c.matrix[i][j] = 
                    (c.matrix[i][j] + ((ll)a.matrix[i][k]*b.matrix[k][j])%MOD)%MOD;
            }
        }
    }
    
    return c;
}

Matrix power(int n, Matrix &base) {
    if (n == 1) return base;
    else {
        Matrix A = power(n>>1, base);
        if (n&1) { //odd
            Matrix c = multiply(A,A);
            return multiply(c,base);
        } else {
            return multiply(A,A);
        }
    }
}

int calc(int n, int k, Matrix &multiplier, int* bc) {
    Matrix r = power(n-k, multiplier);
    int sum = 0;
    for (int i=0; i<k; i++) {
        sum = (int)((sum + ((ll)bc[k-i-1]*r.matrix[i][0])%MOD)%MOD);
    }
    return sum;
}

int main() {
    int testcase, k, n;
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &k);
        mul.dimension = k;
        init(mul);
        for (int i=0; i<k; i++) {
            scanf("%d", &b[i]);
        }
        for (int i=0; i<k; i++) {
            scanf("%d", &mul.matrix[i][0]);
        }
        scanf("%d", &n);
        if (n <= k) printf("%d\n", b[n-1]);
        else printf("%d\n", calc(n, k, mul, b));
    }
    return 0;
}