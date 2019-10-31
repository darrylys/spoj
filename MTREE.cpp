#include<stdio.h>
#include<vector>

#define MOD 1000000007
#define MAXN 100010
#define ll long long

using namespace std;

int safe_minus(int a, int b) {
    a -= b;
    if (a < 0) a += MOD;
    return a;
}

vector<int> E[MAXN]; //shows target
vector<int> W[MAXN]; //the weight
int exc_path[MAXN];
int end_here[MAXN];
int bridge[MAXN];

void solve(int root, int parent) {
    if (E[root].size() == 1 && E[root][0] == parent) { //a leaf
        exc_path[root] = 0;
        end_here[root] = 0;
        bridge[root] = 0;
    } else {
        int size = E[root].size();
        int dex[size], cntr = 0;
        
        for (int i=0; i<size; i++) {
            if (E[root][i] != parent) {
                dex[cntr++] = i;
                solve(E[root][i], root);
            }
        }
        
        end_here[root] = 0;
        for (int i=0; i<cntr; i++) {
            end_here[root] = (int)((end_here[root] + ((end_here[E[root][dex[i]]]+1)
                *((ll)W[root][dex[i]]))%MOD)%MOD);
        }
        
        int sum[cntr+1];
        sum[0] = 0;
        for (int i=1; i<=cntr; i++) {
            sum[i] = (int)((sum[i-1] + ( (end_here[E[root][dex[i-1]]] + 1) *
                ((ll)W[root][dex[i-1]]))%MOD)%MOD);
        }
        
        bridge[root] = 0;
        for (int k=1, i; k<cntr; k++) {
            i=dex[k-1];
            //bridge[root] = (int)(bridge[root] + 
            int d = (int)(((( W[root][i] * (ll)(end_here[ E[root][i] ] + 1) )%MOD) * (ll)safe_minus(sum[cntr], sum[k]))%MOD);
            bridge[root] = (int)(bridge[root] + d)%MOD;
        }
        
        exc_path[root] = 0;
        for (int k=0, i; k<cntr; k++) {
            i=dex[k];
            exc_path[root] = (int)(( (ll)exc_path[root] + bridge[E[root][i]] + 
                end_here[E[root][i]] + exc_path[E[root][i]] )%MOD);
        }
    }
}

void print_tree(int root, int parent, int space) {
    if (E[root].size() == 1 && E[root][0] == parent) {
        while (space--) putchar(' ');
        printf("[exclusives, end_here, bridges] => [%d, %d, %d]\n", 
            exc_path[root], end_here[root], bridge[root]);
    } else {
        int sp = space;
        while (space--) putchar(' ');
        printf("[exclusives, end_here, bridges] => [%d, %d, %d]\n", 
            exc_path[root], end_here[root], bridge[root]);
        
        for (int i=0; i<E[root].size(); ++i) {
            if (parent != E[root][i]) {
                print_tree(E[root][i], root, sp+4);
            }
        }
    }
}

int main() {
    int n, a,b, w;
    scanf("%d", &n);
    for (int i=1; i<n; ++i) {
        scanf("%d %d %d", &a, &b, &w);
        E[a].push_back(b);
        W[a].push_back(w);
        
        E[b].push_back(a);
        W[b].push_back(w);
    }
    solve(1, 0);
    
    //print_tree(1, 0, 0);
    
    printf("%d\n", ( (exc_path[1] + end_here[1])%MOD + bridge[1])%MOD );
    return 0;
}