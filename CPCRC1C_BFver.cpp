//brute force version to check program correctness

#include<cstdio>

int get_digit_sum(int a) {
    int res=0;
    while (a>0) {
        res+=a%10;
        a/=10;
    }
    return res;
}

int main() {
    int a = 617263, b = 927394856;
    long long res = 0;
    for (int i=a; i<=b; i++) {
        res += get_digit_sum(i);
    }
    printf("%lld\n", res);
}
