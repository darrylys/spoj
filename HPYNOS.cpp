//brute force approach

#include<cstdio>

bool flag[900];

int main() {
    int n, cntr=0, tmp;
    scanf("%d", &n);
    while (true) {
        tmp = 0;
        while (n>0) {
            tmp += (n%10)*(n%10);
            n/=10;
        }
        n = tmp;
        cntr++;
        if (n==1) {
            printf("%d\n", cntr);
            break;
        }
        if (flag[n]) {
            printf("-1\n");
            break;
        }
        flag[n] = true;
    }
    return 0;
}
