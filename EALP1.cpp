#include<stdio.h>

int ar[1005];

int main() {
    int t, N, gt, wp, c=1;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &N);
        gt = wp = 0;
        for (int i=0; i<N; ++i) {
            scanf("%d", &ar[i]);
            gt ^= ar[i];
        }
        for (int i=0, tv; i<N; ++i) {
            wp += (gt ^ ar[i]) < ar[i];
        }
        printf("Case %d: %d\n", c++, wp);
    }
    return 0;
}