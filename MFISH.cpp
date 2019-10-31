#include <stdio.h>
#include <algorithm>
#include <string.h>

#define MAXN 100005

using namespace std;

typedef struct {
    int anchor;
    int length;
} Ship;

bool shipCmp(Ship a, Ship b) {
    return a.anchor < b.anchor;
}

Ship ship[MAXN];
int data[MAXN];
int sum[MAXN]; //-> NOTE: sum[n] = data[0]+data[1]+...+data[n-1]
int dp[MAXN];
int shipsPlaced[MAXN];

//sum of data[a]+data[a+1]+...+data[b]
int sumRange(int a, int b) {
    return sum[b+1] - sum[a];
}

int _max(int a, int b) {
    return (a > b) ? a : b;
}

int _min(int a, int b) {
    return (a < b) ? a : b;
}

int getDP(int id) {
    if (id < 0) return 0;
    else return dp[id];
}

int main() {
    int n;
    scanf("%d", &n);
    sum[1] = 0;
    
    for (int i=1; i<=n; ++i) {
        scanf("%d", &data[i]);
        sum[i+1] = data[i] + sum[i];
    }
    
    int m;
    scanf("%d", &m);
    
    for (int i=0; i<m; ++i) {
        scanf("%d %d", &ship[i].anchor, &ship[i].length);
    }
    
    sort(ship, ship+m, shipCmp);
    
    //memset(dp, -1, sizeof(dp));
    
    dp[0] = 0;
    shipsPlaced[0] = 0;
    int lastMax = 0;
    for (int i=0, prev; i<m; ++i) {
        //printf("%d %d\n", ship[i].anchor, ship[i].length);
        
        if (i) {
            prev = ship[i-1].anchor + ship[i-1].length;
        } else {
            prev = 1;
        }
        
        for (int j=prev; j<ship[i].anchor; ++j) {
            dp[j] = lastMax;
            shipsPlaced[j] = shipsPlaced[j-1];
        }
        
        lastMax = -1;
        for (int j=0, piv; j<ship[i].length; ++j) {
            piv = ship[i].anchor;
            if(piv+j <= n) {
                int idx = (piv-ship[i].length+j < 0) ? 0 : piv-ship[i].length+j;
                //printf("idx=%d, piv=%d, len=%d, j=%d\n", idx, piv, ship[i].length, j);
                if (shipsPlaced[idx] == i) {
                    dp[piv+j] = _max(lastMax, getDP(piv-ship[i].length+j) + 
                        sumRange( _max(piv-ship[i].length+j+1, 1), _min(piv+j, n)));
                    lastMax = _max(lastMax, dp[piv+j]);
                    shipsPlaced[piv+j] = i+1;
                }
            } else {
                break;
            }
        }
    }
    
    //for (int i=0; i<=n; ++i) printf("%d ", dp[i]);
    //putchar('\n');
    
    //for (int i=0; i<=n; ++i) printf("%d ", shipsPlaced[i]);
    //putchar('\n');
    
    printf("%d\n", lastMax);
    
    return 0;
}