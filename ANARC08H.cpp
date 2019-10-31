#include<cstdio>

#define N 1000005

int heaptree[N*3];
int heapmap[N];

void make_tree(int root, int a, int b) {
    heaptree[root] = 0;
    if (a == b) {
        heapmap[a] = root;
    } else {
        make_tree(root<<1, a, (a+b)/2);
        make_tree((root<<1) + 1, (a+b)/2+1, b);
    }
}

int get_index(int root, int a, int b, int x) {
    
    int start = a;
    int end = b;
    int mid;
    int idx = x;
    
    while (start != end) {
        mid = (start+end)/2;
        
        if (idx + heaptree[root*2] > mid) {
            idx += heaptree[root*2];
            root = (root<<1)+ 1;
            start = mid+1;
        } else {
            root <<= 1;
            end = mid;
        }
    }
    return idx;
}

void update_tree(int start) {
    while (start > 0) {
        heaptree[start]++;
        start /= 2;
    }
}

int solve(int n, int d) {
    make_tree(1, 0, n-1);
    
    int r = 0;
    int idx;
    for (int i=n; i>=2; i--) {
        r = (r+d-1)%i;
        
        idx = get_index(1, 0, n-1, r);
        update_tree(heapmap[idx]);
    }
    
    for (int i=0; i<n; i++) {
        if (!heaptree[heapmap[i]]) {
            return i+1;
        }
    }
}

int main() {
    int n, d, r;
    
    while (scanf("%d %d", &n, &d) && (n+d)) {
        r = solve(n,d);
        printf("%d %d %d\n", n, d, r);
    }
    return 0;
}