#include<stdio.h>

int phi[1<<20];
int mark[1<<20];
char remap[1<<20];

int build() {
    phi[1] = 1;
    
    for (int i=2; i<=1000; ++i) {
        if (!mark[i]) {
            for (int j=i*i; j<=1000000; j+=i) {
                mark[j] = i;
            }
        }
    }
    
    for (int i=2; i<=1000000; ++i) {
        if (!mark[i]) {
            phi[i] = i-1;
        } else {
            if (i % (mark[i] * mark[i]) == 0) {
                phi[i] = mark[i] * phi[i/mark[i]];
            } else {
                phi[i] = (mark[i]-1) * phi[i/mark[i]];
            }
        }
        remap[phi[i]] = 1;
    }
    
}

int main() {
    build();
    int t, a, b, c, k;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d %d %d", &a, &b, &c, &k);
        printf("%s\n", remap[k] ? "Yes" : "No");
    }
    return 0;
}

