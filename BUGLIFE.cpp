#include<cstdio>
#include<queue>
#include<vector>
#include<cstring>

#define AA (int)1
#define BB (int)-1
#define UU (int)0

#define N_NODE 2005

using namespace std;

typedef struct {
    int child[N_NODE];
} Node;

int much[N_NODE];
int type[N_NODE];
Node node[N_NODE];

bool make_color(int root, int color) {
    queue<int> q;
    queue<int> ccols;
    
    q.push(root);
    ccols.push(color);
    int currentcolor, now;
    
    while (!(q.empty())) {
        now = q.front();
        currentcolor = ccols.front();
        q.pop(); ccols.pop();
        
        if (type[now] == UU) {
            type[now] = currentcolor;
            int* ch = node[now].child;
            
            int size = much[now];
            for (int i=0; i<size; i++) {
                int next = ch[i];
                if (type[next] == UU) {
                    q.push(ch[i]);
                    ccols.push(-currentcolor);
                } else if (type[next] != -currentcolor) {
                    return false;
                }
            }
        } else if (type[now] != currentcolor) {
            return false;
        } 
    }
    return true;
}

void clear(int n) {
    memset(much, 0, (n+1)*sizeof(int));
    memset(type, UU, (n+1)*sizeof(int));
}

int main() {
    int test, bugs, intrs, a, b, scec = 1;
    bool cont;
    scanf("%d", &test);
    while (test--) {
        scanf("%d %d", &bugs, &intrs);
        clear(bugs);
        for (int i=0; i<intrs; i++) {
            scanf("%d %d", &a, &b);
            node[a].child[much[a]] = b;
            node[b].child[much[b]] = a;
            much[a]++; much[b]++;
        }
        
        cont = true;
        for (int i=1; i<=bugs && cont; i++) {
            if (type[i] == UU) {
                cont = cont && make_color(i, AA);
            }
            //printf("i=%d cont=%d\n", i, cont);
        }
        printf("Scenario #%d:\n", scec++);
        if (cont) {
            printf("No suspicious bugs found!\n");
        } else {
            printf("Suspicious bugs found!\n");
        }
        
        
    }
    return 0;
}
