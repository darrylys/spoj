#include<cstdio>

long long find(int num) {
    long long prev = 0;
    long long tmp = 0;
    int after;
    int n = num;
    long long mul = 1;
    while (n>0) {
        after = (n/10);
        tmp += after * 45LL * mul;
        tmp += (n%10)*(n%10 - 1) / 2 * mul;
        tmp += (n%10)*(prev+1);
        prev += (n%10)*mul;
        n/=10;
        mul *= 10LL;
    }
    //printf("\tprev=%lld\n", prev);
    return tmp;
}

int main() {
    int a, b; long long res;
    while (true) {
        scanf("%d%d\n", &a, &b);
        if (a + b == -2) break;
        if (a == b) {
            res = 0;
            while (a>0) {
                res += a%10;
                a/=10;
            }
        } else {
            long long resb = find(b);
            long long resa;
            if (a == 0) res = resb;
            else {
                resa = find(a-1);
                res = resb-resa;
            }
        }
        printf("%lld\n", res);
    }
}
