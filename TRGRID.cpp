#include<cstdio>

int main() {
    int t, h, w;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &h, &w);
        if (w>=h) {
            if (h%2) putchar('R');
            else putchar('L');
        } else {
            if (w%2) putchar('D');
            else putchar('U');
        }
        putchar('\n');
    }
    return 0;
}