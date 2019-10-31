#include<stdio.h>

#define ll long long
#define MXN 1000001

ll far[MXN];

void build() {
    for (int i=1; i<MXN; ++i) {
        for (int j=2*i; j<MXN; j+=i) {
            far[j] += i;
        }
    }
    for (int i=3; i<MXN; ++i) {
        far[i] = far[i-1] + far[i];
    }
    far[0] = far[1] = 0;
}

int main() {
    build();
    int t, n;
    scanf("%d", &t);
    while(t--) {
    
        scanf("%d", &n);
        printf("%lld\n", far[n]);
    }
}
