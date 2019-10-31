#include<stdio.h>
#include<vector>

#define N 10005

using namespace std;

int total_volume;
int width[N];
vector<int> tree[N]; 

void solve(int root, int parent) {
    //printf("root=%d, parent=%d\n", root, parent);
    if (tree[root].size() == 1 && tree[root][0] == parent) {
        width[root] = 1;
    } else {
        int size = tree[root].size();
        int cntr = 0;
        for (int i=0; i<size; i++) {
            if (tree[root][i] != parent) {
                solve(tree[root][i], root);
                cntr++;
            }
        }
        
        width[root] = cntr+1;
        for (int i=0; i<size; i++) {
            if (tree[root][i] != parent) {
                width[root] += width[tree[root][i]];
            }
        }
    }
    total_volume += width[root];
}

int main() {
    int test, n, a, b;
    scanf("%d", &test);
    
    while (test--) {
        scanf("%d", &n);
        tree[0].push_back(-1);
        
        for (int i=1; i<n; i++) {
            scanf("%d %d", &a, &b);
            
            tree[a].push_back(b);
            tree[b].push_back(a);
        }
        total_volume = 0;
        solve(0, -1);
        printf("%d\n", total_volume);
        
        for (int i=0; i<n; i++) {
            tree[i].clear();
        }
    }
    return 0;
}