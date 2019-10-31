#include<stdio.h>
#include<math.h>
#define PI 3.141592653589793

double _max(double a, double b) {
    if(a<b) return b;
    else return a;
}

double calcVol(int w, int h) {
    double r;
    double v1 = -1.0, v2 = -1.0, v3 = -1.0;
    r = w/2.0;
    if (h-2.0*r >= 2*PI*r) {
        v1 = PI*r*r*w;
    }
    r = h/(2.0*(1+PI));
    if (2.0*r <= (double)w) {
        v2 = PI*r*r*w;
    }
    r = w/(2.0*PI);
    v3 = PI*r*r*(h-2.0*r);
    return _max(v1, _max(v2, v3));
}

int main() {
    int w, h;
    while (1) {
        scanf("%d%d", &w, &h);
        if (w==0 && h==0) break;
        printf("%.3lf\n", calcVol(w,h));
    }
    return 0;
}
