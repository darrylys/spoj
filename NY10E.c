#include<stdio.h>
#define ll unsigned long long int
#define N 64
#define DIGIT 10

int main() {
    ll table[N][DIGIT];
    int i, j; ll sum;
    for (i=0;i<DIGIT;i++) table[0][i] = 1;
    for (i=1;i<N;i++) {
        table[i][9] = 1;
        sum = 1;
        for (j=DIGIT-2; j>=0; j--) {
            table[i][j] = table[i][j+1] + table[i-1][j];
            sum = sum + table[i][j];
        }
        printf(",%llu", sum);
    }
}
