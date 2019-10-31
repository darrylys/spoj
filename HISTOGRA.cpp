//impl Stack

#include<cstdio>
#include<stack>
#define ll long long int

using namespace std;

int main() {
    stack<int> h, index;
    int n, idx, tn, a, top, ti, hold;
    ll temp, max;
    while (scanf("%d",&n) && n) {
        h.push(-1); index.push(-1);
        max = -1;
        tn = n;
        idx = 0;
        while (tn--) {
            scanf("%d",&a);
            top = h.top();
            if (a > top) {
                h.push(a);
                index.push(idx);
            } else if (a < top) {
                do {
                    top = h.top();
                    ti = index.top();
                    if (top == a) break;
                    else if (top < a) {
                        h.push(a);
                        index.push(hold);
                        break;
                    }
                    temp = (idx-ti)*(ll)top;
                    if (temp > max) max = temp;
                    hold = ti;
                    h.pop(); index.pop();
                } while (1);
            }
            idx++;
        }
        a = -1;
        do {
            top = h.top();
            ti = index.top();
            if (top == a) break;
            else if (top < a) {
                h.push(a);
                index.push(hold);
                break;
            }
            temp = (idx-ti)*(ll)top;
            if (temp > max) max = temp;
            hold = ti;
            h.pop(); index.pop();
        } while (1);
        printf("%lld\n", max);
        while (!h.empty())h.pop();
        while (!index.empty())index.pop();
    }
}
