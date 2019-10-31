//impl direct Physics Formula

#include<cstdio>
#include<cmath>

double g = 9.8;

int main() {
    int V, H;
    double x, costheta, sintheta;
    while (true) {
        scanf("%d%d",&V,&H);
        if (V == -1 && H == -1) break;
        if (V == 0) {
            printf("0.000000\n");
        } else {
            costheta = sqrt((V*V + 2.0*g*H) / (2.0*(V*V+g*H)));
            sintheta = sqrt((V*V)/(2.0*(V*V+g*H)));
            x = 1/g*V*costheta*(V*sintheta+sqrt(V*V*sintheta*sintheta+2.0*g*H));
            printf("%.6lf\n", x);
        }
    }
}
