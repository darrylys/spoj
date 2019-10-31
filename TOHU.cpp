#include<stdio.h>

int main() {
    int t, n;
    scanf("%d", &t);
    double f;
    while (t--) {
        scanf("%d", &n);
        printf("%.11lf\n", 0.75 - 1.0/((n+1)*2.0) + 1.0/((n+2)*2.0));
    }
    return 0;
}