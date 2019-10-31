#include<stdio.h>
#include<queue>
#include<string.h>

using namespace std;

typedef struct {
    char digit;
    int parent;
} NODE;

NODE node[10005];
queue<int> dq;

// dgbuf MUST be sorted (increasing)
int fillK(int* dgbuf, int ndigit, int N) {

    for (int i=0; i<ndigit; ++i) {
        if (dgbuf[i]) {
            if (dgbuf[i] % N) {
                int c = dgbuf[i]%N;
                
                if (node[c].parent == -1) {
                    dq.push(c);
                    node[c].parent = 0;
                    node[c].digit = dgbuf[i];
                }
            } else {
                int c = dgbuf[i]%N;
                
                node[c].parent = 0;
                node[c].digit = dgbuf[i];
                return c;
            }
        }
    }
    
    while (!dq.empty()) {
        
        int te = dq.front();
        dq.pop();
        
        if (te == 0) {
            return te;
        }
        
        for (int i=0, ch; i<ndigit; ++i) {
            ch = (te*10 + dgbuf[i])%N;
            if (node[ch].parent == -1) {
                node[ch].parent = te;
                node[ch].digit = dgbuf[i];
                dq.push(ch);
            }
        }
        
    }
    return -1;
}

void cprint(int r) {
    if (node[r].parent) {
        cprint(node[r].parent);
    }
    putchar(node[r].digit+'0');
}

int main() {
    int N, m, c=1;
    int dgbuf[10];
    char flagdg[10];
    
    while (scanf("%d %d", &N, &m) != -1) {
        for (int i=0; i<10; ++i) {
            flagdg[i] = (char)1;
        }
        
        for (int i=0; i<=10000; ++i) {
            node[i].parent = -1;
        }
        
        for (int i=0, te; i<m; ++i) {
            scanf("%d", &te);
            flagdg[te] = (char)0;
        }
        
        int f = 0;
        for (int i=0; i<10; ++i) {
            if (flagdg[i]) {
                dgbuf[f++] = i;
            }
        }
        
        int r = fillK(dgbuf, f, N);
        if (r == -1) printf("Case %d: -1\n", c++);
        else {
            printf("Case %d: ", c++);
            cprint(r);
            putchar('\n');
        }
        
        while (!dq.empty()) dq.pop();
    }
    return 0;
}
