#include<stdio.h>

#define HORZ 0
#define VERT 1

#define max(a,b) (((a)>(b))?(a):(b))
#define min(a,b) (((a)<(b))?(a):(b))
#define abs(a) (((a)>=0)?(a):(-(a)))

int main() {
    int n;
    int pa, pb, ca, cb;
    int data[2];
    int pw, ph, cw, ch, tv, th, kk;
    
    scanf("%d", &n);
    pa = pb = 0;
    scanf("%d %d", &ca, &cb);
    
    data[HORZ] = max(ca,cb);
    data[VERT] = min(ca,cb);
    
    pa = ca, pb = cb;

    while (--n) {
        scanf("%d %d", &ca, &cb);
        //printf("ca=%d, cb=%d\n", ca, cb);
        //left tree
        
        //vertical
        pw = min(pa,pb);
        ph = max(pa,pb);
        cw = min(ca,cb);
        ch = max(ca,cb);
        
        tv = data[VERT] + cw;
        tv += abs(ch-ph);
        //printf("cw = %d, abs(ch-ph) = %d, data[VERT] = %d, tv = %d\n", cw, abs(ch-ph), data[VERT], tv);
        //horizontal
        cw = max(ca,cb);
        ch = min(ca,cb);
        
        th = data[VERT] + cw;
        th += abs(ch-ph);
        //printf("th=%d\n", th);
        
        //right tree
        
        //vertical
        pw = max(pa,pb);
        ph = min(pa,pb);
        cw = min(ca,cb);
        ch = max(ca,cb);
        
        kk = data[HORZ] + cw;
        kk += abs(ch-ph);
        data[VERT] = max(tv, kk);
        
        //horizontal
        cw = max(ca,cb);
        ch = min(ca,cb);
        
        kk = data[HORZ] + cw;
        kk += abs(ch-ph);
        data[HORZ] = max(th, kk);
        
        pa = ca;
        pb = cb;
    }
    printf("%d\n", max(data[HORZ], data[VERT]));
    return 0;
}