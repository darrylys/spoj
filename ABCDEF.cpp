#include<cstdio>
#include<algorithm>

#define N 101
#define VAL 0
#define POLL 1
#define REP(i,a,b) for(int i=a; i<b; i++)

using namespace std;

int vals[N*N*N];
int cv[2][N*N*N];
int arr[N];

int main() {
    int n;
    scanf("%d", &n);
    REP(i,0,n) {
        scanf("%d", &arr[i]);
    }
    int c = 0;
    REP(d,0,n) {
        REP(e,0,n) {
            REP(f,0,n) {
                if (arr[d]) {
                    vals[c++] = arr[d]*(arr[e]+arr[f]);
                }
            }
        }
    }
    
    //printf("1-");
    
    sort(vals, vals+c);
    
    int prev = vals[0];
    int count = 1;
    int idx = 0;
    
    cv[VAL][idx] = prev;
    cv[VAL][N*N*N] = 2000000000;
    
    REP(i,1,N*N*N+1) {
        if (vals[i] == prev) {
            count++;
        } else {
            cv[POLL][idx] = count;
            idx++;
            count = 1;
            prev = vals[i];
            cv[VAL][idx] = prev;
        }
    }
    
    //printf("2-");
    long long int much = 0;
    REP(a,0,n) {
        REP(b,0,n) {
            REP(c,0,n) {
                int key = arr[a]*arr[b]+arr[c];
                int u = 0, v = idx;
                
                while (true) {
                    if (u >= v) { //not found
                        break;
                    } else {
                        int c = (u+v)/2;
                        if (key > cv[VAL][c]) {
                            u = c+1;
                        } else if (key < cv[VAL][c]) {
                            v = c;
                        } else { //found
                            much = much + cv[POLL][c];
                            break;
                        }
                    }
                }
            }
        }
    }
    //printf("3-");
    printf("%lld\n", much);
    return 0;
}
