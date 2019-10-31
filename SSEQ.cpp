#include<stdio.h>
#include<cctype>

#define N 200005

int heapmap[N];
int value[N];
int ans[N];
int heap[N*3];
char mstack[15];

int getint() {
    char c = getchar();
    int n = 0;
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') {
        n = n*10 + c-'0';
        c=getchar();
    }
    return n;
}

void printint(int n) {
    if (n == 0) {
        putchar('0');
        return;
    }
    int p=0;
    while (n) {
        mstack[p++] = n%10;
        n/=10;
    }
    while (p--) {
        putchar(mstack[p]+'0');
    }
}

void make_heap(int root, int a, int b) {
    if (a == b) {
        heap[root] = 0;
        heapmap[a] = root;
    } else {
        int lc = root<<1, mid=(a+b)>>1;
        make_heap(lc, a, mid);
        make_heap(lc+1, mid+1, b);
        heap[root] = 0;
    }
}

void update(int index) {
    int tr = heapmap[index];
    while (tr) {
        ++heap[tr];
        tr>>=1;
    }
}

int get_val(int root, int a, int b, int pos) {
    int st = root;
    int mid, lc;
    
    while (a < b) {
        mid = (a+b)>>1;
        lc = st<<1;
        
        if (heap[lc] + pos <= mid) {
            st = lc;
            b = mid;
        } else {
            pos += heap[lc];
            st = lc+1;
            a = mid+1;
        }
    }
    
    return pos;
}

int main() {
    int t, n, pos;
    t = getint();
    while (t--) {
        n = getint();
        for (register int i=0; i<n; ++i) {
            value[i] = getint();
        }
        make_heap(1, 0, n-1);
        
        for (register int i=n-1; i>=0; --i) {
            pos = get_val(1,0,n-1,i-value[i]);
            update(pos);
            ans[i] = pos+1;
        }
        
        printint(ans[0]);
        for (register int i=1; i<n; ++i) {
            putchar(' ');
            printint(ans[i]);
        }
        putchar('\n');
    }
    return 0;
}
