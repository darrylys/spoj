#include<stdio.h>
#include<string.h>

#define MAXN 100010

int flag[MAXN];

int main() {
    int n, c, x, sum;
    char m;
    
    while (scanf("%d %d", &c, &n) && c) {
        sum=0;
        memset(flag, 0, c*sizeof(int));
        
        for (int i=1; i<=n; ++i) {
            scanf("%d", &x);
            sum += x;
            sum %= c;
            
            if (sum == 0) {
                for (int j=1; j<=i; ++j) {
                    printf("%d ", j);
                }
                putchar('\n');
                break;
            }
            
            if (flag[sum] == 0) {
                flag[sum] = i;
            } else {
                for (int j=flag[sum]+1; j<=i; ++j) {
                    printf("%d ", j);
                }
                putchar('\n');
                break;
            }
        }
        while ((m=getchar()) != '\n') ; //killing characters
    }
    return 0;
}