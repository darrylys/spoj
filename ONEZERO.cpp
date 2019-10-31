#include<cstdio>
#include<queue>

using namespace std;

#define ll unsigned long long int
#define FOR(i,a,b) for(int i=a; i<b; i++)
#define REP(i,n) FOR(i,0,n)

void print(ll num) {
    if (num > 0) {
        print(num/2);
        printf("%d", num%2);
    }
}

int main() {
    int k, n;
    queue<int> num;
    queue<ll> bs;
    bool flag[20010];
    ll binstr;
    scanf("%d", &k);
    while (k--) {
        scanf("%d", &n);
        memset(flag, false, n*sizeof(bool));
        if (n==1) {
            binstr = 1;
        } else {
            //printf("testcase %d:\n", k);
            num.push(1);
            bs.push(1);
            flag[1] = true;
            while (!num.empty()) {
                int f = num.front();
                num.pop();
                ll str = bs.front();
                bs.pop();
                //printf("f= %d, str=%llu\n", f, str);
                if ((f*10)%n == 0) {
                    binstr = str<<1;
                    break;
                } else {
                    if (!flag[(f*10)%n]) {
                        num.push((f*10)%n);
                        bs.push(str<<1);
                        flag[(f*10)%n] = true;
                    }
                }
                if ((f*10+1)%n == 0) {
                    binstr = (str<<1) + 1;
                    break;
                } else {
                    if (!flag[(f*10+1)%n]) {
                        num.push((f*10+1)%n);
                        bs.push((str<<1)+1);
                        flag[(f*10+1)%n] = true;
                    }
                }
            }
        }
        //printf("%llu\n", binstr);
        while (!num.empty()) num.pop();
        while (!bs.empty()) bs.pop();
        print(binstr);
        putchar('\n');
    }
    return 0;
}