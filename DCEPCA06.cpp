#include<stdio.h>

//#define DEBUG
#define MOD 1000000007
#define ll long long

typedef struct {
    int m[10][10];
} Mk;

Mk ID;
Mk base2;

#ifdef DEBUG
void printMk(Mk& a, char* text) {
    printf("%s\n", text);
    for (int i=0; i<10; ++i) {
        for (int j=0; j<10; ++j) {
            printf("%d ", a.m[i][j]);
        }
        putchar ('\n');
    }
    printf("==============================\n");
}
#endif

void fillID() {
    for (int i=0; i<10; ++i) {
        ID.m[i][i]=1;
    }
}

void fillBase2(int k) {
    
    if (k >=2 && k <= 4) {
        for (int i=0; i<10; ++i) {
            for (int j=0; j<10; ++j) {
                base2.m[i][j] = j<=i-k || j>=i+k;           
            }
        }
    } else {
        for (int i=0; i<10-k; ++i) {
            for (int j=10-k-1; j>10-k-i-1; --j) {
                base2.m[i][j] = 0;
            }
            for (int j=10-k-i-1; j>=0; --j) {
                base2.m[i][j] = 1;
            }
        }
    }
}

Mk matrixmul(Mk& a, Mk& b, int mod, int _k) {
    Mk c;
    
    if (_k!=0) {
        for (int i=0; i<10-_k; ++i) {
            for (int j=0; j<10-_k; ++j) {
                c.m[i][j]=0;
                for (int k=0; k<10-_k; ++k) {
                    c.m[i][j] = (int)((c.m[i][j] + ((ll)a.m[i][k] * b.m[k][j]))%mod);
                }            
            }
        }
    } else {
        for (int i=0; i<10-_k; ++i) {
            for (int j=0; j<i; ++j) {
                c.m[i][j] = c.m[j][i];
            }
            for (int j=i; j<10-_k; ++j) {
                c.m[i][j]=0;
                for (int k=0; k<10-_k; ++k) {
                    c.m[i][j] = (int)((c.m[i][j] + ((ll)a.m[i][k] * b.m[k][j]))%mod);
                }            
            }
        }
    }
    return c;
}

int bigmodsgl(int base, int exp, int mod) {
    if (exp==0) return 1;
    if (exp==1) return base;
    int half = bigmodsgl(base, exp>>1, mod);
    if (exp&1) {
        return (int)((((ll)half*half)%mod * (ll)base)%mod);
    } else {
        return (int)(((ll)half*half)%mod);
    }
}

Mk bigmodmtr(int exp, int mod, int k, int side) {
    if (exp==0) return ID;
    if (exp==1) {
        fillBase2(k);
        //printMk(base2, "base2 refill!");
        return base2;
    }
    Mk half = bigmodmtr(exp>>1, mod, k, side);
    int x = (k <= 4)? x=0: x=k;
    if (exp&1) {
        Mk temp = matrixmul(half, half, mod, x);
        Mk res = matrixmul(temp, base2, mod, x);
        return res;
    } else {
        Mk temp = matrixmul(half, half, mod, x);
        return temp;
    }
}

int getFinalSum( Mk& up, int k, int mod) {
    int sum=0;
    for (int i=9-k, r=0; i>=0; --i) {
        sum = ((sum + ((2*i+1)*(ll)up.m[r++][0]))%mod);
    }
    return sum;
}

int getFinalSum234(Mk& mat, int k, int mod) {
    int sum=0;
    
    for (int i=1; i<10; ++i) {
        for (int j=0; j<10; ++j) {
            sum = (sum + mat.m[i][j])%mod;
        }
    }
    
    return sum;
}

int main() {
    int t, n, k;
    fillID();
    scanf ("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &k);
        switch (k) {
            case 0: {
                int ten = bigmodsgl(10, n-1, MOD);
                printf("%d\n", ((ll)9*ten)%MOD);
            } break;
            
            case 1: {
                printf("%d\n", bigmodsgl(9, n, MOD));
            } break;
            
            case 9: {
                printf("1\n");
            } break;
            
            case 8:
            case 7:
            case 6:
            case 5: {
                Mk up = bigmodmtr(n-1, MOD, k, 2);
                //printMk(up, "upper!");
                printf("%d\n", getFinalSum(up, k, MOD));
            } break;
            
            default: {
                Mk up = bigmodmtr(n-1, MOD, k, 2);
                //printMk(up, "upper!");
                printf("%d\n", getFinalSum234(up, k, MOD));
            } break;
        }
    }
}