#include<stdio.h>

//186583×587117

#define ull unsigned long long
#define MOD 109546051211LL
#define P2 587117
#define P2INVP1 166628
#define P1 186583
#define P1INVP2 62792

int main() {
    int N;
    scanf("%d", &N);
    if (N >= P2) {
        printf("0\n");
    } else {
        ull ffmup1 = 1;
        ull facp1 = 1;
        ull ffmup2 = 1;
        ull facp2 = 1;
        
        for (int i=1; i<=N; ++i) {
            facp1 = (facp1*i)%P1;
            ffmup1 = (ffmup1*facp1)%P1;
            
            facp2 = (facp2*i)%P2;
            ffmup2 = (ffmup2*facp2)%P2;
        }
        
        ull res1 = ((ffmup1*P2)%MOD * P2INVP1)%MOD;
        ull res2 = ((ffmup2*P1)%MOD * P1INVP2)%MOD;
        
        printf("%llu\n", (res1+res2)%MOD);
    }
}
