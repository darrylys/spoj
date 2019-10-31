#include<cstdio>
#include<algorithm>

#define N 20005
#define MAXINT 2000000000

using namespace std;

int arr[N];

int main() {
    int test, n, k;
    scanf("%d", &test);
    while (test--) {
        scanf("%d %d", &n, &k);
        for (int i=0; i<n; i++) {
            scanf("%d", &arr[i]);
        }
        
        sort(arr, arr+n);
        
        int min = MAXINT;
        
        for (int i=0; i+k<=n; i++) {
            if (arr[i+k-1] - arr[i] < min) {
                min = arr[i+k-1] - arr[i];
            }
        }
        
        printf("%d\n", min);
    }
    return 0;
}