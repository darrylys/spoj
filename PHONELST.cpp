#include<stdio.h>
#include<string.h>

#define N 100100

typedef struct {
    int child[10];
} Node;

bool end[N];
bool flag[N];
Node node[N];

bool insert(int &now, int &nextpos, char num, bool isend, bool &sgn) {
    if (end[now]) return false;
    if (flag[now] && node[now].child[num-'0']) { //exist edge
        now = node[now].child[(int)(num-'0')];
    } else {
        if (!flag[now]) memset(node[now].child, 0, 10*sizeof(int));
        flag[now] = true;
        node[now].child[(int)(num-'0')] = nextpos;
        end[nextpos] = isend;
        now = nextpos;
        nextpos++;
        sgn = false;
    }
    return true;
}

int main() {
    int nextpos = 0;        //next empty
    int currentpos = 0;     //now
    
    int testcase, n, len;
    char str[15];
    bool v, sgn;
    scanf("%d", &testcase);
    
    while (testcase--) {
        scanf("%d", &n);
        memset(end, false, n*10*sizeof(bool));
        memset(flag, false, n*10*sizeof(bool));
        flag[0] = false;
        end[0] = false;
        nextpos = 1;
        v = true;
        sgn = false;
        while (n-- && v && !sgn) {
            sgn = true;
            currentpos = 0;
            scanf("%s", str);
            len = strlen(str);
            for (int i=0; i<len-1 && v; i++) {
                v &= insert(currentpos, nextpos, str[i], false, sgn);
            }
            if (v) {
                v &= insert(currentpos, nextpos, str[len-1], true, sgn);
                if (!sgn) v = true;
                else v = false;
            }
        }
        if (n==-1) {
            if (v) printf("YES\n");
            else printf("NO\n");
        } else {
            do {
                scanf("%s",str);
            } while (n--);
            printf("NO\n");
        }
    }
    return 0;
}