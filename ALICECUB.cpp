#include<stdio.h>
#include<string.h>

#include<queue>

using namespace std;

const int GOAL = ((1<<8)-1)<<9;

int data[18][5] = {
    {0,0,0,0,-1},
    {2,3,5,9,-1},
    {4,6,10,-1},
    {4,7,11,-1},
    {8,12,-1},
    {6,7,13,-1},
    {8,14,-1},
    {8,15,-1},
    {16,-1},
    {10,11,13,-1},
    {12,14,-1},
    {12,15,-1},
    {16,-1},
    {14,15,-1},
    {16,-1},
    {16,-1},
    {-1}
};

int flag[(1<<16)+10];

bool check(int q, int i, int j) {
    bool ci = (q & (1<<i)) > 0;
    bool cj = (q & (1<<j)) > 0;
    
    return ci != cj;
}

int flip(int q, int i, int j) {
    return (q ^ ((1<<i) + (1<<j)));
}

void print_binary(int x) {
    if (x >0) {
        print_binary(x>>1);
        putchar((x&1) + '0');
    }
}

int bfs(int root) {
    queue<int> qs;
    int q, step, f;
    //print_binary(root);
    //printf("root = %d\n", root);
    qs.push(root);
    flag[root>>1] = 0;
    
    while (!qs.empty()) {
        q = qs.front(); qs.pop();
        if (flag[q>>1] == 3) {
            break;
        }
        for (int i=1; i<16; ++i) {
            
            for (int j=0, d=data[i][j]; data[i][j] != -1; ++j, d=data[i][j]) {
                
                if (check(q, i, d)) {
                    f = flip(q, i, d);
                    if (flag[f>>1] == 0) {
                        flag[f>>1] = flag[q>>1] + 1;
                        qs.push(f);
                    }
                }
            }
        }
    }
    return 4;
}



int main() {
    int t, d, cs = 0;
    scanf("%d", &t);
    int root = 0;
    bfs(GOAL);
    
    while (t--) {
        root = 0;
        for (int i=1; i<=16; ++i) {
            scanf("%d", &d);
            if (d) {
                root += (1<<i);
            }
        }
        
        if (root == GOAL) printf("Case #%d: 0\n", ++cs);
        else if (flag[root>>1] == 0) printf("Case #%d: more\n", ++cs);
        else printf("Case #%d: %d\n", ++cs, flag[root>>1]);
    }
    return 0;
}