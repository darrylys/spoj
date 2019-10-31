#include<cstdio>
#define N 50010
#define max3(a,b,c) _max(a,_max(b,c))
#define INF 1000000000

typedef struct {
    int fullsum;
    int leftsum;
    int rightsum;
    int maxsum;
} Node;

typedef struct {
    int fullsum, leftsum, rightsum, maxsum;
    bool flag;
} Item;

int array[N];
int heapmap[N];
Node node[N*3];

int _max(int a, int b) {
    return (a>=b)?a:b;
}

void edit_tree(int root) {
    int left, right;
    while (root > 0) {
        left = node[root*2+1].leftsum;
        right= node[root*2].rightsum;
        
        node[root].maxsum = max3(node[root*2+1].maxsum, node[root*2].maxsum,left + right);
        node[root].fullsum = node[root*2+1].fullsum + node[root*2].fullsum;
        node[root].leftsum = _max(node[root*2].fullsum + node[root*2+1].leftsum,
                                  node[root*2].leftsum);
        node[root].rightsum = _max(node[root*2+1].fullsum + node[root*2].rightsum,
                                  node[root*2+1].rightsum);
        root /= 2;
    }
}

void run_edit(int pos, int newval) {
    node[pos].fullsum = newval;
    node[pos].leftsum = newval;
    node[pos].rightsum = newval;
    node[pos].maxsum = newval;
    
    edit_tree(pos/2);
}

void init(int root, int a, int b) {
    if (a == b) {
        //printf("stop %d\n", root);
        node[root].fullsum = array[a];
        node[root].leftsum = array[a];
        node[root].rightsum = array[a];
        node[root].maxsum = array[a];
        heapmap[a] = root;
    } else {
        //printf("rec %d\n", root);
        init(root*2, a, (a+b)/2);
        init(root*2+1, (a+b)/2+1, b);
        
        int left = node[root*2+1].leftsum;
        int right= node[root*2].rightsum;
        
        node[root].maxsum = max3(node[root*2+1].maxsum, node[root*2].maxsum,left + right);
        node[root].fullsum = node[root*2+1].fullsum + node[root*2].fullsum;
        node[root].leftsum = _max(node[root*2].fullsum + node[root*2+1].leftsum,
                                  node[root*2].leftsum);
        node[root].rightsum = _max(node[root*2+1].fullsum + node[root*2].rightsum,
                                  node[root*2+1].rightsum);
        //--
    }
}

Item query(int root, int a, int b, int x, int y) {
    if (x > b || y < a || (x > y)) { //out of / impossible range
        Item v;
        v.fullsum = -INF;
        v.leftsum = -INF;
        v.rightsum = -INF;
        v.maxsum = -INF;
        v.flag = false;
        return v;
    } else if (a == x && y == b) { //intervals match
        Item r;
        r.fullsum = node[root].fullsum;
        r.leftsum = node[root].leftsum;
        r.rightsum = node[root].rightsum;
        r.maxsum = node[root].maxsum;
        r.flag = true;
        return r;
    } else {
        int ny = y, nx = x;
        if (ny > (a+b)/2) ny = (a+b)/2;
        if (nx < (a+b)/2+1) nx = (a+b)/2+1;
        Item left = query(root*2, a, (a+b)/2, x, ny);
        Item right = query(root*2+1, (a+b)/2+1, b, nx, y);
        
        Item now;
        
        if (left.flag && right.flag) {
            now.maxsum = max3(left.maxsum, right.maxsum, left.rightsum + right.leftsum);
            now.fullsum = left.fullsum + right.fullsum;
            now.leftsum = _max(left.fullsum + right.leftsum, left.leftsum);
            now.rightsum = _max(right.fullsum + left.rightsum,right.rightsum);
            now.flag = true;
        } else if (!left.flag) {
            return right;
        } else {
            return left;
        }
        return now;
    }
}

int main() {
    int n, m, x, y, h;
    scanf("%d", &n);
    for (int i=1; i<=n; i++) {
        scanf("%d", &array[i]);
    }
    init(1, 1, n);
    scanf("%d", &m);
    while (m--) {
        scanf("%d %d %d", &h, &x, &y);
        if (h) {
            Item now = query(1, 1, n, x,y);
            printf("%d\n", now.maxsum);
        } else {
            run_edit(heapmap[x], y);
        }
    }
    return 0;
}
