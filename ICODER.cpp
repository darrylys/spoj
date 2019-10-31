#include<cstdio>
#define MOD 65536

int gcd(int a, int b) {
    if (b==0) return a;
    else return gcd(b,a%b);
}

int main() {
    int n, a, b;
    int var;
    char instr[5];
    while (scanf("%d",&n) && n) {
        var = MOD;
        while (n--) {
            scanf("%s %d", instr, &a);
            if (instr[0] == 'M') {
                var /= gcd(a, var);
            }
        }
        printf("%d\n", var);
    }
    return 0;
}