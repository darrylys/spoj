#include<stdio.h>

#define LOGN 20
#define MAXN 300010
#define MAXC 100010
#define COL 0
#define CNT 1

int domc[3*MAXN];              //dominate color (<0 -> no dominant color)
int array[LOGN][MAXN][2];
int arr_end[3*MAXN];
int lineup[MAXN];

void build_heap(int root, int a, int b, int level) {
    if (a == b) {
        array[level][a][COL] = lineup[a];
        array[level][a][CNT] = 1;
        arr_end[root] = a;
        domc[root] = lineup[a];
    } else {
        int lc = root<<1, mid = (a+b)>>1;
        
        build_heap(lc, a, mid, level+1);
        build_heap(lc+1, mid+1, b, level+1);
        
        int lp = a, rp = mid+1, p = a;
        int f = -1;
        
        while (lp <= arr_end[lc] && rp <= arr_end[lc+1]) {
            if (array[level+1][lp][COL] < array[level+1][rp][COL]) {
                if (array[level][p][COL] == array[level+1][lp][COL]) {
                    array[level][p][CNT] += array[level+1][lp][CNT];
                } else {
                    if (f == -1) f = 0;
                    else ++p;
                    array[level][p][COL] = array[level+1][lp][COL];
                    array[level][p][CNT] = array[level+1][lp][CNT];
                }
                lp++;
            } else {
                if (array[level][p][COL] == array[level+1][rp][COL]) {
                    array[level][p][CNT] += array[level+1][rp][CNT];
                } else {
                    if (f == -1) f = 0;
                    else ++p;
                    array[level][p][COL] = array[level+1][rp][COL];
                    array[level][p][CNT] = array[level+1][rp][CNT];
                }
                rp++;
            }
        }
        
        for (; lp<=arr_end[lc]; lp++) {
            if (array[level][p][COL] == array[level+1][lp][COL]) {
                array[level][p][CNT] += array[level+1][lp][CNT];
            } else {
                ++p;
                array[level][p][COL] = array[level+1][lp][COL];
                array[level][p][CNT] = array[level+1][lp][CNT];
            }
        }
        
        for (; rp<=arr_end[lc+1]; rp++) {
            if (array[level][p][COL] == array[level+1][rp][COL]) {
                array[level][p][CNT] += array[level+1][rp][CNT];
            } else {
                ++p;
                array[level][p][COL] = array[level+1][rp][COL];
                array[level][p][CNT] = array[level+1][rp][CNT];
            }
        }
        
        arr_end[root] = p;
        int last = array[level][p][CNT];
        if (last > (b-a+1)>>1) {
            domc[root] = array[level][p][COL];
        } else {
            domc[root] = -1;
        }
    }
}

Pair find_num(int root, int a, int b, int x, int y) {
    
}

void print_heap(int root, int a, int b, int space, int level) {
    if (a == b) {
        while (space--) putchar(' ');
        printf("end => %d ", arr_end[root]);
        for (int i=a; i<=arr_end[root]; i++) {
            printf("[%d %d] ", array[level][i][COL], array[level][i][CNT]);
        }
        putchar('\n');
    } else {
        for (int i=0;i<space;i++) putchar(' ');
        printf("end => %d |[color, cnt] => ", arr_end[root]);
        for (int i=a; i<=arr_end[root]; i++) {
            printf("[%d, %d] ", array[level][i][COL], array[level][i][CNT]);
        }
        putchar('\n');
        
        int lc=root<<1, mid=(a+b)>>1;
        print_heap(lc, a, mid, space+3, level+1);
        print_heap(lc+1, mid+1, b, space+3, level+1);
    }
}

int main() {
    int len;
    scanf("%d", &len);
    for (int i=0; i<len; i++) {
        scanf("%d", &lineup[i]);
    }
    
    build_heap(1, 0, len-1, 0);
    print_heap(1, 0, len-1, 0, 0);
}