// segment tree based algorithm -> using divide&conquer. looking for a faster algo?
// this code is AC O(nlogn)

#include<stdio.h>

#define MAXN 300010
#define LOGN 20
#define ll long long
#define _max(a,b) ((a)>(b))?(a):(b)
#define _min(a,b) ((a)<(b))?(a):(b)
#define _abs(a) ((a)<0)?(-(a)):(a)
//#define DEBUG

int array[MAXN];
ll summaxa[MAXN];
ll summina[MAXN];
int maxa[LOGN][MAXN];
int mina[LOGN][MAXN];

#ifdef DEBUG
void pr(int lv, int n) {
    printf("MAXA\n");
    for (int i=0; i<=lv; ++i) {
        for (int j=0; j<n; ++j) {
            printf("%lld ", maxa[i][j]);
        }
        putchar('\n');
    }
    printf("MINA\n");
    for (int i=0; i<=lv; ++i) {
        for (int j=0; j<n; ++j) {
            printf("%lld ", mina[i][j]);
        }
        putchar('\n');
    }
}
#endif

//a,b -> [a,b]
ll solve(char side, int lv, int a, int b, int n) {
    if (a>=0 && b>=0 && a<n && b<n && a<=b) {
    
        if (b==a) {
            #ifdef DEBUG
            printf("same %d\n", a);
            #endif
            maxa[lv][a] = array[a];
            mina[lv][a] = array[a];
            
            return 0;
        } else if (b-a == 1) {
            if (side=='L') {
                maxa[lv][b] = array[b];
                maxa[lv][a] = _max(array[b], array[a]);
                mina[lv][b] = array[b];
                mina[lv][a] = _min(array[b], array[a]);
                
            } else if (side=='R') {
                maxa[lv][a] = array[a];
                maxa[lv][b] = _max(array[b], array[a]);
                mina[lv][a] = array[a];
                mina[lv][b] = _min(array[b], array[a]);
            
            }
            
            return _abs(array[a]-array[b]);
        } else {
            int mid = (a+b)>>1;
            ll leftsum = solve('L', lv+1, a, mid, n);
            ll rightsum = solve('R', lv+1, mid+1, b, n);
            
            #ifdef DEBUG
            printf("mid=%d\n", mid);
            #endif
            summaxa[a] = 0;
            summina[a] = 0;
            for (int i=a; i<=mid; ++i) {
                summaxa[i+1] = summaxa[i] + maxa[lv+1][i];
                summina[i+1] = summina[i] + mina[lv+1][i];
                #ifdef DEBUG
                printf("    x=%d, n=%d\n", summaxa[i+1], summina[i+1]);
                #endif
            }
            
            int l = mid+1;
            int r = mid;
            ll maxmidsum = 0;
            ll minmidsum = 0;
            #ifdef DEBUG
            printf("r=%d\n", r);
            #endif
            for (int px=mid+1; px<=b; ++px) {
                
                while (r>=a && maxa[lv+1][px] >= maxa[lv+1][r]) {
                    r--;
                }
                
                #ifdef DEBUG
                printf("--r=%d, mid-r=%d\n", r, mid-r);
                #endif
                
                maxmidsum += summaxa[r+1] + (ll)(mid-r)*maxa[lv+1][px];
            }
            
            r=mid;
            #ifdef DEBUG
            printf("r=%d\n", r);
            #endif
            for (int px=mid+1; px<=b; ++px) {
                
                while (r>=a && mina[lv+1][px] <= mina[lv+1][r]) {
                    r--;
                }
                
                #ifdef DEBUG
                printf("--r=%d, mid-r=%d\n", r, mid-r);
                #endif
                minmidsum += summina[r+1] + (ll)(mid-r)*mina[lv+1][px];
            }
            
            // array construction
            if (side=='L') {
                maxa[lv][b] = array[b];
                mina[lv][b] = array[b];
                for (int i=b-1; i>=a; --i) {
                    maxa[lv][i] = _max(maxa[lv][i+1], array[i]);
                    mina[lv][i] = _min(mina[lv][i+1], array[i]);
                }
            } else if (side=='R') {
                maxa[lv][a] = array[a];
                mina[lv][a] = array[a];
                for (int i=a+1; i<=b; ++i) {
                    maxa[lv][i] = _max(maxa[lv][i-1], array[i]);
                    mina[lv][i] = _min(mina[lv][i-1], array[i]);
                }
            }
            
            #ifdef DEBUG
            printf("ls=%d, rs=%d, mms=%d, mmins=%d\n", leftsum, rightsum, maxmidsum, minmidsum);
            #endif
            return leftsum + maxmidsum - minmidsum +rightsum;
        }
        
    } else {
        return 0;
    }
}

int getint() { //ok
    int s = 0;
    char c;
    while ((c=getchar())<'0' || c>'9');
    do {
        s = s*10 + c-'0';
    } while ((c=getchar())>='0'&&c<='9');
    return s;
}

int main() {
    int n = getint();
    #ifdef DEBUG
    printf("____n=%d\n", n);
    #endif
    for (int i=0; i<n; ++i) {
        array[i] = getint();
        #ifdef DEBUG
        printf("%d ", array[i]);
        #endif
    }
    #ifdef DEBUG
    putchar('\n');
    #endif
    
    printf("%lld\n", solve('M', 0, 0, n-1, n));
    #ifdef DEBUG
    pr(4, n);
    #endif
    
    return 0;
}

