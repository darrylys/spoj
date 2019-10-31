#include<cstdio>
#include<cmath>
#define ll long long int
#define lfd long double

using namespace std;

int primes[80000];
bool flag[1000005];

int main() {
    int cntr = 1, i;
    primes[0]=2;
    flag[0] = flag[1] = true;
    for (i=3;i <= 1000; i+=2) {
        if (!flag[i]) {
            primes[cntr++] = i;
            for (int j=3*i; j<1000000; j+=2*i) {
                flag[j] = true;
            }
        }
    }
    for (; i<=1000000; i+=2) {
        if (!flag[i]) primes[cntr++] = i;
    }
    
    int c;
    ll n;
    scanf("%d",&c);
    while (c--) {
        scanf("%lld", &n);
        if (n == 0) {
            printf("Yes\n"); 
            continue;
        }
        int pntr = 0;
        ll temp = n;
        int count;
        bool fail = false;
        while (pntr < cntr && temp > 1) {
            if (primes[pntr] % 4 == 3) {
                count = 0;
                while ((temp%primes[pntr])==0) {
                    temp = temp / primes[pntr];
                    count++;
                }
                if (count % 2) {
                    fail = true;
                    break;
                }
            } else {
                while ((temp%primes[pntr])==0) {
                    temp = temp / primes[pntr];
                }
            }
            pntr++;
        }
        
        if (temp == n) {
            if (temp % 4 == 1) printf("Yes\n");
            else printf("No\n");
        } else {
            if (temp == 1) {
                if (fail) printf("No\n");
                else printf("Yes\n");
            } else {
                if (fail) printf("No\n");
                else {
                    if (temp % 4 == 3) printf("No\n");
                    else printf("Yes\n");
                }
            }
        }
    }
    return 0;
}
