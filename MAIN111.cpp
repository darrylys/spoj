#include<stdio.h>

#define MP 100001
#define SH 7777
#define ull unsigned long long

int map[] = {0, 1, 4, 6, 8, 9};

char prime[MP];
char fplag[MP];
int sumdp[MP];

int buildpr() {
    int f=0;
    for (int i=3; i*i<=MP; i+=2) {
        if (!prime[i]) {
            for (int j=i*i; j<MP; j+= i) {
                prime[j] = 1;
            }
        }
    }
    return f+1;
}

char isPrime(int n) {
    if (n == 2) return 1;
    if (n == 0 || n == 1 || !(n&1)) return 0;
    return !prime[n];
}

int b6210(int b6) {
    int b10 = 0;
    int mul = 1;
    while (b6) {
        b10 += map[b6%6]*mul;
        b6 /= 6;
        mul *= 10;
    }
    return b10;
}

void start() {
    for (int i=0, nd=1, b6=6, b10=1; i<SH; ++i) {
        if (i >= b6) {
            nd++;
            b6 *= 6;
            b10 *= 10;
        }
        int rn = b6210(i);
        int back = rn%b10;
        //printf("rn=%d, back=%d\n", rn, back);
        
        if (!fplag[back]) {
            fplag[rn] = 0;
            sumdp[rn] = 1;
            
            int fd = i/(b6/6);
            //printf("checked x=%d, nd=%d, b6=%d, b10=%d\n", map[fd]*b10, nd , b6, b10);
            
            for (int j=0; j<(1<<(nd-1)); ++j) {
                int v = i;
                int m = j;
                int x = 0;
                int mul = 1;
                
                while (v && m) {
                    if (m&1) {
                        x += map[v%6] * mul;
                        mul*=10;
                    }
                    v/=6;
                    m>>=1;
                }
                
                x += map[fd]*mul;
                
                if (isPrime(x)) {
                    fplag[rn] = 1;
                    sumdp[rn] = 0;
                    break;
                }
            }
        } else {
            fplag[rn] = 1;
            sumdp[rn] = 0;
        }
        
        //printf("\t\tfplag[%d]=%d\n", rn, fplag[rn]);
    }
    
    for (int i=1; i<MP; ++i) {
        sumdp[i] += sumdp[i-1];
    }
}

int main() {
    //printf("primes=%d\n",);
    buildpr();
    start();
    
    int t, a, b;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &a, &b);
        int zmax = (a>b)?a:b;
        int zmin = (a<b)?a:b;
        printf("%d\n", sumdp[zmax] - sumdp[zmin-1]);
    }
    /*
    printf("\n");
    for (int i=1; i<=100000; ++i) {
        printf("verdict %d=%d\n", i, sumdp[i] - sumdp[i-1]);
    }
    */
    return 0;
}
