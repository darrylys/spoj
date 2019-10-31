#include<stdio.h>

#define N 101000
#define max3(a,b,c) _max(a,_max(b,c))

int _max(int a, int b) {
    return (a>b)?a:b;
}

typedef struct {
    int left;
    int right;
    int max;
    int leftelement;
    int rightelement;
} Node;

typedef struct {
    int left, right, max;
    int leftelement;
    int rightelement;
    bool flag;
} Item;

int arr[N];
Node node[N*3];

void make_tree(int root, int a, int b) {
    if (a == b) {
        node[root].left = 1;
        node[root].right = 1;
        node[root].max = 1;
        node[root].leftelement = arr[a-1];
        node[root].rightelement = arr[b-1];
    } else {
        int leftc = root<<1;
        int rightc = (root<<1)+1;
        int mid =  (a+b)>>1;
        make_tree(leftc, a, mid);
        make_tree(rightc, mid+1, b);
        
        node[root].max = max3(node[leftc].max, node[rightc].max,
            (node[leftc].rightelement == node[rightc].leftelement)?
            (node[leftc].right + node[rightc].left):(0));
        
        node[root].left = (node[leftc].leftelement == node[rightc].leftelement)?
            (node[leftc].left+node[rightc].left):(node[leftc].left);
        node[root].right =(node[leftc].rightelement == node[rightc].rightelement)?
            (node[rightc].right+node[leftc].right):(node[rightc].right);
        
        node[root].leftelement = node[leftc].leftelement;
        node[root].rightelement = node[rightc].rightelement;
    }
}

Item query(int root, int a, int b, int x, int y) {
    if (x == a && y == b) { //range match
        Item r;
        r.left = node[root].left;
        r.right = node[root].right;
        r.max = node[root].max;
        r.leftelement = node[root].leftelement;
        r.rightelement = node[root].rightelement;
        r.flag = true;
        return r;
    } else if (x>y || y<a || x>b) { //invalid
        Item r;
        r.flag = false;
        return r;
    } else {
        int ny = y, nx = x, mid = (a+b)>>1, leftc = root<<1, rightc = leftc+1;
        if (ny > mid) ny = mid;
        if (nx <= mid) nx = mid+1;
        Item left = query(leftc, a, mid, x, ny);
        Item right = query(rightc, mid+1, b, nx, y);
        
        Item now;
        
        if (left.flag && right.flag) {
            now.max = max3(left.max, right.max,
                (left.rightelement == right.leftelement)?(left.right + right.left):(0));
        
            now.left = (left.leftelement == right.leftelement)?
                (left.left+right.left):(left.left);
            now.right =(left.rightelement == right.rightelement)?
                (right.right+left.right):(right.right);
                
            now.leftelement = left.leftelement;
            now.rightelement = right.rightelement;
            now.flag = true;
            return now;
        } else if (!left.flag) {
            return right;
        } else {
            return left;
        }
        
    }
}

void print_tree(int root, int a, int b, int space) {
    if (a == b) {
        while (space--) putchar(' ');
        printf("[le, l, m, r, re] => [%d, %d, %d, %d, %d]\n",
            node[root].leftelement, node[root].left, node[root].max, node[root].right, node[root].rightelement);
    } else {
        int sp = space;
        while (sp--) putchar(' ');
        printf("[le, l, m, r, re] => [%d, %d, %d, %d, %d]\n",
            node[root].leftelement, node[root].left, node[root].max, node[root].right, node[root].rightelement);
        print_tree(root*2, a, (a+b)/2, space+4);
        print_tree(root*2+1, (a+b)/2+1, b, space+4);
    }
}

int main() {
    int n, q, x, y;
    Item m;
    
    while (scanf("%d", &n) && n) {
        scanf("%d", &q);
        
        for (int i=0; i<n; i++) {
            scanf("%d", &arr[i]);
        }
        
        make_tree(1,1,n);
        //print_tree(1,1,n,0);
        while (q--) {
            scanf("%d %d", &x, &y);
            m = query(1,1,n,x,y);
            printf("%d\n", m.max);
        }
    }
    return 0;
}
