#include<stdio.h>
#include<vector>

using namespace std;

#define MAXN 100010

vector<int> student[MAXN];
int stack[MAXN];
char flag[MAXN];
int parent[MAXN];

void iterate(int n, int root, int mparentnode) {
    if (flag[root] == 1) return;
    
    int top = 0;
    stack[top++] = root;
    
    while (top) {
        int node = stack[--top];
        flag[node] = 1;
        
        parent[node] = mparentnode;
        
        for (int i=student[node].size()-1; i>=0; --i) {
            int child = student[node][i];
            if (!flag[child]) {
                stack[top++] = child;
            }
        }
    }
}

int main() {
    int n, m, q, a, b;
    scanf("%d %d", &n, &m);
    for (int i=0; i<m; ++i) {
        scanf("%d %d", &a, &b);
        student[a].push_back(b);
        student[b].push_back(a);
    }
    
    for (int i=0; i<n; ++i) {
        iterate(n, i, i);
    }
    
    scanf("%d", &q);
    while (q--) {
        scanf("%d %d", &a, &b);
        if (parent[a] == parent[b]) {
            printf("YES\n");
        } else {
            printf("NO\n");
        }
    }
    return 0;
}

