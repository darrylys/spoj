#include<stdio.h>
#include<vector>

#define MAXN 300020
#define MAXC 100010

using namespace std;

typedef struct {
    int cand;
    int cnt;
} Pair;

typedef struct {
    int CD;
    int CN;
} Node;

Node tree[3*MAXN];
int array2[MAXN];               //real array
vector<int> index[MAXC];

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

int bsearch(vector<int> &arr, int key, int start, int end, bool &isFound) {
    int u = start, v =end, c;
    
    while (u<v) {
        c = (u+v)>>1;
        if (key < arr[c]) {
            v = c;
        } else if (key > arr[c]) {
            u = c+1;
        } else {
            isFound = true;
            return c;
        }
    }
    
    isFound = false;
    return u-1;
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
*/


int main() {
    int n, c, m, x, y;
    bool fa, fb;
    scanf("%d %d", &n, &c);
    
    for (int i=0; i<n; i++) {
        scanf("%d", &array2[i]);
        index[array2[i]].push_back(i);
    }
    
    build_tree(1,0,n-1);
    
    //printf("Tree:\n");
    //print_tree(1, 0, n-1, 0);
    
    scanf("%d", &m);
    while (m--) {
        scanf("%d %d", &x, &y);
        Pair result = query(1,0,n-1,x-1,y-1);
        
        int ia = bsearch(index[result.cand], x-1, 0, index[result.cand].size(), fa);
        int ib = bsearch(index[result.cand], y-1, 0, index[result.cand].size(), fb);
        int res;
        if (fa) {
            res = ib-ia+1;
        } else {
            res = ib-ia;
        }
        //printf("%d\n", res);
        //printf("num=%d, candidate=%d\n", num, result.cand);
        if (res <= (y-x+1)>>1) {
            printf("no\n");
        } else {
            //printf("num=%d\n", num);
            printf("yes %d\n", result.cand);
        }
        //putchar('\n');
    }
    return 0;
}