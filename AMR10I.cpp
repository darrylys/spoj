#include<stdio.h>
#include<set>

#define ull unsigned long long

using namespace std;

set<int> dset;
char pn[21] = {1,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71};

void getRemain(int N, int P, int currMidVal, int startFrom) {
    if (N < 0) {
        return;
    }
    
    if (N == 0) {
        dset.insert(currMidVal);
        return;
    }
    
    for (int i=startFrom; pn[i] <= N; ++i) {
        getRemain(N-pn[i], P, (int)(((ull)currMidVal * pn[i])%P), i);
    }
    
    return;
}

int main() {
    int t, N, P;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %d", &N, &P);
        dset.clear();
        getRemain(N, P, 1, 0);
        printf("%d\n", dset.size());
    }
    
}
