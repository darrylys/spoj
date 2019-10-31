#include<stdio.h>
#include<algorithm>
#include<vector>
#include<string.h>
#include<queue>

//#define DEBUG
#define SH 15

using namespace std;

vector<int> node[1010];
queue<int> _q;
int degree_in[1010];
int buf[2010];

int main() {
    int t, n, r, a, b, fi, top, c=1;
    scanf ("%d", &t);
    while (t--) {
        scanf("%d %d", &n, &r);
        memset(degree_in, 0, n*sizeof(degree_in[0]));
        
        for (int i=0; i<r; ++i) {
            scanf("%d %d", &a, &b);
            node[b].push_back(a);
            degree_in[a]++;
        }
        
        fi = 0;
        top = 0;
        for (int i=0; i<n; ++i) {
            if (degree_in[i] == 0) {
                _q.push((1<<SH) + i);
            }
        }
        
        while (_q.size()) {
            int rt = _q.front();
            _q.pop();
            #ifdef DEBUG
            printf("rt=%d\n", rt);
            #endif
            buf[fi++] = rt;
            int lv = rt>>SH;
            int idx = rt&((1<<SH)-1);
            #ifdef DEBUG
            printf("lv=%d, idx=%d\n", lv, idx);
            #endif
            for (int i=node[idx].size()-1; i>=0; --i) {
                degree_in[node[idx][i]]--;
                if (degree_in[node[idx][i]] == 0) {
                    _q.push(((lv+1)<<SH) + node[idx][i]);
                }
            }
        }
        
        sort(buf, buf+fi);
        printf("Scenario #%d:\n", c++);
        for (int i=0; i<fi; ++i) {
            printf("%d %d\n", buf[i]>>SH, buf[i]&((1<<SH)-1));
        }
        
        for (int i=0; i<n; ++i) {
            node[i].clear();
        }
    }
}