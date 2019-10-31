#include<stdio.h>
#include<string.h>
#include<vector>

using namespace std;

#define N 20010
#define K 20
#define MOD 1000000007
#define ll long long

int C[K+1][K+1];
int parent[N];
int num_of_adj[N];
int suplist[N][K+1];
int stack[N];
bool flag[N];
int tempS[K+1];

typedef struct {
    vector<int> adj;
} Node;

int S[N][K+1];          //if node-x is root of SUBTREE, what is SUBtree-sum
int S2[N][K+1];         //if node-x is root of WHOLE TREE, what is WHOLEtree-sum

Node node[N];
    
//i => k, j => child index, root => root node index
int supersum(int i, int j, int* arr) {
    int r = 0;
    for (int l=0; l<=i; l++) {
        r = (r + (ll)C[i][l]*arr[l])%MOD;
    }
    return r;
}

// implement (a-b)%MOD
int subMod(int a, int b, int mod) {
    return (a-b < 0)? a-b+MOD: a-b;
}

void make_combinatorics() { //ok!
    C[0][0] = 1;
    for (int i=1; i<=K; i++) {
        C[i][0] = 1;
        for (int j=1; j<i; j++) {
            C[i][j] = C[i-1][j-1] + C[i-1][j];
        }
        C[i][i] = 1;
    }
}

void build_tree(int root, int k) { //ok!
    flag[root] = true;
    if (num_of_adj[root] == 1 && flag[node[root].adj[0]]) { //a leaf
        for (int i=0; i<=k; i++) {
            S[root][i] = 1;
        }
        parent[root] = node[root].adj[0];
    } else {
        for (int i=0; i<num_of_adj[root]; i++) {
            if (!flag[node[root].adj[i]]) {
                build_tree(node[root].adj[i], k);
            } else {
                parent[root] = node[root].adj[i];
            }
        }
        int sum = 1;
        int tempsum = 0;
        
        for (int i=0; i<=k; i++) {
            tempsum = 1;
            for (int j=0; j<num_of_adj[root]; j++) {
                if (node[root].adj[j] != parent[root]) {
                    sum = supersum(i,0, S[node[root].adj[j]]);
                    suplist[node[root].adj[j]][i] = sum;
                    tempsum = (tempsum + (ll)sum)%MOD;
                }
            }
            S[root][i] = tempsum;
        }
    }
}

//special for original root, don't use this routine
void solve_node(int root, int k) {
    for (int i=0; i<=k; i++) {
        tempS[i] = subMod(S2[parent[root]][i], suplist[root][i], MOD);
    }
    
    int r = 0;
    int sum = 0;
    for (int i=0; i<=k; i++) {
        sum = supersum(i, 0, tempS);
        S2[root][i] = (S[root][i] + sum)%MOD;
    }
}

void solve_all(int root, int k) {
    int top = 0;
    stack[top++] = root;
    int t;
    while (top) {
        t = stack[--top];
        for (int i=0; i<num_of_adj[t]; i++) {
            if (node[t].adj[i] != parent[t]) {
                solve_node(node[t].adj[i], k);
                stack[top++] = node[t].adj[i];
            }
        }
        //for all child of root, solve_node()
    }
}
/*
void display_tree(int root, int space, int k) { 
    if (num_of_adj[root] == 1 && parent[root] == node[root].adj[0]) {
        while (space--) putchar(' ');
        printf("%d => [", root);
        for (int i=0; i<=k; i++) {
            printf("%d | ", S[root][i]);
        }
        printf("]\n");
    } else {
        int sp = space;
        while (sp--) putchar(' ');
        printf("%d => [", root);
        for (int i=0; i<=k; i++) {
            printf("%d | ", S[root][i]);
        }
        printf("]\n");
        //while (space--) putchar(' ');
        for (int i=0; i<num_of_adj[root]; i++) {
            if (parent[root] != node[root].adj[i])
                display_tree(node[root].adj[i], space+2, k);
        }
    }
}
*/
int main() {
    make_combinatorics();
    int n, k, test, a, b;
    
    scanf("%d", &test);
    while (test--) {
        scanf("%d %d", &n, &k);
        memset(num_of_adj, 0, n*sizeof(int));
        memset(flag, false, n*sizeof(bool));
        
        for (int i=1; i<n; i++) {
            scanf("%d %d", &a, &b);
            node[a].adj.push_back(b);
            num_of_adj[a]++;
            
            node[b].adj.push_back(a);
            num_of_adj[b]++;
        }
        parent[0] = 0;
        build_tree(0, k);
        //display_tree(0, 0, k);
        
        for (int i=0; i<=k; i++) {
            S2[0][i] = S[0][i];
        }
        
        solve_all(0, k);
        
        for (int i=0; i<n; i++) {
            printf("%d\n", S2[i][k]);
        }
        putchar('\n');
        
        for (int i=0; i<n; i++) {
            node[i].adj.clear();
        }
    }
    return 0;
}

