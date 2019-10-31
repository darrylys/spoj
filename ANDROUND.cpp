#include<stdio.h>

#define N 31000
#define AND_ID 2147483647
#define OUT 1000000

int heap[N*3];
int arr[N];

int init(int root, int a, int b) {
    if (a == b) {
        heap[root] = arr[a];
        return heap[root];
    } else {
        int left = init(root<<1, a, (a+b)>>1);
        int right = init((root<<1)+1, ((a+b)>>1)+1, b);
        
        heap[root] = left&right;
        return heap[root];
    }
}

int query(int root, int a, int b, int x, int y) {
    if (x > b || y < a || (x > y)) { //out of / impossible range
        return AND_ID;
    } else if (a == x && y == b) { //intervals match
        return heap[root];
    } else {
        int ny = y, nx = x, mid = (a+b)>>1, lc = root<<1, rc = lc+1;
        if (ny > mid) ny = mid;
        if (nx < mid+1) nx = mid+1;
        int left = query(lc, a, mid, x, ny);
        int right = query(rc, mid+1, b, nx, y);
        
        return left&right;
    }
}

int main() {
    int test, n, k, s1, e1, s2, e2;
    scanf("%d", &test);
    while (test--) {
        scanf("%d %d", &n, &k);
        for (int i=0; i<n; i++) scanf("%d", &arr[i]);
        init(1, 0, n-1);
        if (((k<<1) + 1) >= n) {
            printf("%d", heap[1]);
            for (int i=1; i<n; i++) printf(" %d", heap[1]);
        } else {
            s1 = OUT, s2 = OUT, e1 = OUT, e2 = OUT;
            
            //s1 - e1
            s2 = -k+n;
            e2 = n-1;
            s1 = 0;
            e1 = k;
            printf("%d", query(1,0,n-1,s1,e1) & query(1,0,n-1,s2,e2));
            //printf("s1,e1,s2,e2 => [%d %d %d %d]", s1, e1, s2, e2);
            for (int i=1; i<n; i++) {
                s1 = OUT, s2 = OUT, e1 = OUT, e2 = OUT;
                
                //s1 - e1
                if (n-1 >= i+k) {
                    s1 = i-k;
                    if (s1 < 0) {
                        s2 = s1+n;
                        e2 = n-1;
                        s1 = 0;
                    }
                    e1 = i+k;
                } else {
                    s1 = i-k;
                    e1 = n-1;
                    s2 = 0;
                    e2 = i+k-n;
                }
                
                //printf("s1,e1,s2,e2 => [%d %d %d %d]", s1, e1, s2, e2);
                
                printf(" %d", query(1,0,n-1,s1,e1) & query(1,0,n-1,s2,e2));
            }
        }
        putchar('\n');
    }
    return 0;
}