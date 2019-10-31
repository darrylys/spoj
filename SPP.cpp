#include<stdio.h>
#include<string.h>

#define MAXK 17
#define ll long long

typedef struct {
    int dim;              //using square matrix ONLY
    int m[MAXK][MAXK];
} Matrix;

void initGeneral(Matrix &c, int* coef) {
    for (int i=1; i<c.dim; i++) {
        c.m[0][i-1] = coef[i-1];
    }
    c.m[0][c.dim-1] = 0;
    
    for (int i=1; i<c.dim; i++) {
        memset(c.m[i], 0, (c.dim)*sizeof(int));
    }
    for (int i=1; i<c.dim; i++) {
        c.m[i][i-1] = 1;
    }
    c.m[c.dim-1][c.dim-1] = 1;
}

Matrix multiply(Matrix &a, Matrix &b, int p) { //axb
    Matrix c;
    c.dim = a.dim;
    
    for (int i=0; i<c.dim; i++) {
        for (int j=0; j<c.dim; j++) {
            c.m[i][j] = 0;
            for (int k=0; k<a.dim; k++) {
                c.m[i][j] = (int)((c.m[i][j] + ((ll)a.m[i][k]*b.m[k][j])%p)%p);
            }
        }
    }
    return c;
}

Matrix power(ll n, Matrix &base, int p) {
    if (n == 1) return base;
    else {
        Matrix A = power(n>>1, base, p);
        if (n&1LL) { //odd
            Matrix c = multiply(A,A,p);
            return multiply(c,base,p);
        } else {
            return multiply(A,A,p);
        }
    }
}

void compute_list_of_c(Matrix &coefMtr, ll pow, int* res, int p) {
    Matrix r = power(pow, coefMtr, p);
    //printMatrix("r", r);
    
    for (int i=0; i<r.dim; i++) {
        res[i] = 0;
        for (int j=0; j<r.dim; j++) {
            res[i] = (res[i] + r.m[j][i])%p;
        }
    }
}

//p = modulus, c = coefficient matrix, a = initial a value, coef = c array
int solve2(ll m, ll n, int p, int k, Matrix &c, int* a, int* coef) { 
    c.dim = k+1;
    initGeneral(c, coef);
    int nlist[MAXK], mlist[MAXK];
    
    if (n > k && m > k+1) {
        compute_list_of_c(c, n-k, nlist, p);
        compute_list_of_c(c, m-1-k, mlist, p);
        
        int sum1 = 0, sum2 = 0;
        for (int i=k-1; i>=0; i--) {
            sum1 = (int)((sum1 + (ll)nlist[i]*a[-i+k-1])%p);
            sum2 = (int)((sum2 + (ll)mlist[i]*a[-i+k-1])%p);
        }
        
        int ans = sum1 - sum2;
        if (ans < 0) return ans + p;
        else return ans;
    }
    if (n > k) {
        compute_list_of_c(c, n-k, nlist, p);
        
        int sum1 = 0, sum2 = 0;
        for (int i=k-1; i>=0; i--) {
            sum1 = (int)((sum1 + (ll)nlist[i]*a[-i+k-1])%p);
        }
        for (int i=1; i<m; i++) {
            sum2 = (int)((sum2 + a[i-1])%p);
        }
        
        int ans = sum1 - sum2;
        if (ans < 0) return ans + p;
        else return ans;
    }
    
    int sum = 0;
    for (int i=m; i<=n; i++) {
        sum = (int)((sum + a[i-1])%p);
    }
    return sum;
}

int main() {
    int b[MAXK], c[MAXK], test, k;
    ll n, m;
    int p;
    Matrix coef;
    scanf("%d", &test);
    while (test--) {
        scanf("%d", &k);
        for (int i=0; i<k; i++) {
            scanf("%d", &b[i]);
        }
        for (int i=0; i<k; i++) {
            scanf("%d", &c[i]);
        }
        scanf("%lld %lld %d", &m, &n, &p);
        int res = solve2(m,n,p,k,coef,b,c);
        printf("%d\n", res);
    }
    return 0;
}