#include<stdio.h>
#include<string.h>

enum {
    SHORT=1, LONG_S, LONG_M, LONG_E
} _sth;

bool conflict[130];
char str[50];
char field[1024][10];
int dp[1024][130];
int scoreboard[130];
int cfs[130];

void fill_scoreboard() {
    for (int i=0, d; i<128; ++i) {
        scoreboard[i] = 0;
        d = i;
        
        while (d > 0) {
            scoreboard[i] += d&1;
            d >>= 1;
        }
    }
}

void init() {
    memset(conflict, false, sizeof (conflict));
    memset(field, (char)0, sizeof (field));
}

void close_conflict(int k) {
    
    for (int i=0; i<k; ++i) {
        //conflict[cfs[i]] = true;
        
        for (int j=cfs[i]; j<128; ++j) {
            if ((j & cfs[i]) == cfs[i]) {
                conflict[j] = true;
            }
        }
    }
}

void parse(int len, int key) {
    //printf("len=%d\n", len);
    int a, b, st = 0;
    bool isl = false;
    
    a = 0;
    for (int i=0; i<len; ++i) {
        
        if (str[i] == '-') {
            st = i+1;
            isl = true;
            break;
        } else {
            a = a*10 + str[i]-'0';
        }
    }
    
    if (!isl) {
        field[a][key] = SHORT;
    } else {
        b=0;
        for (int i=st; i<len; ++i) {
            b = b*10 + str[i]-'0';
        }
        
        field[a][key] = LONG_S;
        for (int i=a+1; i<b; ++i) {
            field[i][key] = LONG_M;
        }
        
        field[b][key] = LONG_E;
    }
}

void printfield(int n) {
    for (int b=0; b<7; ++b) {
        for (int i=0; i<=n; ++i) {
            printf("%c ", field[i][b]+'0');
        }
        putchar('\n');
    }
}

int main() {
    int t, n, m, k, s, c=0, p;
    fill_scoreboard();
    
    scanf("%d", &t);
    
    while (t--) {
        init();
        scanf("%d", &n);
        
        for (int i=0; i<7; ++i) {
            scanf("%d", &m);
            
            while (m--) {
                scanf("%s", str);
                parse(strlen(str), i);
            }
        }
        
        //printfield(n);
        
        scanf("%d", &k);
        
        p = 0;
        while (k--) {
            s = 0; m=1;
            scanf("%s", str);
            for (int i=6; i>=0; --i) {
                s += (str[i]-'0')*m;
                m <<= 1;
            }
            
            cfs[p++] = s;
            //conflict[s] = true;
            //printf("s=%d\n", s);
        }
        
        close_conflict(p);
        
        for (int i=0; i<128; ++i) {
            dp[0][i] = 0;
        }
        
        int prevmax=0, currentmax=0;
        
        for (int t=1; t<=n; ++t) { //timeline
            int prev, now, last, max;
            int sl=0, lm=0, le=0;
            
            //analyze the field
            for (int k=0; k<7; ++k) {
                if (field[t][k] == SHORT || field[t][k] == LONG_S) {
                    sl += 1<<(6-k);
                } else if (field[t][k] == LONG_M) {
                    lm += 1<<(6-k);
                } else if (field[t][k] == LONG_E) {
                    le += 1<<(6-k);
                }
            }
            
            for (int i=0; i<128; ++i) { //current key
                
                if (conflict[i]) {
                    dp[t][i] = prevmax;
                } else {
                    max = 0;
                    
                    // for each combi
                    for (int j=0; j<128; ++j) { //prevkey
                        now = i;
                        prev = (conflict[j]) ? 0 : j;
                        last = dp[t-1][j];
                        
                        //s / ls
                        last += scoreboard[sl & now];
                        
                        //lm
                        if ((lm & now & prev) != (lm & now)) continue;
                        
                        //le
                        last += scoreboard[le & (127^now) & prev];
                        
                        if (last > max) max = last;
                    }
                    
                    dp[t][i] = max;
                    
                    if (dp[t][i] > currentmax) currentmax = dp[t][i];
                }
            }
            
            prevmax = currentmax;
            currentmax = 0;
            //for (int i=0; i<128; i+=16) {
            //    printf("%d ", dp[i][t]);
            //}
            //putchar('\n');
        }
        
        int max = -1;
        for (int i=0; i<128; ++i) {
            if (dp[n][i] > max) max = dp[n][i];
        }
        printf("Case #%d: %d\n", ++c, max);
    }
    return 0;
}