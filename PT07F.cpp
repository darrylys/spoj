#include<stdio.h>
#include<string.h>
#include<vector>

#define N 10010
#define STOP 0         //stop here?
#define BRIDGE 1         //as a 'bridge'?
#define START 2       //start a new path?
#define MAXINT (1<<30)
#define min3(a,b,c) _min(a,_min(b,c))
#define L 1
#define R 2

using namespace std;

int dp[N][3];
int path[N][3][2];
bool flag[N];
int parent[N];
vector<int> child[N];
vector<int> way[N];
int ne;

int _min(int a, int b) {
    return (a<b)?a:b;
}

int abs(int a) {
    return (a<0)?-a:a;
}

void solve(int n) {
    //printf("n=%d, parent[n]=%d\n", n, parent[n]);
    if (child[n].size() == 1 && (parent[n] == child[n][0])) { //leaf
        dp[n][STOP] = 1;
        dp[n][BRIDGE] = 1;
        dp[n][START] = 1;
    } else {
        int size = child[n].size();
        //printf("size=%d\n", size);
        int dex[size], cntr = 0;
        for (int i=0; i<size; i++) {
            if (parent[n] != child[n][i]) {
                dex[cntr++] = i;
                parent[child[n][i]] = n;
                solve(child[n][i]);
            }
        }
        
        dp[n][START] = 1;
        int m, d;
        int arr[size];
        int first;
        bool f = true;
        for (int k=0; k<cntr; k++) {
            m = child[n][dex[k]];
            arr[dex[k]] = min3(dp[m][START], dp[m][STOP], dp[m][BRIDGE]);
            dp[n][START] += arr[dex[k]];
        }
        
        int min = MAXINT;
        int val, idmin;
        for (int i=0; i<cntr; i++) {
            m = child[n][dex[i]];
            val = dp[n][START]-1 - arr[dex[i]] + _min(dp[m][STOP], dp[m][START]);
            if (val < min) {
                min = val;
                idmin = dex[i];
            }
        }
        dp[n][STOP] = min;
        path[n][STOP][0] = idmin;
        
        int min1 = abs(arr[dex[0]]-_min(dp[child[n][dex[0]]][STOP],dp[child[n][dex[0]]][START]));
        int min2 = MAXINT;
        int id1=dex[0], id2=dex[0];
        //if (n==1) printf("min1=%d min2=%d\n", min1, min2);
        for (int i=1; i<cntr; i++) {
            m = child[n][dex[i]];
            d = abs(arr[dex[i]] - _min(dp[m][STOP],dp[m][START]));
            if (d < min1) {
                min2 = min1;
                min1 = d;
                id2 = id1;
                id1 = dex[i];
            } else if (d < min2) {
                min2 = d;
                id2 = dex[i];
            }
            //if (n==1) printf("min1=%d min2=%d\n", min1, min2);
        }
        if (size > 2) {
            int l = _min(dp[child[n][id1]][STOP],dp[child[n][id1]][START]);
            int r = _min(dp[child[n][id2]][STOP],dp[child[n][id2]][START]);
            dp[n][BRIDGE] = dp[n][START]-1-arr[id1]-arr[id2]+l-1+r;
            path[n][BRIDGE][0] = id1;
            path[n][BRIDGE][1] = id2;
            //printf("%d %d %d %d %d %d %d n=%d br=%d\n", dp[n][START], arr[id1], arr[id2], l, r, id1, id2, n, dp[n][BRIDGE]);
        } else {
            dp[n][BRIDGE] = dp[n][STOP];
            path[n][BRIDGE][0] = idmin;
            path[n][BRIDGE][1] = -1; //not used
        }
    }
}

int min_dx(int idx) {
    int m = MAXINT;
    int iid;
    for (int i=0; i<=2; i++) {
        if (dp[idx][i] < m) {
            m = dp[idx][i];
            iid = i;
        }
    }
    return iid;
}

int ststart(int idx) {
    if (dp[idx][START] < dp[idx][STOP]) return START;
    else return STOP;
}

