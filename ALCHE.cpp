#include<cstdio>

int gcd(int a, int b) {
    int c;
    while (b!=0) {
        c = a%b;
        a=b;
        b=c;
    }
    return a;
}

int main() {
    int a; int b;
    while (1) {
        scanf("%d%d",&a,&b);
        if (a==-1 && b==-1) break;
        int dem = gcd(a,b);
        if (b/dem == 37 && a/dem == 1000) putchar('Y');
        else putchar('N');
        putchar('\n');
    }
}
