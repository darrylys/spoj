#include<stdio.h>
#include<algorithm>
#include<cctype>

#define MAXN 1000020

using namespace std;

char mstack[15];
int hg[MAXN];
int mark[MAXN];
int sum[MAXN];

int abs(int a) {
    if (a<0) return -a;
    else return a;
}

int getint() {
    char c;
    int n = 0;
    while (!isdigit(c=getchar()));
    while (isdigit(c)) {
        n = n*10 + c-'0';
        c=getchar();
    }
    return n;
}

void printint(int n) {
    if (n == 0) {
        putchar('0');
        return;
    }
    int p=0;
    while (n) {
        mstack[p++] = n%10;
        n/=10;
    }
    while (p--) {
        putchar(mstack[p]+'0');
    }
}

bool cmp(int a, int b) {
    return abs(a) < abs(b);
}

int main() {
    int testcase, n, d, x, h, ct, qry, u, v, c, res, id, smx;
    testcase = getint();
    
    while (testcase--) {
        
        n = getint();
        d = getint();
        
        hg[0] = 0;
        ct=1;
        for (int i=1; i<=n; ++i) {
            h = getint();
            if (h != hg[ct-1]) {
                hg[ct++] = h;
            }
        }
        hg[ct] = 0;
        sum[0] = 1;
        x = 1;
        mark[0] = 0;
        for (int i=1; i<ct; ++i) {
            if (hg[i] > hg[i-1] && hg[i] > hg[i+1]) {
                mark[x++] = -hg[i];
            } else if (hg[i] < hg[i-1] && hg[i] < hg[i+1]) {
                mark[x++] = hg[i];
            }
        }
        
        sort(mark+1, mark+x, cmp);
        
        for (int i=1; i<x; i++) {
            if (mark[i] > 0) {
                sum[i] = sum[i-1] + 1;
            } else {
                sum[i] = sum[i-1] - 1;
            }
        }
        //printf("%d\n", sum[0]);
        //for (int i=0; i<x; i++) printf("%d ", mark[i]);
        //putchar('\n');
        //for (int i=0; i<x; i++) printf("%d ", sum[i]);
        //putchar('\n');
        u = 0; v = x; id=-1;
        while (d--) {
            qry = getint();
            
            //u = 0; v = x;
            //res = -1;
            while (u < v) {
                c = (u+v)>>1;
                
                /*
                if (qry < abs(mark[c])) {
                    v = c;
                } else if (qry > abs(mark[c])) {
                    u = c+1;
                } else {
                    res = sum[c];
                    id = c;
                    break;
                }
                */
                if (qry < abs(mark[c])) {
                    v = c;
                } else {
                    u = c+1;
                }
            }
            //if (res == -1) {
            res = sum[u-1];
            id = u-1;
            //}
            
            printint(res);
            if (d) putchar(' ');
            
            u = id+1; v = x;
        }
        putchar('\n');
    }
    
    return 0;
}