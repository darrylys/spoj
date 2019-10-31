#include<cstdio>
#include<algorithm>

using namespace std;

bool cmp(int a, int b) {return a>b; }

int main() {
    int a[1010];
    int n, k, s, sum;
    scanf("%d%d%d",&n,&k,&s);
    for(int i=0;i<n;i++) scanf("%d",&a[i]);
    sort(a, a+n, cmp);
    sum=0;
    for (int i=0;i<n;i++) {
        sum+=a[i];
        if (sum >= k*s) {
            printf("%d\n", i+1);
            break;
        }
    }
    return 0;
}
