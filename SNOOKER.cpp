#include<stdio.h>

int gcd(int a, int b) {
    if (b == 0) return a;
    else return gcd(b, a%b);
}

int main() {
    int m, n;
    while (scanf("%d %d", &m, &n) && n) {
        int div = gcd(m, n);
        m /= div;
        n /= div;
        printf("%d\n", (2*m + 2*n - 4) * 2);
    }
    return 0;
}