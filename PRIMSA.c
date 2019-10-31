#include<stdio.h>
#include<math.h>
#define PI 3.14159265358979
#define SIN60 0.866025403784439

int main() {
    int t;
    scanf("%d",&t);
    while(t--) {
        double v;
        scanf("%lf",&v);
        double a = pow(4.0*v, 1.0/3.0);
        double h = (2*v)/(a*a*SIN60);
        double s = a*a*SIN60 + 3.0*a*h;
        printf("%.6lf\n", s);
    }
    return 0;
}
