#include<cstdio>

#define N 110000

typedef struct {
    int off;
    int on;
    bool need_update;
} Node;

Node node[N*3];

void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void make_tree(int root, int a, int b) {
    if (a == b) {
        node[root].off = 1;
        node[root].on = 0;
        node[root].need_update = false;
    } else {
        make_tree(root<<1, a, (a+b)>>1);
        make_tree((root<<1)+1, ((a+b)>>1)+1, b);
        
        node[root].off = node[root<<1].off + node[(root<<1)+1].off;
        node[root].on = node[root<<1].on + node[(root<<1)+1].on;
        node[root].need_update = false;
    }
}

void flip(int root, int a, int b, int x, int y) {
    //printf("flip %d %d %d %d %d\n", root, a, b, x, y);
    if (x == a && y == b) { //range match
        if (!node[root].need_update) {
            swap(node[root].on, node[root].off);
            if (a != b) {
                node[root<<1].need_update = !(node[root<<1].need_update);
                node[(root<<1)+1].need_update = !(node[(root<<1)+1].need_update);
            }
        }
        
        node[root].need_update = false;
    } else if (x>y || y<a || x>b) { //invalid range
        if (node[root].need_update) {
            swap(node[root].on, node[root].off);
            node[root].need_update = false;
            
            if (a != b) {
                node[root<<1].need_update = !(node[root<<1].need_update);
                node[(root<<1)+1].need_update = !(node[(root<<1)+1].need_update);
            }
        }
    } else {
        int xs = x, ys = y, mid = (a+b)>>1;
        if (xs <= mid) xs = mid+1;
        if (ys > mid) ys = mid;
        
        if (node[root].need_update) {
            if (a != b) {
                node[root<<1].need_update = !(node[root<<1].need_update);
                node[(root<<1)+1].need_update = !(node[(root<<1)+1].need_update);
            }
        }
        flip(root<<1, a, mid, x, ys);
        flip((root<<1)+1, mid+1, b, xs, y);
        
        node[root].off = node[root<<1].off + node[(root<<1)+1].off;
        node[root].on = node[root<<1].on + node[(root<<1)+1].on;
        node[root].need_update = false;
    }
}

int get(int root, int a, int b, int x, int y) {
    //printf("get %d %d %d %d %d\n", root, a, b, x, y);
    if (x == a && y == b) {
        if (node[root].need_update) { //need update
            
            //update values
            swap(node[root].on, node[root].off);
            node[root].need_update = false;
            
            if (a != b) {
                node[root<<1].need_update = !(node[root<<1].need_update);
                node[(root<<1)+1].need_update = !(node[(root<<1)+1].need_update);
            }
        }
        return node[root].on;
    } else if (x>y || y<a || x>b) { //invalid range
        if (node[root].need_update) {
            swap(node[root].on, node[root].off);
            node[root].need_update = false;
            
            if (a != b) {
                node[root<<1].need_update = !(node[root<<1].need_update);
                node[(root<<1)+1].need_update = !(node[(root<<1)+1].need_update);
            }
        }
        return 0;
    } else { 
        int xs = x, ys = y, mid = (a+b)>>1;
        if (xs <= mid) xs = mid+1;
        if (ys > mid) ys = mid;
        
        if (node[root].need_update) {
            if (a != b) {
                node[root<<1].need_update = !(node[root<<1].need_update);
                node[(root<<1)+1].need_update = !(node[(root<<1)+1].need_update);
            }
        }
        int left = get(root<<1, a, mid, x, ys);
        int right = get((root<<1)+1, mid+1, b, xs, y);
        
        node[root].off = node[root<<1].off + node[(root<<1)+1].off;
        node[root].on = node[root<<1].on + node[(root<<1)+1].on;
        node[root].need_update = false;
        
        return left+right;
    }
}

void printspace(int space) {
    while (space--) putchar(' ');
}

void print_tree(int root, int a, int b, int spaces) {
    if (a == b) {
        printspace(spaces);
        printf("[%d,%d] => <off=%d|on=%d|U=%d>\n", a, b, node[root].off, node[root].on, node[root].need_update);
    } else {
        printspace(spaces);
        printf("[%d,%d] => <off=%d|on=%d|U=%d>\n", a, b, node[root].off, node[root].on, node[root].need_update);
        print_tree(root<<1, a, (a+b)>>1, spaces+4);
        print_tree((root<<1)+1, ((a+b)>>1)+1, b, spaces+4);
    }
    
}

void view_debug(int n, int &q) {
    printf("config = %d\n", q++);
    print_tree(1,1,n,0);
    putchar('\n');
}

int main() {
    int n, m, k, x, y, ans, q = 0;
    
    scanf("%d %d", &n, &m);
    
    make_tree(1, 1, n);
    //view_debug(n,q);
    
    while (m--) {
        scanf("%d %d %d", &k, &x, &y);
        //printf("%d %d %d", k, x, y);
        if (k) {
            ans = get(1, 1, n, x, y);
            //view_debug(n,q);
            printf("%d\n", ans);
        } else {
            flip(1,1,n,x,y);
            //view_debug(n,q);
        }
    }
    return 0;
}