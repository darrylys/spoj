#include<stdio.h>
#include<math.h>

#define ll long long

typedef struct {
    int m[3][3];
} Matrix;

Matrix prepBase() {
    Matrix b;
    b.m[0][0] = 2;
    b.m[0][1] = 1;
    b.m[0][2] = 0;
    b.m[1][0] = 2;
    b.m[1][1] = 0;
    b.m[1][2] = 1;
    b.m[2][0] = -1;
    b.m[2][1] = 0;
    b.m[2][2] = 0;
    return b;
}

Matrix prepID() {
    Matrix b;
    for (int i=0; i<3; ++i) {
        for (int j=0; j<3; ++j) {
            if (i!=j) b.m[i][j]=0;
            else b.m[i][j]=1;
        }
    
    }
    return b;
}

Matrix mmul(Matrix& a, Matrix& b, int mod) {
    Matrix c;
    for (int i=0; i<3; ++i) {
        for (int j=0; j<3; ++j) {
            c.m[i][j] = 0;
            for (int k=0; k<3; ++k) {
                c.m[i][j] = (int)(((ll)c.m[i][j] + (ll)a.m[i][k] * b.m[k][j] + mod)%mod);
            }
        }
    }
    return c;
}

Matrix mexp(ll exp, int mod, Matrix& base, Matrix& id) {
    if (exp == 0) {
        return id;
    } else if (exp == 1) {
        return base;
    }
    Matrix half = mexp(exp>>1, mod, base, id);
    if (exp&1) {
        Matrix dhalf = mmul(half, half, mod);
        return mmul(dhalf, base, mod);
    } else {
        return mmul(half, half, mod);
    }
}

void pm(Matrix& a) {
    printf("====\n");
    for (int i=0; i<3; ++i) {
        for (int j=0; j<3; ++j) {
            printf("%d ", a.m[i][j]);
        }
        printf("\n");
    }
    printf("====\n");
}

int main() {
    int t, _0, _1, _2, m;
    ll n;
    Matrix base = prepBase();
    Matrix id = prepID();
    
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d%d%lld", &_0, &_1, &m, &n);
        
        //printf("%d %d %d %lld\n", _0, _1, m, n);
        
        if (n==0) {
            printf("%d\n", _0%m);
        } else if (n==1) {
            printf("%d\n", _1%m);
        } else if (n==2) {
            _2 = (int)((_0+_1+2*(int)floor(sqrt(3.0+(ll)_0*_1)))%m);
            printf("%d\n", _2);
        } else {
            _2 = (int)((_0+_1+2*(int)floor(sqrt(3.0+(ll)_0*_1)))%m);
            //printf("2=%d \n", _2);
            //pm(base);
            //pm(id);
            
            //Matrix mm = mmul(base, base, m);
            //Matrix mmm = mmul(mm, base, m);
            //pm(mm);
            //pm(mmm);
            
            Matrix f = mexp(n-2, m, base, id);
            //pm(f);
            int result = (int)(((ll)_2*f.m[0][0] + (ll)_1*f.m[1][0] + (ll)_0*f.m[2][0])%m);
            printf("%d\n", result);
            
            //pm(base);
        }
        
    }
}