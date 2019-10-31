#include<stdio.h>
#include<algorithm>

using namespace std;

#define MAXN 100010

int remap[MAXN];
int s[MAXN];
int h[MAXN];
int r[MAXN];
int node[3*MAXN];

void build_tree(int root, int a, int b) {
    if (a==b) {
        node[root] = 0;
        remap[a] = root;
    } else {
        int lc = root<<1, rc=lc+1, mid = (a+b)>>1;
        build_tree(lc,a,mid);
        build_tree(rc,mid+1,b);
        
        node[root] = 0;
    }
}

void update(int idx) {
    int id = remap[idx];
    
    while (id > 0) {
        node[id]++;
        //printf("id=%d, node[id]=%d\n", id, node[id]);
        id >>= 1;
    }
}

int get_item_index(int root, int a, int b, int id) {
    int st = root;
    int index = id;
    int lc, rc, mid;
    
    while (a < b) {
        mid = (a+b)>>1;
        lc = st<<1;
        
        if (node[lc] + index <= mid) {
            b = mid;
            st = lc;
        } else {
            index += node[lc];
            a = mid+1;
            st = lc+1;
        }
    }
    
    return index;
}

int getItemIndex(int id, int n) {
    return get_item_index(1,0,n-1,id); //play in zero-based array
}

void print_tree(int root, int a, int b, int space) {
    if (a == b) {
        while (space--) putchar(' ');
        printf("[a,b,value,remap] => [%d,%d,%d,%d]\n", a,b,node[root],remap[a]);
    } else {
        for (int i=0;i<space;i++) putchar(' ');
        printf("[a,b,value] => [%d,%d,%d]\n", a,b,node[root]);
        print_tree(root<<1, a, (a+b)/2, space+4);
        print_tree(root*2+1, (a+b)/2+1, b, space+4);
    }
}

int main() {
    int n, index;
    scanf("%d", &n);
    for (int i=0;i<n;i++) {
        scanf("%d", &h[i]);
    }
    sort(h, h+n);
    
    for (int i=0;i<n;i++) {
        scanf("%d", &s[i]);
    }
    
    build_tree(1,0,n-1);
    
    for (int i=n-1; i>=0; i--) {
        index = getItemIndex(s[i], n);
        r[i] = h[index];
        update(index);
        //printf("index=%d\n", index);
        //print_tree(1,0,n-1,0);
        //putchar('\n');
    }
    
    for (int i=0; i<n; i++) {
        printf("%d\n", r[i]);
    }
    return 0;
}