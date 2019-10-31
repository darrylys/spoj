#include<cstdio>

int main() {
    int a, b;
    while (true) {
        scanf("%d%d",&a,&b);
        if (a+b == -2) break;
        if (a == 1 || b == 1) printf("%d+%d=%d\n",a,b,a+b);
        else printf("%d+%d!=%d\n",a,b,a+b);
    }
}
