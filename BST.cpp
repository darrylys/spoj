#include<stdio.h>
#include<string.h>

#define N 310000
#define L1 0
#define L2 1
#define R1 2
#define R2 3
#define LC 0
#define RC 1
#define ll long long

int range[N][4];
int level[N];
int _heap[N*4];

void update_tree(int root, int a, int b, int x, int y, int fill) {
    //printf("%d\n", root);
    if (a == x && b == y) {
        _heap[root] = fill;
    } else if (x>y || x>b || y<a) {
        // do nothing
    } else {
        int lc = root<<1, rc = lc+1;
        int ny = y, nx = x, mid = (a+b)>>1;
        if (ny > mid) ny = mid;
        if (nx < mid+1) nx = mid+1;
        
        update_tree(lc, a, mid, x, ny, fill);
        update_tree(rc, mid+1, b, nx, y, fill);
    }
}

int getParent(int root, int a, int b, int x) {
    int now = root;
    int mid;
    int val = 0;
    while (true) {
        mid = (a+b)>>1;
        val = (_heap[now] == 0) ? val : _heap[now];
        if (a == b) break;
        now <<= 1;
        if (x > mid) {
            a = mid+1;
            now++;
        } else {
            b = mid;
        }
        //printf("a=%d|b=%d|now=%d\n", a,b,now);
    }
    return val;
}

void update_range(int parent, int x, int n) {
    if (x > parent) {
        range[x][L1] = range[parent][R1];
        range[x][L2] = x-1;
        range[x][R1] = x+1;
        range[x][R2] = range[parent][R2];
    } else {
        range[x][L1] = range[parent][L1];
        range[x][L2] = x-1;
        range[x][R1] = x+1;
        range[x][R2] = range[parent][L2];
    }
    update_tree(1,1,n,range[x][L1], range[x][L2], x);
    update_tree(1,1,n,range[x][R1], range[x][R2], x);
}

void init_first_node(int node, int n) {
    range[node][L1] = 1;
    range[node][L2] = node-1;
    range[node][R1] = node+1;
    range[node][R2] = n;
    update_tree(1,1,n,range[node][L1], range[node][L2], node);
    update_tree(1,1,n,range[node][R1], range[node][R2], node);
}

int main() {
    
    int n, root, num;
    ll C = 0;
    scanf("%d", &n);
    scanf("%d", &root);
    level[0] = 0;
    init_first_node(root, n);
    printf("0\n");
    //printf("number = %d\n\n", root);
    //print_tree(1,1,n,0);
    for (int i=1; i<n; i++) {
        scanf("%d", &num);
        int parent = getParent(1, 1, n, num);
        level[num] = level[parent]+1;
        C = C + level[num];
        printf("%lld\n", C);
        update_range(parent, num, n);
        
        //printf("number = %d\n", num);
        //print_tree(1,1,n,0);
    }

    return 0;
}