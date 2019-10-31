#include<stdio.h>

int gcd(int a, int b) {
    if (b == 0) return a;
    else return gcd(b, a%b);
}

int main() {
    int w, h;
    while (scanf("%d %d", &w, &h) && w) {
        int div = gcd(w,h);
        long long d = w/div * (long long)h/div;
        printf("%lld\n", d);
    }
    return 0;
}