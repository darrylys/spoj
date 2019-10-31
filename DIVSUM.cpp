#include<cstdio>

int main() {
    int test, n, c;
    scanf("%d", &test);
    
    while (test--) {
        scanf("%d", &n);
        c = 1;
        if (n == 1) c = 0;
        else if (n%2 == 0) {
            for (int i=2; i*i <= n; i++) {
                if (n%i == 0) {
                    if (i*i < n) {
                        c += i + n/i;
                    } else {
                        c += i;
                    }
                }
            }
        } else {
            for (int i=3; i*i <= n; i+=2) {
                if (n%i == 0) {
                    if (i*i < n) {
                        c += i + n/i;
                    } else {
                        c += i;
                    }
                }
            }
        }
        printf("%d\n", c);
    }
    return 0;
}