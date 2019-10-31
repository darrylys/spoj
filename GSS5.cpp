#include<cstdio>

#define N 15000
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

int cum_array[N];
int array[N];
Node node[N*3];

int _max(int a, int b) {
    return (a>=b)?a:b;
}

void init(int root, int a, int b) {
    if (a == b) {
        //printf("stop %d\n", root);
        node[root].fullsum = array[a];
        node[root].leftsum = array[a];
        node[root].rightsum = array[a];
        node[root].maxsum = array[a];
    } else {
        //printf("rec %d\n", root);
        init((root<<1), a, ((a+b)>>1));
        init((root<<1)+1, ((a+b)>>1)+1, b);
        
        int left = node[(root<<1)+1].leftsum;
        int right= node[(root<<1)].rightsum;
        
        node[root].maxsum = max3(node[(root<<1)+1].maxsum, node[(root<<1)].maxsum,left + right);
        node[root].fullsum = node[(root<<1)+1].fullsum + node[(root<<1)].fullsum;
        node[root].leftsum = _max(node[(root<<1)].fullsum + node[(root<<1)+1].leftsum,
                                  node[(root<<1)].leftsum);
        node[root].rightsum = _max(node[(root<<1)+1].fullsum + node[(root<<1)].rightsum,
                                  node[(root<<1)+1].rightsum);
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
        int ny = y, nx = x, mid = ((a+b)>>1);
        if (ny > mid) ny = mid;
        if (nx < mid+1) nx = mid+1;
        Item left = query((root<<1), a, mid, x, ny);
        Item right = query((root<<1)+1, mid+1, b, nx, y);
        
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
    int test, n, m, x1, y1, x2, y2;
    Item left, right, middle, now;
    scanf("%d", &test);
    while (test--) {
        scanf("%d", &n);
        cum_array[0] = 0;
        for (int i=1; i<=n; i++) {
            scanf("%d", &array[i]);
        }
        for (int i=1; i<=n; i++) {
            cum_array[i] = cum_array[i-1] + array[i];
        }
        init(1, 1, n);
        scanf("%d", &m);
        while (m--) {
            scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
            if (x1 == x2 && y1 == y2) {
                now = query(1, 1, n, x1,y1);
                printf("%d\n", now.maxsum);
            } else if (x1 < x2 && y1 < y2) {
                if (x2 < y1) {
                    left = query(1,1,n,x1,x2-1);
                    right = query(1,1,n,y1+1,y2);
                    middle = query(1,1,n,x2,y1);
                    
                    int maxm = max3((left.rightsum + middle.leftsum), 
                                    middle.maxsum, 
                                    (right.leftsum + middle.rightsum));
                    int finmax = _max(maxm, left.rightsum + middle.fullsum + right.leftsum);
                    
                    printf("%d\n", finmax);
                } else if (x2 == y1){
                    left = query(1,1,n,x1,y1);
                    right = query(1,1,n,x2+1,y2);
                    
                    int maxm = _max(left.rightsum, left.rightsum + right.leftsum);
                    int fmax = max3(maxm, array[x2] + right.leftsum, array[x2]);
                    
                    printf("%d\n", fmax);
                } else {
                    left = query(1,1,n,x1,y1);
                    right = query(1,1,n,x2,y2);
                    int fm = cum_array[x2-1] - cum_array[y1];
                    printf("%d\n", left.rightsum + fm + right.leftsum);
                }
            } else if (x1 < x2 && y1 == y2) {
                left = query(1,1,n,x1,x2-1);
                right = query(1,1,n,x2,y2);
                
                int maxm = _max(left.rightsum + right.leftsum, right.maxsum);
                printf("%d\n", maxm);
            } else {
                left = query(1,1,n,x1,y1);
                right = query(1,1,n,y1+1,y2);
                
                int maxm = _max(left.maxsum, left.rightsum + right.leftsum);
                printf("%d\n", maxm);
            }
        }
    }
    return 0;
}
