#include<stdio.h>
#include<string.h>
#define MXN 1<<20

char vN[MXN];
char dFlag[50];

void printbinary(int x) {
    if (x) {
        printbinary(x>>1);
        putchar((x&1) + '0');
    }
}

void build() {
    for (int i=0; i<(MXN); ++i) {
        if (i == (i&(-i))) {
            vN[i] = 0;
        } else {
            int v = i;
            
            memset(dFlag, 0, sizeof(dFlag));
            //for (int xx=0; xx<25; xx++) dFlag[xx]=0;
            
            int r1 = 1;
            int r3 = 3;
            
            while (r1 <= v) {
                int e1 = v&(~r1);
                int e3 = v&(~r3);
                
                if (e1 < v) {
                    dFlag[vN[e1]] = 1;
                    
                    if (e3 < e1) {
                        dFlag[vN[e3]] = 1;
                    }
                    
                }
                
                r1<<=1;
                r3<<=1;
            }
            
            int x=0;
            while (dFlag[x]) ++x;
            vN[i] = x;
        }
        
        //printf("%d: %d\n", i, vN[i]);
    }
}

int main() {
    build();
    
    int t, N;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &N);
        printf("%s\n", (vN[N]) ? "Alice" : "Bob");
    }
}
