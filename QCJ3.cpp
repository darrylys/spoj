#include<stdio.h>

int arr[30];

int main() {
    int t;
    scanf("%d", &t);
    
    while (t--) {
        int n, x, r = 0;
        scanf("%d", &n);
        
        for (int i=1; i<=n; ++i) {
            scanf("%d", &x);
            
            if (x&1) r^=i;
        }
        if (r) printf("Tom Wins\n");
        else printf("Hanks Wins\n");
    }
    return 0;
}