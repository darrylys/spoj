#include<cstdio>
#include<cmath>
#include<algorithm>

double deg[1010];
char temp[50];

int main() {
    int t,n; double max, diff;
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        for(int i=0;i<n;i++){
            scanf("%s%lf",temp,&deg[i]);
        }
        std::sort(deg, deg+n);
        max = -1.0;
        for (int i=0; i<n-1; i++) {
            diff = deg[(i+1)] - deg[i];
            if (diff > max) max = diff;
        }
        diff = 360 + deg[0] - deg[n-1];
        if (diff > max) max = diff;
        printf("%.0lf\n", ceil((360.0 - max)*12.0));
    }
}
