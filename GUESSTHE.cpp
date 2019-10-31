#include<stdio.h>
#include<string.h>

#define ll long long int

char clue[25];

int gcd(int a, int b) {
    if (b == 0) return a;
    else return gcd(b, a%b);
}

int main() {
    while (scanf("%s", clue)) {
        if (clue[0] == '*') break;
        
        if (clue[0] == 'N') {printf("-1\n"); continue; }
        int len = strlen(clue);
        ll num = 1;
        
        for (int i=1; i<len; i++) {
            if (clue[i] == 'Y') {
                num = num/gcd(num, i+1)*(i+1);
            }
        }
        
        for (int i=1; i<len; i++) {
            if (clue[i] == 'N' && num%(i+1) == 0) {
                num = -1;
                break;
            }
        }
        
        printf("%lld\n", num);
    }
    return 0;
}