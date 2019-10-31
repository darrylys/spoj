#include<cstdio>
#include<cstring>
#include<vector>

using namespace std;

typedef struct {
    vector<int> child;
    int parent;
    int rest;
} Node;

bool flag[100010];
bool mark_vc[100010];
Node node[100010];
int stack[100010];

int vertex_cover(int n) {
    memset(flag, false, (n+1)*sizeof(bool));
    memset(mark_vc, false, (n+1)*sizeof(bool));
    node[1].parent = 0;
    mark_vc[0] = true;
    int vc = 0;
    int top = 0;
    int checked = 0;
    stack[top++] = 1;
    while (checked < n && top > 0) {
        int topelem = stack[top-1];
        flag[topelem] = true;
        
        //input children
        if (node[topelem].rest > 0) {
            while (node[topelem].rest--) {
                int now = node[topelem].child[node[topelem].rest];
                if (!flag[now]) {
                    stack[top++] = now;
                    node[now].parent = topelem;
                    flag[now] = true;
                }
            }
        } else {
            if (!mark_vc[topelem] && !mark_vc[node[topelem].parent]) {
                mark_vc[node[topelem].parent] = true;
                mark_vc[topelem] = true;
                vc++;
            }
            top--;
            checked++;
        }
        
    }
    return vc;
}

int main() {
    int n;
    scanf("%d", &n);
    int u, v;
    for (int i=1; i<n; i++) {
        scanf("%d %d", &u, &v);
        node[u].child.push_back(v);
        node[v].child.push_back(u);
        //node[v].parent = u;
    }
    for (int i=1; i<=n; i++) {
        node[i].rest = node[i].child.size();
    }
    printf("%d\n", vertex_cover(n));
    return 0;
}
