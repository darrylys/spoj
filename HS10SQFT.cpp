#include<stdio.h>
#include<math.h>

#define ull unsigned long long

int main() {
    int t, c=0; ull N;
    bool found;
    scanf("%d",&t);
    while(t--) {
        scanf("%llu",&N);
        found = false;
        printf("Case #%d:\n", ++c);
        for (int a=2; ; ++a) {
            ull la = (ull)(a-1)*(a+1);
            if (la*la <= N) {
                if (!(N%la)) {
                    ull ba = N/la+1;
                    int sqrtb = (int)floor(sqrt((double)ba));
                    if ((ull)sqrtb*sqrtb == ba) {
                        if (!found) {
                            printf("%llu", N);
                            found = true;
                        }
                        printf("=(%d^2-1)*(%d^2-1)", a, sqrtb);
                    }
                }
            } else break;
        }
        if (!found) {
            printf("For n=%llu there is no almost square factorisation.", N);
        }
        printf("\n");
    }
}