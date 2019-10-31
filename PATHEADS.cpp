#include<stdio.h>
#include<string.h>

#define MAXA 1000001
#define MAXN 100005

using namespace std;

int tally[MAXA];
int nas[MAXA];
int nums[MAXN];

void solve(int n, int max_a) {
    for (int i=1; i<=(max_a>>1); ++i) {
        if (nas[i]) {
            for (int j=(i+i); j<=max_a; j+=i) {
                if (tally[j] >= 0) tally[j] += nas[i];
            }
        }
    }
}

int main() {
    int n, a, max=-1;
    memset(tally, -1, sizeof(tally));
    
    scanf("%d", &n);
    for (int i=0; i<n; ++i) {
        scanf("%d", &nums[i]);
        ++tally[nums[i]];
        ++nas[nums[i]];
        if (nums[i] > max) max=nums[i];
    }
    solve(n,max);
    for (int j=0; j<n; ++j) {
        printf("%d\n", tally[nums[j]]);
    }
    return 0;
}