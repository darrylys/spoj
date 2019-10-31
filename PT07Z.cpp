#include<cstdio>
#include<vector>

#define max3(a,b,c) _max(a,_max(b,c))

using namespace std;

typedef struct {
    int parent;
    bool flag;
    int farleaf;
    int longest;
    vector<int> child;
} Node;

Node node[10005];
bool flag[10005];

int _max(int a, int b) {
    return (a>b)?a:b;
}

void dfs(int root, int parent) {
    if (!flag[root]) {
        flag[root] = true;
        node[root].parent = parent;
        int llol = node[root].child.size();
        for (int i=0; i<llol; i++) {
            dfs(node[root].child[i], root);
        }
    }
}

void solve(int root) {
    if (node[root].child.size() == 0) {
        node[root].farleaf = 0;
        node[root].longest = 0;
        flag[root] = true;
    } else if (!flag[root]){
        int lot = node[root].child.size();
        vector<int> chs = node[root].child;
        
        for (int i=0; i<lot; i++) {
            if (chs[i] != node[root].parent) solve(chs[i]);
        }
        
        int maxlong = -1;
        int max1 = -1, max2 = -1;
        int ml, m1, m2;
        //m1 = higher, m2 = lower
        for (int i=0; i<=lot/2; i++) {
            ml = -1; m1 = -1; m2 = -1;
            if (2*i < lot && chs[2*i] != node[root].parent) {
                ml = node[chs[2*i]].longest;
                m1 = node[chs[2*i]].farleaf;
                m2 = -1;
            }  
            if (2*i+1 < lot && chs[2*i+1] != node[root].parent) {
                if (ml < node[chs[2*i+1]].longest) {
                    ml = node[chs[2*i+1]].longest;
                }
                m2 = node[chs[2*i+1]].farleaf;
            }
            
            if (m1 < m2) {
                int tmp = m1;
                m1 = m2;
                m2 = tmp;
            }
            
            if (ml > maxlong) maxlong = ml;
            if (m2 > max1) {
                max1 = m1;
                max2 = m2;
            } else if (m1 >= max1) {
                max2 = max1;
                max1 = m1;
            } else if (m1 >= max2) {
                max2 = m1;
            }
        }
        
        node[root].farleaf = max1+1;
        node[root].longest = _max(max1+max2+2, maxlong);
        flag[root] = true;
    }
}

int main() {
    int n, a, b;
    scanf("%d", &n);
    
    for (int i=1; i<n; i++) {
        scanf("%d %d", &a, &b);
        node[a].child.push_back(b);
        node[b].child.push_back(a);
    }
    memset(flag, false, (n+1)*sizeof(bool));
    dfs(1,0);
    
    memset(flag, false, (n+1)*sizeof(bool));
    solve(1);
    
    printf("%d\n", _max(node[1].longest, node[1].farleaf));
    return 0;
}