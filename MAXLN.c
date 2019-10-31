#include<stdio.h>
#define ll long long

int main() {
    int c=1, t, r;
    scanf("%d",&t);
    while(t--) {
        scanf("%d",&r);
        printf("Case %d: %lld.25\n",c++,(ll)4*(ll)r*r);
    }
    return 0;
}
