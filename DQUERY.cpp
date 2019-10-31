#include<stdio.h>
#include<algorithm>
#include<vector>

using namespace std;

#define MAXN 30010
#define MAXQ 200010
#define MAXS 1000010

vector<int> pos[MAXS];
int qp[MAXQ];
int remap[MAXN];
int array[MAXN];
int ptr[MAXS];
int result[MAXQ];

int tree[MAXN*3];
int qstart[MAXQ];
int qend[MAXQ];

int getint() {
    char c = getchar();
    int n = 0;
    while (c < '0' || c > '9') c=getchar();
    while (c >= '0' && c <= '9') {
        n = n*10 + c-'0'
        c=getchar();
    }
    return n;
}

bool cmp(int a, int b) {
    return qstart[a] < qstart[b];
}

//edit the array BEFOREHAND
void build_tree(int root, int a, int b) {
    if (a == b) {
        tree[root] = (int)(array[a] != 0);
        remap[a] = root;
    } else {
        int lc = root<<1, mid = (a+b)>>1, rc=lc+1;
        build_tree(lc, a, mid);
        build_tree(lc+1, mid+1, b);
        
        tree[root] = tree[lc]+tree[rc];
    }
}

void update(int index, int nv) {
    int root = remap[index], lc, rc;
    
    tree[root] = (int)(nv != 0);
    root >>= 1;
    
    while (root) {
        lc = root<<1, rc = lc+1;
        tree[root] = tree[lc]+tree[rc];
        root >>= 1;
    }
}

int getval(int root, int a, int b, int x, int y) {
    if (a == x && b == y) {
        return tree[root];
    } else if (x>b || y<a || x>y) {
        return 0;
    } else {
        int lc = root<<1, rc=lc+1, mid=(a+b)>>1, xs = x, ys = y;
        if (xs < mid+1) xs = mid+1;
        if (ys > mid) ys = mid;
        
        int left = getval(lc, a, mid, x, ys);
        int right = getval(rc, mid+1, b, xs, y);
        
        return left+right;
    }
}

/*
void print_tree(int root, int a, int b, int space) {
    for (int i=0;i<space;i++) putchar(' ');
    if (a == b) {

        printf("tree=>%d, root=>%d, a,b => %d,%d\n", tree[root], root, a, b);
    } else {
        printf("tree=>%d, root=>%d, a,b => %d,%d\n", tree[root], root, a, b);
        int lc = root<<1, mid = (a+b)>>1, rc=lc+1;
        print_tree(lc, a, mid, space+4);
        print_tree(lc+1, mid+1, b, space+4);
        
    }
}
*/
int main() {
    int n, q, a, id;
    
    n=getint();
    
    for (int i=1; i<=n; ++i) {
        a=getint();
        
        //only mark first occurences. the rest is 0
        if (pos[a].size() == 0) {
            array[i] = a;
        } else {
            array[i] = 0;
        }
        pos[a].push_back(i);
    }
    
    build_tree(1,1,n);
    
    //print_tree(1,1,n,0);
    
    q=getint();
    for (int i=0;i<q;++i) {
        qstart[i]=getint();
        qend[i]=getint();
        qp[i] = i;
    }
    sort(qp, qp+q, cmp); //sort the query
    
    //for (int i=0;i<q;i++) {
    //    printf("start, end = %d %d\n", query[qp[i]].start, query[qp[i]].end);
    //}
    int last = qstart[qp[q-1]];
    for (int i=1, x = 0; i<=last; ++i) {
        id = qp[x];
        
        if (qstart[id] == i) {
            
            while (qstart[id] == i) {
                result[id] = getval(1, 1, n, i, qend[id]);
                x++;
                if (x < q) {
                    id =qp[x];
                } else goto here;
            }
        }
        //printf("i=%d, x=%d\n", i, x);
        //updating values of the tree.
        int val = array[i];
        int next = ++ptr[val];
        if (next < pos[val].size()) { //update if necessary
            update(pos[val][next] ,val);
            array[pos[val][next]] = val;
        }
        
        //print_tree(1,1,n,0);
    }
    
    here:
    ;
    
    for (int i=0; i<q; ++i) {
        printf("%d\n", result[i]);
    }    
    
    
    return 0;
}