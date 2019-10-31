// implementation: Brute Force + Mapping

#include<cstdio>
#include<set>
#define SEP 10000

using namespace std;

int abs(int a) {
    return (a>=0)?a:-a;
}

int enc(int a, int b) {
    return a*SEP + b;
}

int gcd(int a, int b) {
    if (b == 0) return a;
    else return gcd(b, a%b);
}

int main() {
    set<int> st;
    int x[202], y[202], dx, dy, co;
    int t;
    while (scanf("%d",&t) && t) {
        for (int i=0;i<t;i++) {
            scanf("%d %d",&x[i], &y[i]);
        }
        int ans = 0;
        for (int i=0;i<t;i++) {
            for (int j=i+1; j<t; j++) {
                dx =  x[j] - x[i];
                dy = y[j] - y[i];
                int div = gcd(abs(dx), abs(dy));
                if ((dx < 0 && dy < 0) || (dx > 0  && dy > 0)) {
                    co = enc(abs(dy)/div, abs(dx)/div);
                } else if (dx == 0 || dy == 0) {
                    co = enc(abs(dy)/div, abs(dx)/div);
                } else {
                    co = -enc(abs(dy)/div, abs(dx)/div);
                }
                if (st.find(co) == st.end() ) {
                    st.insert(co);
                    ans++;
                }
            }
        }
        st.clear();
        printf("%d\n", ans);
    }
    return 0;
}
