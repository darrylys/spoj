//not ready

#include<cstdio>
#include<cmath>

double max_area(double a, double b, double c, double d) {
    double s = (a+b+c+d)/2.0;
    
    double area = sqrt((s-a)*(s-b)*(s-c)*(s-d));
    
    return area;
}

int main() {
    int test;
    double a, b, c, d;
    scanf("%d", &test);
    while (test--) {
        scanf("%lf %lf %lf %lf", &a, &b, &c, &d);
        printf("%.2lf\n", max_area(a,b,c,d));
    }
    return 0;
}