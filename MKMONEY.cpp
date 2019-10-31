#include<cstdio>
#include<cmath>

int main() {
    double start, interest; int comp, cntr = 1;
    while (scanf("%lf%lf%d",&start, &interest, &comp) && comp) {
        double pertime = interest/comp;
        double add;
        double run = start;
        for (int i=0; i<comp; i++) {
            add = run * pertime;
            add = floor(add);
            add /= 100.0;
            run += add;
        }
        printf("Case %d. $%.2lf at %.2lf%% APR compounded %d times yields $%.2lf\n",
            cntr++,start,interest,comp,run);
    }
    return 0;
}
