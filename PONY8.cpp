#include<stdio.h>

#define ull unsigned long long
#define LIM 1000000000000000001LL

ull f[20];
ull _9e[20];

int main() {
    f[1] = 8;
    f[0] = 0;
    _9e[0] = 1;
    _9e[1] = 9;
    int ck=0;
    
    ull m = 9;
    int last;
    for (int i=2; ; ++i) {
        f[i] = f[i-1] + 8*m*i;
        m *= 9;
        _9e[i] = m;
        //printf("9e=%llu\n", _9e[i]);
        //printf("f=%llu\n", f[i]);
        if (f[i] >= LIM) {
            last = i+1;
            break;
        }
    }
    //printf("%d\n", last);
    
    int t;
    ull n;
    scanf("%d", &t);
    while (t--) {
        scanf("%llu", &n);
        int u=0, v=last, c, near;
        while(1) {
            c=(u+v)/2;
            if (u>=v) {
                near = u-1;
                break;
            }
            if (f[c] > n) {
                v=c;
            } else if (f[c] < n) {
                u=c+1;
            } else {
                near = c;
                break;
            }
        }
        //printf("near=%d\n", near);
        ull diff = n-f[near];
        
        //printf("difference=%llu\n", diff);
        
        ull part = diff / (near+1);
        int wdigit = diff%(near+1);
        
        //printf("part=%llu, wdigit=%d, n=%llu\n", part, wdigit, n);
        
        ull od = part / _9e[near-wdigit];
        int pdigit = od%9;
        
        if (wdigit==0) {
            pdigit++;
            if (pdigit >= 5) pdigit++;
        } else {
            if (pdigit >= 5) pdigit++;
        }
        printf("%d\n", pdigit);
        //++ck;
        //if (ck % 80 == 0) {
        //    putchar('\n');
        //}
        //putchar('\n');
        
    }
    return 0;
}