void path_retrieval(int root, int dx, int dir, int mode) {
    //printf("ne=%d\n", ne);
    if (child[root].size() == 1 && (parent[root] == child[root][0])) {
        way[dx].push_back(root);
        return;
    }
    int sz = child[root].size(), m;
    if (mode == START) { //just 
        way[dx].push_back(root);
        for (int i=0; i<sz; i++) {
            m = child[root][i];
            if (parent[root] != m) {
                ne++;
                //printf("START => ne=%d\n", ne);
                path_retrieval(m, ne, R, min_dx(m));
            }
        }
    } else if (mode == BRIDGE) {
        if (path[root][BRIDGE][1] == -1) {
            //printf("BRIDGE1\n");
            if (dir == R) way[dx].push_back(root);
            path_retrieval(child[root][path[root][BRIDGE][0]], dx, dir, 
                ststart(child[root][path[root][BRIDGE][0]]));
            if (dir == L) way[dx].push_back(root);
            
            for (int i=0; i<sz; i++) {
                m = child[root][i];
                if (parent[root] != m && i != path[root][BRIDGE][0]) {
                    ne++;
                    //printf("BRIDGE_1 => ne=%d\n", ne);
                    path_retrieval(m, ne, R, min_dx(m));
                }
            }
            
        } else {
            //printf("BRIDGE2\n");
            path_retrieval(child[root][path[root][BRIDGE][0]], dx, L, ststart(child[root][path[root][BRIDGE][0]]));
            way[dx].push_back(root);
            path_retrieval(child[root][path[root][BRIDGE][1]], dx, R, ststart(child[root][path[root][BRIDGE][1]]));
            
            for (int i=0; i<sz; i++) {
                m = child[root][i];
                if (parent[root] != m && i != path[root][BRIDGE][0] && i != path[root][BRIDGE][1]) {
                    ne++;
                    //printf("BRIDGE_2 => ne=%d\n", ne);
                    path_retrieval(m, ne, R, min_dx(m));
                }
            }
        }
    } else { //STOP
        if (dir == R) way[dx].push_back(root);
        path_retrieval(child[root][path[root][STOP][0]], dx, dir, 
            ststart(child[root][path[root][STOP][0]]));
            
        if (dir == L) way[dx].push_back(root);
        
        for (int i=0; i<sz; i++) {
            m = child[root][i];
            if (parent[root] != m && i != path[root][STOP][0]) {
                ne++;
                //printf("STOP => ne=%d\n", ne);
                path_retrieval(m, ne, R, min_dx(m));
            }
        }
    }
}

void print_tree(int root, int space) {
    if (child[root].size() == 1 && (parent[root] == child[root][0])) {
        while (space--) putchar(' ');
        printf("[start, bridge, stop] => [%d ,%d, %d]\n", dp[root][START], dp[root][BRIDGE], dp[root][STOP]);
    } else {
        int sp = space;
        while (space--) putchar(' ');
        printf("[start, bridge, stop] => [%d ,%d, %d]\n", dp[root][START], dp[root][BRIDGE], dp[root][STOP]);
        for (int i=0; i<child[root].size(); i++) {
            if (parent[root] != child[root][i]) {
                print_tree(child[root][i], sp+4);
            }
        }
    }
}

int main() {
    parent[1] = 0;
    int t, n, a, b;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        child[1].push_back(0); //trick
        for (int i=1; i<n; i++) {
            scanf("%d %d", &a, &b);
            child[a].push_back(b);
            child[b].push_back(a);
        }
        solve(1);
        //print_tree(1, 0);
        int min = MAXINT;
        int id;
        for (int i=0; i<=2; i++) {
            if (dp[1][i] < min) {
                min = dp[1][i];
                id = i;
            }
        }
        ne = 0;
        path_retrieval(1, 0, R, id);
        printf("%d\n", min);
        int pth = min3(dp[1][START], dp[1][BRIDGE], dp[1][STOP]);
        
        for (int i=0; i<pth; i++) {
            int len = way[i].size();
            printf("%d", way[i][0]);
            for (int j=1; j<len; j++) {
                printf(" %d", way[i][j]);
            }
            putchar('\n');
            way[i].clear();
        }
        
        for (int i=1; i<=n; i++) {
            child[i].clear();
        }
        parent[1] = 0;
    }
    return 0;
}