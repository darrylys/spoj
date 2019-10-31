#include<stdio.h>
#include<string.h>

#include<vector>
#include<algorithm>

using namespace std;

#define MAXN 100010

int stack[MAXN];
int index_node[MAXN];
int lowlink[MAXN];
bool flag[MAXN];

int owner_set[MAXN];

int idx;
int top;
int set_id;
int in_degree[MAXN];

vector<int> E[MAXN];
vector<int> S[MAXN];

int min(int a, int b) {
    return (a < b)? a: b;
}

int getint() {
    char c = getchar();
    int n=0;
    
    while (c < '0' || c > '9') c=getchar();
    while (c >= '0' && c <= '9') {
        n = n*10 + c-'0';
        c=  getchar();
    }
    return n;
}

void strong_connect(int v) {
    index_node[v] = idx;
    lowlink[v] = idx;
    ++idx;
    
    stack[top++] = v;
    flag[v] = true;
    
    for (int i=0; i<E[v].size(); ++i) {
        if (index_node[ E[v][i] ] == -1) {
            strong_connect(E[v][i]);
            lowlink[v] = min(lowlink[v], lowlink[E[v][i]]);
        } else if (flag[E[v][i]]) {
            lowlink[v] = min(lowlink[v], index_node[E[v][i]]);
        }
    }
    
    if (index_node[v] == lowlink[v]) {
        int topelem;
        
        do {
            topelem = stack[--top];
            flag[topelem] = false;
            //printf("%d ", topelem);
            owner_set[topelem] = set_id;
            S[set_id].push_back(topelem);
            
        } while (topelem != v);
        
        ++set_id;
        //putchar('\n');
    }
}

void run_tarjan(int n) {
    idx = 0;
    top = 0;
    set_id = 0;
    
    memset(index_node, -1, (n+1)*sizeof(int));
    //memset(flag, false, (n+1)*sizeof(bool));
    
    for (int i=1; i<=n; ++i) {
        if (index_node[i] == -1) {
            strong_connect(i);
        }
    }
}

int find_zero() {
    
    for (int i=0; i<set_id; ++i) {
        for (int j=0; j<S[i].size(); ++j) {
            for (int k=0; k<E[ S[i][j]].size(); ++k) {
                if (owner_set[E[S[i][j]][k]] != i) {
                    ++in_degree[ owner_set[E[S[i][j]][k]] ];
                }
            }
        }
    }
    
    int nz = -1;
    for (int i=0; i<set_id; ++i) {
        if (in_degree[i] == 0) {
            if (nz >= 0) return -1;
            else nz = i;
        }
    }
    return nz;
}

int main() {
    int n, a, b, m;
    n = getint(); m = getint();
    
    for (int i=0; i<m; ++i) {
        a = getint();
        b = getint();
        
        E[b].push_back(a);
    }
    
    run_tarjan(n);
    int zeros = find_zero();
    
    if (zeros != -1) {
        printf("%d\n", S[zeros].size());
        sort(S[zeros].begin(), S[zeros].end());
        
        for (int i=0; i < S[ zeros ].size(); ++i) {
            printf("%d ", S[zeros][i]);
        }
        putchar('\n');
    } else {
        printf("0\n");
    }
    return 0;
}