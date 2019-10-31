#include<stdio.h>

#define MAXN 300020
#define LOGN 20

int array2[MAXN];               //real array

typedef struct {
    int cand;
    int cnt;
} Pair;

typedef struct {
    int CD;
    int CN;
} Node;

typedef struct {
    int COL;
    int CNT;
} Data;

Node tree[3*MAXN];
int arr_end[3*MAXN];

void build_tree(int root, int a, int b) {
    if (a == b) {
        tree[root].CD = array2[a];
        tree[root].CN = 1;
    } else {
        int lc = root<<1, mid = (a+b)>>1;
        build_tree(lc, a, mid);
        build_tree(lc+1, mid+1, b);
        
        if (tree[lc].CD == tree[lc+1].CD) {
            tree[root].CD = tree[lc].CD;
            tree[root].CN = tree[lc].CN + tree[lc+1].CN;
        } else {
            if (tree[lc].CN > tree[lc+1].CN) {
                tree[root].CD = tree[lc].CD;
                tree[root].CN = tree[lc].CN - tree[lc+1].CN;
            } else {
                tree[root].CD = tree[lc+1].CD;
                tree[root].CN = tree[lc+1].CN - tree[lc].CN;
            }
        }
    }
}

Pair query(int root, int a, int b, int x, int y) {
    if (a == x && y == b) {
        Pair r;
        
        r.cand = tree[root].CD;
        r.cnt = tree[root].CN;
        
        return r;
    } else if (x>b || y<a || x>y) {
        Pair r;
        
        r.cand = -1;
        r.cnt = 0;
        
        return r;
    } else {
        int lc = root<<1, mid = (a+b)>>1;
        int xs = x, ys = y;
        if (ys > mid) ys = mid;
        if (xs <= mid) xs = mid+1;
        
        Pair left = query(lc, a, mid, x, ys);
        Pair right = query(lc+1, mid+1, b, xs, y);
        
        Pair result;
        
        if (left.cand == right.cand) {
            result.cand = left.cand;
            result.cnt = left.cnt + right.cnt;
        } else {
            if (left.cnt > right.cnt) {
                result.cand = left.cand;
                result.cnt = left.cnt - right.cnt;
            } else {
                if (right.cand == -1) result.cand = left.cand;
                else result.cand = right.cand;
                
                result.cnt = right.cnt - left.cnt;
            }
        }
        
        return result;
    }
}

Data array[LOGN][MAXN];       //sorted + tallied

void build_heap(int root, int a, int b, int level) {
    if (a == b) {
        array[level][a].COL = array2[a];
        array[level][a].CNT = 1;
        arr_end[root] = a;
    } else {
        int lc = root<<1, mid = (a+b)>>1;
        
        build_heap(lc, a, mid, level+1);
        build_heap(lc+1, mid+1, b, level+1);
        
        int lp = a, rp = mid+1, p = a;
        int f = -1;
        
        while (lp <= arr_end[lc] && rp <= arr_end[lc+1]) {
            if (array[level+1][lp].COL < array[level+1][rp].COL) {
                if (array[level][p].COL == array[level+1][lp].COL) {
                    array[level][p].CNT += array[level+1][lp].CNT;
                } else {
                    if (f == -1) f = 0;
                    else ++p;
                    array[level][p].COL = array[level+1][lp].COL;
                    array[level][p].CNT = array[level+1][lp].CNT;
                }
                lp++;
            } else {
                if (array[level][p].COL == array[level+1][rp].COL) {
                    array[level][p].CNT += array[level+1][rp].CNT;
                } else {
                    if (f == -1) f = 0;
                    else ++p;
                    array[level][p].COL = array[level+1][rp].COL;
                    array[level][p].CNT = array[level+1][rp].CNT;
                }
                rp++;
            }
        }
        
        for (; lp<=arr_end[lc]; lp++) {
            if (array[level][p].COL == array[level+1][lp].COL) {
                array[level][p].CNT += array[level+1][lp].CNT;
            } else {
                ++p;
                array[level][p].COL = array[level+1][lp].COL;
                array[level][p].CNT = array[level+1][lp].CNT;
            }
        }
        
        for (; rp<=arr_end[lc+1]; rp++) {
            if (array[level][p].COL == array[level+1][rp].COL) {
                array[level][p].CNT += array[level+1][rp].CNT;
            } else {
                ++p;
                array[level][p].COL = array[level+1][rp].COL;
                array[level][p].CNT = array[level+1][rp].CNT;
            }
        }
        
        arr_end[root] = p;
    }
}

