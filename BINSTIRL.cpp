#include<cstdio>

int main() {
    int m, n, d;
    scanf("%d", &d);
    while (d--) {
        scanf("%d %d", &n, &m);
        printf("%d\n", ((n-m)&((m-1)/2)) == 0);
    }
    return 0;
}
