#include<stdio.h>

char a[100010];
char b[100010];
char c[100010];

int build() {
    a[0] = 4;
    for (int i=0; i<100000; ++i) {
        switch (i&3) {
            case 0:
            case 1:
            b[i] = 4;
            break;
            
            case 2:
            case 3:
            b[i] = 7;
            break;
        }
        
        a[i+1] = b[i];
    }
}

int getint() {
    char c;
    int x=0;
    while ((c=getchar())<'0' || c>'9') ;
    do {
        x = x*10 + c-'0';
    } while ((c=getchar())>='0' && c<='9');
    return x;
}

int main() {
    build();
    int t, N;
    t=getint();
    while (t--) {
        N=getint();
        for (int i=N-1, carry=0, tv; i>=0; --i) {
            tv = a[i] + b[i] + carry;
            if (tv>=10) {
                carry=1;
                tv-=10;
            } else {
                carry=0;
            }
            c[i] = tv;
        }
        for (int i=0; i<N; ++i) {
            putchar(c[i]+'0');
        }
        putchar('\n');
    }
}
