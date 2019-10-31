#include<cstdio>
#define l long long

l getres(l a) {
    l mul = 1LL;
    l res = 0LL;
    while (mul <= a) {
        res += ((a+mul)/(2LL*mul))*mul;
        mul *= 2LL;
    }
    return res;
}

int main() {
    l a, b;
    scanf("%lld%lld", &a, &b);
    printf("%lld\n", getres(b) - getres(a-1));
    return 0;
}

