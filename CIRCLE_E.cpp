// Descartes theorem on tangent circles (kissing circles)

#include<stdio.h>
#include<math.h>

int main() {
    int t;
    scanf("%d", &t);
    
    double r1, r2, r3, k1, k2, r;
    
    while (t--) {
        scanf("%lf %lf %lf", &r1, &r2, &r3);
        
        k1 = 1/r1 + 1/r2 + 1/r3 + 2*sqrt(1/(r1*r2) + 1/(r2*r3) + 1/(r1*r3));
        //k2 = 1/r1 + 1/r2 + 1/r3 - 2*sqrt(1/(r1*r2) + 1/(r2*r3) + 1/(r1*r3));
        
        printf("%lf\n", 1/k1);
        
    }
}