#include<stdio.h>
#include<string.h>

#define N 810
#define SL 801

int full[N];
int slantUp[N];
int slantBoth[N];
int sameSide[N];
bool flag[N];

int sieve() {
    for (int j=0; ; j++) {
        if (!flag[j]) {
            return j;
        }
    }
}

void solve() {
    
    full[0] = full[1] = 0;
    slantUp[0] = slantUp[1] = 0;
    slantBoth[0] = slantBoth[1] =0;
    sameSide[0] = sameSide[1] = 0;
    
    for (int i=2; i<SL; i++) {
        memset(flag, false, N*sizeof(bool));
        //full
        //_|
        for (int j=1; j<i; j++) {
            flag[slantUp[j] ^ full[i-j-1]] = true;
        }
        full[i] = sieve();
        
        memset(flag, false, N*sizeof(bool));
        //slantUp
        //_|
        for (int j=1; j<i; j++) {
            flag[slantBoth[j] ^ full[i-j-1]] = true;
        }
        for (int j=2; j<i; j++) {
            // _
            //|
            flag[slantUp[j-1] ^ slantUp[i-j]] = true;
            
            //|_
            flag[sameSide[j] ^ full[i-j-1]] = true;
        }
        slantUp[i] = sieve();
        
        memset(flag, false, N*sizeof(bool));
        //sameSide
        for (int j=2; j<i; j++) {
            //_|
            flag[slantBoth[j-1] ^ slantUp[i-j]] = true;
        }
        for (int j=3; j<i; j++) {
            //L
            flag[sameSide[j-1] ^ slantUp[i-j]] = true;
        }
        sameSide[i] = sieve();
        
        memset(flag, false, N*sizeof(bool));
        //slantBoth
        //_|
        for (int j=2; j<i; j++) {
            flag[slantBoth[j-1] ^ slantUp[i-j]] = true;
        }
        //|_
        for (int j=3; j<i; j++) {
            flag[sameSide[j-1] ^ slantUp[i-j]] = true;
        }
        slantBoth[i] = sieve();
    }
    
}

int main() {
    int n, f;
    scanf("%d", &n);
    solve();
    while (n--) {
        scanf("%d", &f);
        printf("%s\n", (full[f])?"X":"Y");
    }
    return 0;
}