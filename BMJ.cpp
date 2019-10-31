#include<cstdio>

int getring(int n) {
    int x = 0;
    while (3*x*x + 3*x + 1 < n) x++;
    return x;
}

void run(int n) {
    int x = getring(n);
    int start = 3*x*x + 3*x + 1, side = 0;
    while (start >= n) {
        start -= x;
        side++;
    }
    start += x;
    int diff = start - n;
    switch (side) {
        case 1: printf("%d %d\n", x, -diff); break;
        case 2: printf("%d %d\n", x-diff, -x); break;
        case 3: printf("%d %d\n",-diff ,-x+diff); break;
        case 4: printf("%d %d\n", -x, diff); break;
        case 5: printf("%d %d\n", -x+diff, x); break;
        case 6: printf("%d %d\n", diff, x-diff); break;
    }
}

int main() {
    int n;
    while (scanf("%d",&n)!=EOF) {
    	if (n == 1) printf("0 0\n");
        else run(n);
    }
    return 0;
}
