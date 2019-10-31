#include<stdio.h>

#define MAXN 100010
#define LL long long int

LL ones[3*MAXN];
LL tree[3*MAXN];
bool need_update[3*MAXN];

int getint() {
    char c = getchar();
    int n = 0;
    
    while (c < '0' || c > '9') c=getchar();
    while (c >= '0' && c <= '9') {
        n = n*10 + c-'0';
        c = getchar();
    }
    return n;
}

void init(int root, int a, int b) {
    tree[root] = ones[root] = 0;
    need_update[root] = false;
    
    if (a != b) {
        int lc = root<<1, mid=(a+b)>>1;
        init(lc, a, mid);
        init(lc+1, mid+1, b);
    }
}

void query0(int root, int a, int b, int x, int y, int addedValue) {
    if (a==x && y==b) {
        ones[root] += addedValue;
        tree[root] += ((LL)ones[root])*(b-a+1);
        
        if (a != b) {
            int lc = root<<1;
            need_update[lc] = true;
            ones[lc] += ones[root];
            
            need_update[lc+1] = true;
            ones[lc+1] += ones[root];
        }
        
        need_update[root] = false;
        ones[root] = 0;
        
    } else if (x>y || x>b || y<a) {
        if (need_update[root]) {
            tree[root] += ((LL)ones[root])*(b-a+1);
            
            if (a != b) {
                int lc = root<<1;
                need_update[lc] = true;
                ones[lc] += ones[root];
                
                need_update[lc+1] = true;
                ones[lc+1] += ones[root];
            }
        }
        
        need_update[root] = false;
        ones[root] = 0;
    } else {
        int lc = root<<1, mid=(a+b)>>1, xs=x, ys=y;
        
        if (xs < mid+1) xs = mid+1;
        if (ys > mid) ys = mid;
        
        if (need_update[root]) {
            tree[root] += ((LL)ones[root])*(b-a+1);
            
            need_update[lc] = true;
            ones[lc] += ones[root];
            
            need_update[lc+1] = true;
            ones[lc+1] += ones[root];
        }
        
        
        query0(lc, a, mid, x, ys, addedValue); 
        query0(lc+1, mid+1, b, xs, y, addedValue);
        
        tree[root] = tree[lc] + tree[lc+1];
        
        need_update[root] = false;
        ones[root] = 0;
    }
}

LL query1(int root, int a, int b, int x, int y) {
    if (a==x && y==b) {
        if (need_update[root]) {
            tree[root] += ((LL)ones[root])*(b-a+1);
            
            if (a != b) {
                int lc = root<<1;
                need_update[lc] = true;
                ones[lc] += ones[root];
                
                need_update[lc+1] = true;
                ones[lc+1] += ones[root];
            }
        }
        
        need_update[root] = false;
        ones[root] = 0;
        
        return tree[root];
    } else if (x>y || x>b || y<a) {
        if (need_update[root]) {
            tree[root] += ((LL)ones[root])*(b-a+1);
            
            if (a != b) {
                int lc = root<<1;
                need_update[lc] = true;
                ones[lc] += ones[root];
                
                need_update[lc+1] = true;
                ones[lc+1] += ones[root];
            }
        }
        
        need_update[root] = false;
        ones[root] = 0;
        
        return 0;
    } else {
        int lc = root<<1, mid=(a+b)>>1, xs=x, ys=y;
        
        if (xs < mid+1) xs = mid+1;
        if (ys > mid) ys = mid;
        
        if (need_update[root]) {
            tree[root] += ((LL)ones[root])*(b-a+1);
            
            need_update[lc] = true;
            ones[lc] += ones[root];
            
            need_update[lc+1] = true;
            ones[lc+1] += ones[root];
        }
        
        LL left = query1(lc, a, mid, x, ys);
        LL right = query1(lc+1, mid+1, b, xs, y);
        
        need_update[root] = false;
        ones[root] = 0;
        
        return left + right;
    }
}

void print_tree(int root, int a, int b, int space) {
    for (int i=0;i<space; ++i) putchar(' ');
    printf("[a, b, value, nu, ones] => [%d, %d, %lld, %d, %d]\n"
        , a, b, tree[root], need_update[root], ones[root]);
    if (a != b) {
        print_tree(root*2, a, (a+b)/2, space+4);
        print_tree(root*2+1, (a+b)/2+1, b, space+4);
    }
}

int main() {
    int test, n, c, cmd, p, q, v;
    test = getint();
    //scanf("%d", &test);
    //printf("test=%d\n", test);
    while (test--) {
        n = getint(); c=getint();
        //scanf("%d%d", &n, &c);
        init(1, 0, n-1);
        
        while (c--) {
            cmd = getint();
            
            if (cmd) {
                p =getint(); q = getint();
                //scanf("%d%d", &p, &q);
                printf("%lld\n", query1(1, 0, n-1, p-1, q-1));
                //print_tree(1, 0, n-1, 0);
            } else {
                p =getint(); q=getint(); v=getint();
                //scanf("%d%d%d", &p, &q, &v);
                //printf("p=%d, q=%d, v=%d\n", p, q, v);
                query0(1, 0, n-1, p-1, q-1, v);
            }
        }
    }
    return 0;
}