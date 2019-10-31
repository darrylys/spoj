#include<stdio.h>

#define XMAX 1000005
#define ll long long int
//#define DEBUG

ll ldata[XMAX];
ll lstart[XMAX];

void build() {
    ldata[1] = 1;
    lstart[1] = 0;
    
    int lp = 1, abv;
    for (int i=2; i<XMAX; ++i) {
        abv = ldata[lp] - ldata[lp-1];
        lp += i>abv;
        ldata[i] = ldata[i-1] + i + lp-1;
        lstart[i] = lstart[i-1] + lp-1;
    }
}

int bsearch(ll* arr, int key, int len) {
    int u=1, v=len, c;
    while (u<v) {
        c = (u+v)>>1;
        if (key > arr[c] - arr[c-1]) {
            u = c+1;
        } else {
            v = c;
        }
    }
    return u-1;
}

inline ll max(ll a, ll b) {
    return (a>b) ? a:b;
}

inline ll min(ll a, ll b) {
    return (a<b) ? a:b;
}

int main() {
    build();
    
    int t, A1, A2, B1, B2, c=1;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d %d %d", &A1, &A2, &B1, &B2);
        
        #ifdef DEBUG
        printf("A1=%d, A2=%d, B1=%d, B2=%d\n", A1, A2, B1, B2);
        #endif
        // assume A = x axis, B = y axis
        
        // upper triangle
        ll uptrzeros;
        int toprow = bsearch(ldata, A1, XMAX);
        int bound_midrowright = bsearch(ldata, A2, XMAX);
        int bound_midrowleft = bsearch(lstart, A1, XMAX);
        int bound_bottom = bsearch(lstart, A2, XMAX);
        int bound_min = min(bound_midrowright, bound_midrowleft);
        int bound_max = max(bound_midrowright, bound_midrowleft);
        
        if (B1 > bound_min || B2 <= toprow) {
            uptrzeros = 0;
        } else {
            // triangle zeros from toprow+1 until B1 == minbounds or hit B2
            int mid = min(B2, bound_min);
            int newtop = max(B1-1, toprow);
            uptrzeros = ldata[mid] - ldata[newtop] - (ll)(A1-1)*(mid-newtop);
        }
        
        #ifdef DEBUG
        printf("toprow=%d, b_mright=%d, b_mleft=%d, b_bottom=%d, uptrzeros=%lld\n", toprow, bound_midrowright, bound_midrowleft, bound_bottom, uptrzeros);
        #endif
        
        // mid zone
        ll sanzuzero = 0, zerosquare = 0;
        if (bound_midrowright > bound_midrowleft) {
            //river
            if (B2 > bound_min && B1 <= bound_max) {
                int stzero = max(B1, bound_midrowleft+1);
                int endzero = min(B2, bound_midrowright);
                sanzuzero = (stzero + endzero) * (ll)(endzero - stzero + 1) / 2;
                
            } //else no such river
            
        } else if (bound_midrowright < bound_midrowleft) {
            //zeroblock
            if (B2 > bound_min && B1 <= bound_max) {
                int stzero = max(B1, bound_midrowright+1);
                int endzero = min(B2, bound_midrowleft);
                zerosquare = (A2 - A1 + 1) * (ll)(endzero - stzero + 1);
                
            } // else no such block
        }
        
        #ifdef DEBUG
        printf("river=%lld, zerosq=%lld\n", sanzuzero, zerosquare);
        #endif
        
        // lower triangle
        ll lwrtrzero=0;
        if (B2 > bound_max) {
            int start = max(B1, bound_max+1);
            int end = min(B2, bound_bottom);
            ll zerobox = 0;
            if (start <= end) {
                zerobox = (ll)(A2-A1+1)*(end-start+1);
                lwrtrzero = zerobox - (lstart[end] - lstart[start-1] - (ll)(A1-1)*(end-start+1));
            }
            #ifdef DEBUG
            printf("start=%d, end=%d, zerobox=%lld\n", start, end, zerobox);
            #endif
            
        }
        
        #ifdef DEBUG
        printf("lowertrianglezeros=%lld\n", lwrtrzero);
        #endif
        
        ll zeros = uptrzeros + sanzuzero + zerosquare + lwrtrzero;
        
        // calc total
        printf("Case #%d: %lld\n", c++, (ll)(A2-A1+1) * (B2-B1+1) - zeros);
        
        #ifdef DEBUG
        printf("\n==============================================\n");
        #endif
    }
    return 0;
}
