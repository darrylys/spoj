#include<stdio.h>
#include<queue>
#include<algorithm>

#define MAXN 20010

using namespace std;

int inbox[MAXN];

int main() {
    int t, n, v, h, m, s, I, fset, cas=1;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i=0; i<n; ++i) {
            scanf("%d:%d:%d", &h, &m, &s);
            inbox[i] = h*3600 + m*60 + s;
        }
        sort(inbox, inbox+n);
        
        scanf("%d", &I);
        
        queue<int> _q;
        fset = 0;
        if (n) {
            fset = 1;
            _q.push(inbox[0] + I);
        }
        for (int i=1; i<n; ++i) {
            int fr = _q.front();
            if (inbox[i] < fr) {
                fset++;
            } else {
                _q.pop();
            }
            _q.push(inbox[i]+I);
        }
        printf("Case %d: %d\n", cas++, fset);
    }
    return 0;
}