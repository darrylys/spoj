#include<stdio.h>

#define ull unsigned long long
#define LIM 10000000
#define MAXN 16

int aIAR[MAXN];
int aFA[MAXN];

inline int IAR(int n) {
    if (n<0) return 0;
    else return aIAR[n];
}

inline int FA(int n) {
    if (n<0) return 0;
    else return aFA[n];
}

void build() {
    aIAR[1] = 0;
    aFA[1] = 10;
    
    for (int i=2; i<MAXN; ++i) {
        aIAR[i] = aIAR[i-1] + aFA[i-1];
        aFA[i] = 9*aIAR[i-1];
    }
}

void fillK(int K, char* buf) {
    
    int k = K;
    int Nlen = 0;
    for (int _n=1; _n<MAXN ; ++_n) {
        if (k > IAR(_n)/10*9) {
            k -= IAR(_n)/10*9;
        } else {
            Nlen = _n;
            break;
        }
    }
    
    int prevdigit = -1;
    for (int n=0, quot; n<Nlen; ) {
        
        for (int d=(n==0); d<=9; ++d) {
            if (d != prevdigit) {
                quot = IAR(Nlen-n)/10;
            } else {
                quot = IAR(Nlen-n+1)/10;
            }
            if (k > quot) {
                k-= quot;
            } else {
                if (prevdigit != d) {
                    buf[n] = buf[n+1] = '0' + d;
                    n += 2;
                } else {
                    buf[n] = '0' + d;
                    n += 1;
                }
                prevdigit = d;
                break;
            }
        }
    }
    
    buf[Nlen] = '\0';
    
}

int main() {
    build();
    
    int t, K;
    char buf[MAXN+1];
    
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &K);
        fillK(K, buf);
        printf("%s\n", buf);
    }
    
}
