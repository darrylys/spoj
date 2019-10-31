#include<stdio.h>
#include<string.h>
#include<algorithm>

using namespace std;

#define PI 3141
#define ll long long
#define N 1020
#define MLY (ll)(1e6)

typedef struct {
    int x, y;
    ll r2t1;
    ll r2t2;
    int covered;    //number of towers covering this point
} Point;

Point point[N];     //point data
int tower1[N];      //index to point
int tower2[N];      //index to point

int max(int a, int b) {return (a>b)?a:b;}
int min(int a, int b) {return (a<b)?a:b;}
ll llmin(ll a, ll b) {return (a<b)?a:b;}

int cmpa(const void* o1, const void* o2) {
    int a = *((int*) o1);
    int b = *((int*) o2);
    
    if (point[a].r2t1 < point[b].r2t1) return -1;
    else if (point[a].r2t1 > point[b].r2t1) return 1;
    else return 0;
}

int cmpd(const void* o1, const void* o2) {
    int a = *((int*) o1);
    int b = *((int*) o2);
    
    if (point[a].r2t2 < point[b].r2t2) return 1;
    else if (point[a].r2t2 > point[b].r2t2) return -1;
    else return 0;
}

int conv_to_int(char* str, int s, int e, bool after_comma) {
    if (str[s] != '-') {
        int r = 0;
        int mul = 1;
        for (int i=e; i>=s; i--) {
            r += (str[i]-'0')*mul;
            mul*=10;
        }
        if (after_comma) {
            if (e-s == 0) r *= 100;
            else if (e-s == 1) r *= 10;
        }
        return r;
    } else {
        return -conv_to_int(str+1, s, e-1, false);
    }
}

int conv(char* str) {
    int l = strlen(str);
    int fr = 0, bc = 0, i=0;
    for (; i<l; i++) {
        if (str[i] == '.') {
            fr = conv_to_int(str, 0, i-1, false);
            bc = conv_to_int(str, i+1, l-1, true);
            if (str[0] == '-') return fr*1000 - bc;
            else return fr*1000 + bc;
        }
    }
    return conv_to_int(str, 0, l-1, false) * 1000;
}

void printpoint(int n) {
    for (int i=0; i<n; i++) {
        printf("[x,y]=[%d,%d]\n", point[i].x, point[i].y);
        printf("area to first tower %lld\n", point[i].r2t1);
        printf("area to second tower %lld\n", point[i].r2t2);
        printf("covered = %d\n", point[i].covered);
    }
}

int main() {
    int n,x1,x2,y1,y2,lt,dx1,dx2,dy1,dy2,r1,r2,maxcovered,maxtemp,k=1, oldmax;
    char _x1[10], _x2[10], _y1[10], _y2[10], __lt[10], _x[10], _y[10];
    ll total_area, pir1, pir2;
    while (scanf("%d", &n) && n) {
        scanf("%s%s%s%s%s",_x1,_y1,_x2,_y2,__lt);
        x1 = conv(_x1);
        x2 = conv(_x2);
        y1 = conv(_y1);
        y2 = conv(_y2);
        lt = conv(__lt);
        total_area = ((ll)(1e6))*(ll)lt;
        for (int i=0; i<n; i++) {
            tower1[i] = i;
            tower2[i] = i;
            scanf("%s%s", _x, _y);
            point[i].x = conv(_x);
            point[i].y = conv(_y);
            point[i].covered = 0;
            dx1 = point[i].x - x1;
            dy1 = point[i].y - y1;
            dx2 = point[i].x - x2;
            dy2 = point[i].y - y2;
            point[i].r2t1 = PI*((ll)dx1*dx1 + (ll)dy1*dy1);
            point[i].r2t2 = PI*((ll)dx2*dx2 + (ll)dy2*dy2);
        }
        //printf("total_area = %lld\n", total_area);
        //printpoint(n);
        point[n].r2t2 = -1;
        point[n].r2t1 = 1LL<<62;
        qsort(tower1, n, sizeof(int), cmpa);
        qsort(tower2, n, sizeof(int), cmpd);
        
        tower1[n] = n;
        tower2[n] = n;
        
        pir1 = 0;
        pir2 = total_area;
        //printf("total area = %lld\n", total_area);
        maxcovered = 0;
        maxtemp = 0;
        oldmax = 0;
        
        //precompute
        int p1 = 0, p2 = 0, tp1, tp2;
        ll d1, d2, diff;
        for (int i=n-1; i>=0; i--) {
            int p = tower2[i];
            if (point[p].r2t2 <= pir2) {
                point[p].covered++;
                maxcovered++;
            } else {
                p2 = min(n-1, i+1); //closest to total_area
                break;
            }
        }
        
        for (int i=0; i<=n; i++) {
            int p = tower1[i];
            if (point[p].r2t1 <= pir1) {
                if (point[p].covered == 0) {
                    maxcovered++;
                }
                point[p].covered++;
            } else {
                p1 = max(0, i-1);
                break;
            }
        }
        
        oldmax = maxcovered;
        maxtemp = oldmax;
        tp1 = p1; tp2 = p2;
        //printf("f => p1=%d tp1=%d p2=%d tp2=%d\n", p1, tp1, p2, tp2);
        while (pir2 > 0 || pir1 < total_area) {
            //find smallest area diffrence tower 1
            for (tp1 = p1; tp1 <= n; tp1++) {
                int p = tower1[tp1];
                if (point[p].r2t1 > total_area) {
                    d1 = total_area - pir1;
                    break;
                }
                if (point[p].r2t1 > pir1) {
                    d1 = point[p].r2t1 - pir1;
                    break;
                }
            }
            
            //find smallest area diffrence tower 2
            for (tp2 = p2; tp2 <= n; tp2++) {
                int p = tower2[tp2];
                if (point[p].r2t2 == -1) {
                    d2 = pir2;
                    break;
                }
                if (point[p].r2t2 < pir2) {
                    d2 = pir2 - point[p].r2t2;
                    break;
                }
            }
            
            //find smaller diffrence
            diff = llmin(d1, d2);
            
            //contract tower2 area
            for (int i=p2; i<=n; i++) {
                int p = tower2[i];
                if (point[p].r2t2 <= pir2-diff) {
                    p2 = i;
                    break;
                }
                if (point[p].r2t2 <= pir2 && point[p].r2t2 > pir2-diff) {
                    if (point[p].covered == 1) {
                        maxtemp--;
                    }
                    if (point[p].covered >= 1) {
                        point[p].covered--;
                    }
                }
            }
            pir2 -= diff;
            
            //expand tower1 area
            for (int i=p1; i<=n; i++) {
                int p = tower1[i];
                if (point[p].r2t1 > pir1+diff) {
                    p1 = i;
                    break;
                }
                if (point[p].r2t1 > pir1 && point[p].r2t1 <= pir1 + diff) {
                    if (point[p].covered == 0) {
                        maxtemp++;
                    }
                    point[p].covered++;
                }
            }
            pir1 += diff;
            
            //update maxcovered
            if (maxtemp > maxcovered) maxcovered = maxtemp;
        }
        printf("%d. %d\n", k++, n - maxcovered);
    }
    return 0;
}

