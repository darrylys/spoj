//using brute force + memoization, simple and effective

#include<cstdio>
#define NVT 0
#define VT -1
#define SAD -2

using namespace std;

int flag[900];
int carr[900];

int main() {
    int testcases, n, tmp, cntr, prevn, top, pntr;
    scanf("%d", &testcases);
    while (testcases--) {
        scanf("%d", &n);
        cntr = 0; pntr = 0;
        while (true) {
            tmp = 0;
            prevn = n;
            while (n>0) {
                tmp += (n%10)*(n%10);
                n/=10;
            }
            n=tmp;
            //printf("\tp%d n%d\n", prevn, n);
            cntr++;
            if (n == 1) {
                int xx = 1;
                pntr-=1;
                do {
                    top = carr[pntr--];
                    flag[top] = xx;
                    xx++;
                } while (pntr>=0);
                printf("%d,", cntr);
                break;
            } else if (flag[n] == NVT) {
                flag[n] = VT;
                carr[pntr++] = n;
            } else if (flag[n] == SAD || flag[n] == VT) {
                pntr--;
                do {
                    top = carr[pntr--];
                    flag[top] = SAD;
                } while (pntr>=0) ;
                printf("-1,");
                break;
            } else if (flag[n] > 0) {
                int xx = flag[n]+1;
                pntr--;
                while (pntr>=0) {
                    top = carr[pntr--];
                    flag[top] = xx;
                    xx++;
                }
                printf("%d,", flag[n]+cntr);
                break;
            }
        }
    }
}
