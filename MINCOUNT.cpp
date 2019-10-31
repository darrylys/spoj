#include<cstdio>
#define ull unsigned long long int

int main() {
    int test; ull h;
    scanf("%d",&test);
    while(test--) {
        scanf("%llu", &h);
        if (h<=(ull)1) printf("0\n");
        else if (h==(ull)2) printf("1\n");
        else {
            ull n;
            if ((h-1)%3 == 1) n = (h-1)/3;
            else if ((h-1)%3 == 2) n = (h-1)/3+1;
            else n = (h-1)/3;
            ull lf = h - 2*n;
            ull res = n*(n+1);
            if (lf % 2 == 0) {
                res += lf/2*(lf-1);
            } else {
                res += (lf-1)/2*lf;
            }
            printf("%llu\n", res);
        }
    }
    return 0;
}
