#include<cstdio>

bool x[40010];
bool y[40010];

int main() {
    int t, w, h, n, a, b, maxx, maxy, curx, cury;
    scanf("%d",&t);
    while(t--){
        scanf("%d%d%d",&w,&h,&n);
        for (int i=0; i<w; i++) x[i] = false;
        for (int i=0; i<h; i++) y[i] = false;
        for (int i=0; i<n; i++) {
            scanf("%d%d",&a,&b);
            x[a-1] = true;
            y[b-1] = true;
        }
        curx = maxx = 0;
        for (int i=0; i<w; i++) {
            if (x[i]) {
                curx = 0;
            } else {
                curx++;
                if (curx > maxx) maxx = curx;
            }
        }
        cury = maxy = 0;
        for (int i=0; i<h; i++) {
            if (y[i]) {
                cury = 0;
            } else {
                cury++;
                if (cury > maxy) maxy = cury;
            }
        }
        printf("%d\n", maxx*maxy);
    }
}
