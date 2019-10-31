#include<cstdio>

int sgn[10005];

int abs(int a) {
    if (a >= 0) return a;
    else return -a;
}

int main() {
    int t, n, s;
    scanf("%d", &t);
    while (t--) {
        scanf("%d%d", &n, &s);
        int tip = n*(n-1)/2;
        int sum = 0;
        sgn[0] = 0;
        int cntr = 1;
        if (tip%2 == abs(s)%2) {
            if (s <= tip && s >= -tip) {
                for (int i=n-1; i>=1; i--) {
                    if (sum > s) {
                        sum -= i;
                        sgn[cntr] = sgn[cntr-1] - 1;
                    } else {
                        sum += i;
                        sgn[cntr] = sgn[cntr-1] + 1;
                    }
                    cntr++;
                }
                for (int i=0; i<n; i++) {
                    printf("%d\n", sgn[i]);
                }
            } else {
                printf("No\n");
            }
        } else {
            printf("No\n");
        }
        if (t > 0) 
            printf("\n");
        //printf("---\n");
    }
    return 0;
}