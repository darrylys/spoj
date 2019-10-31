#include<cstdio>
#include<cmath>

double cal(double a) {
    if (fabs(a) < 1e-6) return 0.0;
    else return a;
}

int main() {
    int t;
    double a,b,c,d,AX,base,CX,AF,PF,BX,PX, vert,res;
    double da,db,dc,L;
    scanf("%d",&t);
    while(t--){
        scanf("%lf%lf%lf%lf",&a,&da,&db,&dc);
        L = a*3.0*da / 2.0;
        b = 2.0*L/3.0/db;
        c = 2.0*L/3.0/dc;
        d = sqrt(2*b*b+2*c*c-a*a)/2.0;
        AX = 3.0*da;
        //printf("d=%lf AX=%lf\n", d, AX);
        base = 2.0*sqrt(cal(d*d - AX*AX)) / 3.0;
        CX = (b*b-c*c+a*a)/(2*a);
        AF = (b*b+c*c-a*a)/(2*c);
        BX = a-CX;
        PF = (BX*AX)/(c + BX*CX/AF);
        PX = CX*PF/AF;
        vert = PX - da;
        //printf("base=%lf vert=%lf\n", base, vert);
        res = sqrt(base*base + vert*vert);
        printf("%.3lf %.3lf\n",L, res);
    }
}
