#include<cstdio>
#include<algorithm>

using namespace std;

int a[4005], b[4005], c[4005], d[4005];
int cd[16000005];
int muls[16000005];
int cf[16000005];

int main() {
    int n;
    scanf("%d", &n);
    for (int i=0; i<n; i++) {
        scanf("%d %d %d %d", &a[i], &b[i], &c[i], &d[i]);
    }
    //printf("1\n");
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            cd[i*n+j] = c[i]+d[j];
            //printf(" %d", cd[i*n+j]);
        }
    }
    //printf("ddn\n");
    sort(cd, cd+n*n);
    cd[n*n] = 1<<30;
    //printf("%d\n", cd[n*n]);
    int prev = cd[0];
    int start = 0, end = 1;
    int cntr = 0;
    for (int i=1; i<=n*n;i++) {
        if (prev == cd[i]) {
            end++;
            //printf("prev=%d, cd[%d]=%d, end=%d\n", prev, i, cd[i], end);
        } else {
            cf[cntr] = prev;
            muls[cntr] = end-start;
            cntr++;
            //printf("prev=%d, cd[%d]=%d, end=%d, muls[cntr]=%d, cf[cntr]=%d\n", prev, i, cd[i], end, muls[cntr-1], cf[cntr-1]);
            /*
            for (int j=start; j<end; j++) {
                muls[j] = end-start;
            }*/
            start = i;
            end = i+1;
            prev = cd[i];
        }
    }
    //printf("2\n");
    long long int sum = 0;
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            int key = -a[i]-b[j];
            //printf("key=%d\n", key);
            int u=0, v=cntr;
            
            while (true) {
                if (u >= v) {
                    break;
                } else {
                    int c = (u+v)>>1;
                    if (cf[c] == key) {
                        sum += muls[c];
                        break;
                    } else if (cf[c] > key) {
                        v = c;
                    } else {
                        u = c+1;
                    }
                }
            }
        }
    }
    printf("%lld\n", sum);
    return 0;
}