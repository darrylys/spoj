#include<stdio.h>
#include<vector>

#define MAX_NODE 100050
#define MOD 10007
//off=0, on=1 as usual

using namespace std;

int _min(int a, int b) {
    return (a<b)?a:b;
}

typedef struct {
    int minlamp[2];
    int combi[2];
    
    vector<int> child;
} Node;

Node node[MAX_NODE];

void work(int parent, int root) {
    //initial cond
    if (node[root].child.size() == 1 && node[root].child[0] == parent) {
        node[root].minlamp[0] = 0;
        node[root].minlamp[1] = 1;
        node[root].combi[0] = 1;
        node[root].combi[1] = 1;
        return;
    }
    
    // rec
    node[root].minlamp[0] = 0; 
    node[root].minlamp[1] = 1;
    node[root].combi[0] = node[root].combi[1] = 1;
    for (int i=node[root].child.size()-1; i>=0; --i) {
        if (node[root].child[i] == parent) continue;
        
        work(root, node[root].child[i]);
        
        //minlamps
        //OFF case
        node[root].minlamp[0] += node[ node[root].child[i] ].minlamp[1];
        
        //ON case
        int off = node[ node[root].child[i] ].minlamp[0];
        int on = node[ node[root].child[i] ].minlamp[1];
        node[root].minlamp[1] += _min(on, off);
        
        //conbis
        //oFF case
        node[root].combi[0] *= node[ node[root].child[i] ].combi[1];
        node[root].combi[0] %= MOD;
        
        //on case
        int coff = node[ node[root].child[i] ].combi[0];
        int con = node[ node[root].child[i] ].combi[1];
        if (off == on) {
            node[root].combi[1] *= (con+coff);
        } else if (on > off) {
            node[root].combi[1] *= coff;
        } else {
            node[root].combi[1] *= con;
        }
        node[root].combi[1] %= MOD;
    }
}

int main() {
    int t, n, a, b, c, v;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        int z = n;
        while (--n) {
            scanf("%d %d", &a, &b);
            
            node[a].child.push_back(b);
            node[b].child.push_back(a);
            
        }
        
        work(-1, 1);
        
        if (node[1].minlamp[0] == node[1].minlamp[1]) {
            c = node[1].minlamp[0];
            v = node[1].combi[0] + node[1].combi[1];
        } else if (node[1].minlamp[0] < node[1].minlamp[1]) {
            c = node[1].minlamp[0];
            v = node[1].combi[0];
        } else {
            c = node[1].minlamp[1];
            v = node[1].combi[1];
        }
        printf("%d %d\n", c, v%MOD);
        
        for (int i=0; i<z; ++i) {
            node[i+1].child.clear();
        }
    }
    return 0;
}