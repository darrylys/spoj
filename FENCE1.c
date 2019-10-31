#include<stdio.h>
#define PI 3.14159265358

int main() {
    int L;
    while(scanf("%d",&L) && L) printf("%.2lf\n", (L*L)/2.0/PI);
    return 0;
}
