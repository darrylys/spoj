#include<cstdio>
#include<algorithm>

using namespace std;
int a[1005], b[1005];

int main() {
    int t, n;
    scanf("%d",&t);
    while (t--) {
        scanf("%d", &n);
	    for (int i=0;i<n;i++) scanf("%d", &a[i]);
	    for (int i=0;i<n;i++) scanf("%d", &b[i]);
	    sort(a, a+n);
	    sort(b, b+n);
	    int sum = 0;
	    for (int i=0;i<n;i++) sum += a[i]*b[i];
	    printf("%d\n", sum);
    }
    return 0;
}
