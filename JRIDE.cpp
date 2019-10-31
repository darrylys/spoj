#include<cstdio>

int main() {
    int t, s, in, maxsum, maxs, maxe, cntr=1;
    int tempsum, temps, tempe;
    bool nice;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&s);
        maxsum = 0;
        tempsum = 0;
        nice = false;
        temps = 1;
        tempe = 1;
        for (int i=1; i<s; i++) {
            scanf("%d",&in);
            tempsum += in;
            tempe++;
            if (tempsum > maxsum) {
                nice = true;
                maxsum = tempsum;
                maxs = temps;
                maxe = tempe;
            } else if (tempsum == maxsum) {
                if (tempe - temps > maxe - maxs) {
                    maxs = temps;
                    maxe = tempe;
                }
            }
            if (tempsum < 0) {
                tempsum = 0;
                temps = tempe;
            }
        }
        if (nice) printf("The nicest part of route %d is between stops %d and %d\n",cntr++,maxs,maxe);
        else printf("Route %d has no nice parts\n", cntr++);
    }
}
