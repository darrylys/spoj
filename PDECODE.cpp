//impl: DisjointSetDataStructure

#include<cstdio>
#include<cstring>
#define MAXN 85
#define SEQL 0
#define INDEX 1
#define PARENT 0

int table[MAXN][MAXN];

int node[MAXN][2];
int seq[MAXN];
bool flag[MAXN];
char text[MAXN];
char decoded[MAXN];

int setting(int x, int head) {
    if (x != node[x][PARENT]) {
        table[head][node[x][INDEX]+1] = x;
        node[x][PARENT] = setting(node[x][PARENT], head);
    } else {
        table[head][node[x][INDEX]+1] = x;
    }
    return node[x][PARENT];
}

int find_set(int x) {
    if (x != node[x][PARENT]) {
        node[x][PARENT] = find_set(node[x][PARENT]);
    }
    return node[x][PARENT];
}

void make_set(int n) {
    for (int i=0; i<n;i++) {
        seq[i]--;
        flag[i] = false;
    }
    //memset(flag, false, sizeof(bool));
    bool makeroot = true;
    int now, cntr, prev;
    
    for (int i=0; i<n; i++) {
        if (!flag[i]) {
            //printf("new roots = %d\n", i);
            makeroot = true;
            now = i;
            cntr = 0;
            flag[i] = true;
            do {
                if (makeroot) {
                    node[now][PARENT] = now;
                    node[now][INDEX] = 0;
                    prev = now;
                    flag[now] = true;
                    now = seq[now];
                    makeroot = false;
                    cntr = 1;
                } else {
                    node[now][PARENT] = prev;
                    node[now][INDEX] = cntr++;
                    prev = now;
                    flag[now] = true;
                    now = seq[now];
                }
            } while (!flag[now]);
            setting(prev, now);
            table[now][SEQL] = cntr;
        }
        //printf("i=%d, flag[%d]=%d\n", i, i, flag[i]);
    }
    //printf("END_MAKE_SET\n");
}

void printtable(int n) {
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            printf("%d ", table[i][j]);
        }
        putchar('\n');
    }
}

int main() {
    int n,m;
    while (scanf("%d %d", &n, &m) && n) {
        for (int i=0; i<n; i++) {
            scanf("%d", &seq[i]);
        }
        getchar();
        gets(text);
        
        make_set(n);
        //printtable(n);
        for (int i=0;i<n;i++) {
            int set = find_set(i);
            //printf("set = %d\n", set);
            decoded[table[set][(node[i][INDEX] + m)
                %table[set][SEQL]+1]] = text[i];
        }
        for (int i=0;i<n;i++) {
            putchar(decoded[i]);
        }
        //printf("TRIMMING");
        putchar('\n');
    }
    return 0;
}