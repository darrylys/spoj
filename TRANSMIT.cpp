#include<cstdio>
#include<cstdlib>

typedef struct {
    int x;
    int y;
    double cosine2;
    int a;                  //delta_y
    int b;                  //delta_x
} Point;

int cmp( const void* a, const void* b ) {
    Point* arg1 = (Point*) a;
    Point* arg2 = (Point*) b;
    if( arg1->cosine2 < arg2->cosine2 ) return 1;
    else if( arg1->cosine2 == arg2->cosine2 ) return 0;
    else return -1;
}

int gcd(int a, int b) {
    if (b==0) return a;
    else return gcd(b,a%b);
}

int abs(int a) {
    return (a>=0)?a:-a;
}

int main() {
    Point pt[160];
    int a, b, n; double c;
    int tx, ty;
    int upnum, downnum, cntr = 0, infield, max, loss, na, nb, gain;
    int neg, pos;
    while (1) {
        scanf("%d %d %lf", &a, &b, &c);
        if (c < 0.0) break;
        scanf("%d",&n);
        upnum = downnum = 0;
        neg = 0; pos = 0;
        cntr = 0;
        for (int i=0;i<n;i++) {
            scanf("%d %d", &tx, &ty);
            
            if ((tx-a)*(tx-a) + (double)(ty-b)*(ty-b) > c*c) continue;
            
            pt[cntr].x = tx - a;
            pt[cntr].y = ty - b;
            
            if (pt[cntr].y <= 0) downnum++;
            if (pt[cntr].y >= 0) upnum++;
            if (pt[cntr].y == 0 && pt[cntr].x < 0) neg++;
            if (pt[cntr].y == 0 && pt[cntr].x > 0) pos++;
            
            //find grad
            int div = gcd(abs(pt[cntr].x), abs(pt[cntr].y));
            int dx = pt[cntr].x, dy = pt[cntr].y;
            if ((dx < 0 && dy < 0) || (dx > 0  && dy > 0) || dx == 0 || dy == 0) {
                pt[cntr].a = abs(dy)/div;
                pt[cntr].b = abs(dx)/div;
            } else {
                pt[cntr].a = -abs(dy)/div;
                pt[cntr].b = abs(dx)/div;
            }
            cntr++;
        }
        n = cntr;
        //printf("n=%d\n", n);
        for (int i=0; i<n; i++) {
            if (pt[i].y > 0) {
                if (pt[i].x >= 0) {
                    pt[i].cosine2 = (pt[i].x*pt[i].x)/((double)(pt[i].x*pt[i].x + pt[i].y*pt[i].y));
                } else {
                    pt[i].cosine2 = -(pt[i].x*pt[i].x)/((double)(pt[i].x*pt[i].x + pt[i].y*pt[i].y));
                }
            } else if (pt[i].y < 0) {
                if (pt[i].x >= 0) {
                    pt[i].cosine2 = -(pt[i].x*pt[i].x)/((double)(pt[i].x*pt[i].x + pt[i].y*pt[i].y));
                } else {
                    pt[i].cosine2 = (pt[i].x*pt[i].x)/((double)(pt[i].x*pt[i].x + pt[i].y*pt[i].y));
                }
            } else {
                if (pt[i].x >= 0) pt[i].cosine2 = 1.0;
                else pt[i].cosine2 = -1.0;
            }
        }
        qsort(pt, n, sizeof(pt[0]), cmp);
        //printf("up = %d down = %d\n", upnum, downnum);
        max = 0; infield = upnum; loss = 0; gain = 0;
        if (infield > max) max = infield;
        for (int i=0; i<n;) {
            if (pt[i].cosine2 == -1.0) break;
            na = pt[i].a;
            nb = pt[i].b;
            infield -= loss;
            //infield += gain;
            //if (infield > max) max = infield;
            loss = 0; gain = 0;
            for (int j=i; j<n;j++) {
                if (na == pt[j].a && nb == pt[j].b) {
                    if (pt[j].y < 0) {
                        gain++;
                    } else if (pt[j].y >= 0) {
                        loss++;
                    }                    
                } else break;
            }
            i+=gain+loss;
            infield += gain;
            if (infield > max) max = infield;
        }
        
        /*infield -= loss;
        infield += gain;
        if (infield > max) max = infield;
        printf("up infield = %d\n", infield);*/
        
        infield = downnum; loss = neg; gain = 0;
        int st = 0;
        while (pt[st].cosine2 == 1.0) st++;
        for (int i=st; i<n;) {
            if (pt[i].cosine2 == 1.0) break;
            //printf("x=%d y=%d\n", pt[i].x, pt[i].y);
            na = pt[i].a;
            nb = pt[i].b;
            infield -= loss;
            
            //printf("down infield = %d\n", infield);
            
            loss = 0; gain = 0;
            //printf("loss = %d, gain=%d\n", loss, gain);
            for (int j=i; j<n; j++) {
                if (na == pt[j].a && nb == pt[j].b) {
                    if (pt[j].y <= 0) {
                        loss++;
                    } else if (pt[j].y > 0) {
                        gain++;
                    }     
                } else break;
            }
            i += gain+loss;
            infield += gain;
            if (infield > max) max = infield;
        }
        /*infield -= loss;
        infield += gain;
        if (infield > max) max = infield;*/
        //printf("down infield = %d\n", infield);
        printf("%d\n", max);
    }
    return 0;
}
