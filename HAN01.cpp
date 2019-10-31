#include<cstdio>
#include<cstring>

#define START 1
#define TEMP 3
#define TARGET 2
#define ll long long int

int peg[4][70];
int pntr[4];

void solve(int n, ll k) {
    for (int i=0; i<4; i++) {
        memset(peg, 0, 70*sizeof(int));
        pntr[i] = 0;
    }
    
    int tstart, ttemp, ttarget, temp; //peg
    
    tstart = START;
    ttemp = TEMP;
    ttarget = TARGET;
    ll rstep = k;
    ll need;
    
    for (int i=n; i>=1; i--) {
        
        //try to move (i-1) piles to temp peg
        need = (1LL<<(i-1))-1;
        //printf("need = %lld\n", need);
        
        if (need == rstep) { //done
            peg[tstart][pntr[tstart]] = i;
            pntr[tstart]++;
            
            for (int j=i-1; j>=1; j--) {
                peg[ttemp][pntr[ttemp]] = j;
                pntr[ttemp]++;
            }
            break;
        } else if (need > rstep) { //n/a
            peg[tstart][pntr[tstart]++] = i;
            
            //swap peg
            temp = ttarget;
            ttarget = ttemp;
            ttemp = temp;
        } else { //loop more
            rstep -= need;
            
            //try to move base to target peg
            rstep --;
            
            if (rstep == 0) {
                peg[ttarget][pntr[ttarget]] = i;
                pntr[ttarget]++;
                
                for (int j=i-1; j>=1; j--) {
                    peg[ttemp][pntr[ttemp]] = j;
                    pntr[ttemp]++;
                }
                break;
            } else {
                peg[ttarget][pntr[ttarget]] = i;
                pntr[ttarget]++;
                
                //swap pegs
                temp = tstart;
                tstart = ttemp;
                ttemp = temp;
            }
        }
    }
}

int main() {
    int test, n; ll k;
    scanf("%d", &test);
    while (test--) {
        scanf("%d%lld", &n, &k);
        solve(n,k);
        
        for (int i=1; i<=3; i++) {
            printf("%d:", i);
            if (pntr[i] > 0) {
                printf(" %d", peg[i][0]);
                for (int j=1; j<pntr[i]; j++) {
                    printf("|%d", peg[i][j]);
                }
            }
            printf("\n");
        }
    }
    return 0;
}
