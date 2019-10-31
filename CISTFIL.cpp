#include<cstdio>
#include<cstdlib>
#include<cmath>

#define MAXN 50002
#define START true
#define END false
#define ll long long int

using namespace std;

typedef struct {
    int b, h, w, d;
} Cistern;

typedef struct {
    int cistcode;
    int lvl;
    bool sgn;
} Baseh;

Baseh baseh[MAXN*2];
Cistern cistern[MAXN];

int cmp(const void* a, const void* b) {
    Baseh* p = (Baseh*) a;
    Baseh* q = (Baseh*) b;
    if (p->lvl > q->lvl) return 1;
    else if (p->lvl < q->lvl) return -1;
    else {
        if (p->sgn == q->sgn) return 0;
        else if (p->sgn == START && q->sgn == END) return 1;
        else return -1;
    }
}

int main() {
    int k, n, vol, currv, area;
    int lv; double finalh;
    int maxh = 0;
    scanf("%d", &k);
    while (k--) {
        scanf("%d", &n);
        int totalvol = 0;
        maxh = 0;
        for (int i=0;i<n;i++) {
            scanf("%d%d%d%d", &cistern[i].b, 
                &cistern[i].h, &cistern[i].w, &cistern[i].d);
            totalvol += cistern[i].h*cistern[i].w*cistern[i].d;
            if (maxh < cistern[i].b + cistern[i].h) maxh = cistern[i].b + cistern[i].h;
        }
        scanf("%d", &vol);
        currv = vol;
        if (currv > totalvol) {
            printf("OVERFLOW\n");
            continue;
        } else if (currv == totalvol) {
            printf("%d.00\n", maxh);
            continue;
        }
        for (int i=0;i<n;i++) {
            baseh[2*i].cistcode = i;
            baseh[2*i].lvl = cistern[i].b;
            baseh[2*i].sgn = START;
            baseh[2*i+1].cistcode = i;
            baseh[2*i+1].lvl = cistern[i].b+cistern[i].h;
            baseh[2*i+1].sgn = END;
        }
        qsort(baseh, 2*n, sizeof(baseh[0]), cmp);
        /*printf("testcase:\n");
        for (int i=0;i<2*n;i++) {
            printf("code=%d level=%d sign=%d\n", baseh[i].cistcode, 
                baseh[i].lvl, baseh[i].sgn);
        }*/
        lv = baseh[0].lvl;
        area = cistern[baseh[0].cistcode].w*cistern[baseh[0].cistcode].d;
        //printf("area = %d\n", area);
        for (int i=1;i<2*n && currv > 0;) {
            //printf("outer area = %d\n", area);
            if (baseh[i].sgn == START) {
                int nexth, diff;
                while (baseh[i].lvl == lv) {
                    area += cistern[baseh[i].cistcode].w*cistern[baseh[i].cistcode].d;
                    i++;
                }
                nexth = baseh[i].lvl;
                diff = nexth - lv;
                if ((ll)area*diff >= currv) {
                    //printf("lv=%d, baseh[i].lvl = %d\n", lv, baseh[i].lvl);
                    finalh = currv/(double)area;
                    double val = lv+finalh - 0.004;
                    val = ceil(val*100.0)/100.0;
                    printf("%.2lf\n", val);
                    currv = 0;
                    break;
                } else {
                    currv -= area*diff;
                    if (baseh[i].sgn == START)
                        area += cistern[baseh[i].cistcode].w*cistern[baseh[i].cistcode].d;
                    lv += diff;
                }
                //printf("%d sgn=%d\n",i, baseh[i].sgn);
                if (baseh[i].sgn == END) {
                    //dirskip = true;
                    area -= cistern[baseh[i].cistcode].w*cistern[baseh[i].cistcode].d;
                    //printf("%d insidearea\n", i);
                }
                i++;
                //printf("currv = %d, start down area = %d\n",currv, area);
            } else {
                if (lv != baseh[i].lvl) {
                //printf("lv=%d, baseh[i].lvl = %d\n", lv, baseh[i].lvl);
                    int nexth, diff;
                    nexth = baseh[i].lvl;
                    diff = nexth - lv;
                    if ((ll)area*diff >= currv) {
                        finalh = currv/(double)area;
                        double val = lv+finalh- 0.004;
                        val = ceil(val*100.0)/100.0;
                        printf("%.2lf\n", val);
                        currv = 0;
                        break;
                    } else {
                        currv -= area*diff;
                        lv += diff;
                        
                    }
                }
                //skipping same tops:
                while (baseh[i].sgn == END && baseh[i].lvl == lv) {
                    area -= cistern[baseh[i].cistcode].w*cistern[baseh[i].cistcode].d;
                    i++;
                }
            }
        }
    }
    return 0;
}

