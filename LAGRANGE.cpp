#include<cstdio>

#define N (1<<15)

int tally[N<<1];

void make() {
    for (int i=1; i*i < N; i++) {
        tally[i*i]++;
    }
    
    for (int i=1; i*i/2 < N; i++) {
        for (int j=i; j*j + i*i < N; j++) {
            tally[i*i+j*j]++;
        }
    }
    
    for (int i=1; i*i < N; i++) {
        int i2 = i*i;
        for (int j=i; i2 + j*j < N; j++) {
            int i2j2 = i2 + j*j;
            for (int k=j; i2j2 + k*k < N; k++) {
                tally[i2j2 + k*k]++;
            }
        }
    }
    
    for (int i=1; i*i < N; i++) {
        int i2 = i*i;
        for (int j=i; i2 + j*j < N; j++) {
            int i2j2 = i2 + j*j;
            for (int k=j; i2j2 + k*k < N; k++) {
                int i2j2k2 = i2j2 + k*k;
                for (int l=k; i2j2k2 + l*l < N; l++) {
                    tally[i2j2k2 + l*l]++;
                }
            }
        }
    }
}

int main() {
    make();
    int n;
    while (scanf("%d", &n) && n) {
        printf("%d\n", tally[n]);
    }
    return 0;
}