int num_of_occurence(int root, int a, int b, int x, int y, int level, int key) {
    if (a == x && y == b) {
        
        int u=a, v=arr_end[root]+1, c;
        
        while (u<v) {
            c = (u+v)>>1;
            if (key < array[level][c].COL) {
                v = c;
            } else if (key > array[level][c].COL) {
                u = c+1;
            } else {
                return array[level][c].CNT;
            }
        }
        return 0;
        
    } else if (x>b || y<a || x>y) {
        return 0;
    } else {
        int lc = root<<1, mid = (a+b)>>1;
        int xs = x, ys = y;
        if (ys > mid) ys = mid;
        if (xs <= mid) xs = mid+1;
        
        int left = num_of_occurence(lc, a, mid, x, ys, level+1, key);
        int right = num_of_occurence(lc+1, mid+1, b, xs, y, level+1, key);
        
        return left+right;
    }
    
}
/*
void print_tree(int root, int a, int b, int space) {
    if (a == b) {
        while (space--) putchar(' ');
        printf("range=[%d. %d], cand, count => [%d, %d]\n", a, b, tree[root].CD, tree[root].CN);
    } else {
        for (int i=0;i<space;i++) putchar(' ');
        printf("range=[%d. %d], cand, count => [%d, %d]\n", a, b, tree[root].CD, tree[root].CN);
        
        int lc = root<<1, mid = (a+b)>>1;
        print_tree(lc, a, mid, space+4);
        print_tree(lc+1, mid+1, b, space+4);
    }
}

void print_heap(int root, int a, int b, int space, int level) {
    if (a == b) {
        while (space--) putchar(' ');
        printf("range=[%d %d] end => %d |[col,cnt] => ", a, b, arr_end[root]);
        for (int i=a; i<=arr_end[root]; i++) {
            printf("[%d %d] ", array[level][i].COL, array[level][i].CNT);
        }
        putchar('\n');
    } else {
        for (int i=0;i<space;i++) putchar(' ');
        printf("range=[%d %d] end => %d |[col,cnt] => ", a, b, arr_end[root]);
        for (int i=a; i<=arr_end[root]; i++) {
            printf("[%d, %d] ", array[level][i].COL, array[level][i].CNT);
        }
        putchar('\n');
        
        int lc=root<<1, mid=(a+b)>>1;
        print_heap(lc, a, mid, space+3, level+1);
        print_heap(lc+1, mid+1, b, space+3, level+1);
    }
}
*/
int main() {
    int n, c, m, x, y;
    scanf("%d %d", &n, &c);
    
    for (int i=0; i<n; i++) {
        scanf("%d", &array2[i]);
    }
    
    build_tree(1,0,n-1);
    build_heap(1,0,n-1,0);
    
    //printf("array top = %d %d <> %d %d\n", array[0][0].COL, array[0][0].CNT, array[0][1].COL, array[0][1].CNT);
    
    //printf("Tree:\n");
    //print_tree(1, 0, n-1, 0);
    
    //printf("\nHeap:\n");
    //print_heap(1,0,n-1,0,0);
    
    scanf("%d", &m);
    while (m--) {
        scanf("%d %d", &x, &y);
        Pair result = query(1,0,n-1,x-1,y-1);
        int num = num_of_occurence(1,0,n-1,x-1,y-1,0,result.cand);
        //printf("num=%d, candidate=%d\n", num, result.cand);
        if (num <= (y-x+1)>>1) {
            printf("no\n");
        } else {
            //printf("num=%d\n", num);
            printf("yes %d\n", result.cand);
        }
        //putchar('\n');
    }
    return 0;
}