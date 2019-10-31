#include<stdio.h>

int a[1010];

int main() {
    int n;
    scanf("%d", &n);
    
    for (int i=0; i<n; ++i) {
        scanf("%d", &a[i]);
    }
    
    int xi=0, xj=0, vx=0, tx;
    for(int i=0 ;i<n; ++i) {
        tx = a[i];
        if (vx < tx) {
            vx = tx;
            xi = i;
            xj = i;
        } else if (vx == tx) {
            if (i < xi || (i == xi && i < xj)) {
                xi = i;
                xj = i;
            }
        }
        
        for (int j=i+1; j<n; ++j) {
            tx ^= a[j];
            if (vx < tx) {
                vx = tx;
                xi = i;
                xj = j;
            } else if (vx == tx) {
                if (i < xi || (i == xi && j < xj)) {
                    xi = i;
                    xj = j;
                }
            }
        }
    }
    
    printf("%d\n%d %d\n", vx, xi+1, xj+1);
}