#include<cstdio>
#include<algorithm>

#define MAX2 0
#define MAX1 1 
#define N 100002

using namespace std;

int heap[N*3][2];
int arr[N];
int heapremap[N];

void rundex(int root, int* arrv) {
    
    int m = -1;
    int id = 0;
    for (int i=0; i<4; i++) {
        if (arrv[i] > m) {
            m = arrv[i];
            id = i;
        }
    }
    
    heap[root][MAX1] = m;
    arrv[id] = -1;
    
    m=-1;
    id=0;
    for (int i=0; i<4; i++) {
        if (arrv[i] > m) {
            m = arrv[i];
            id = i;
        }
    }
    heap[root][MAX2] = m;
}

void make_tree(int root, int a, int b) {
    if (a == b) {
        heap[root][MAX1] = arr[a];
        heap[root][MAX2] = -1;
        heapremap[a] = root;
    } else {
        make_tree(root*2, a, (a+b)/2);
        make_tree(root*2+1, (a+b)/2+1, b);
        
        int arrx[4];
        arrx[0] = heap[root*2][MAX1];
        arrx[1] = heap[root*2][MAX2];
        
        arrx[2] = heap[root*2+1][MAX1];
        arrx[3] = heap[root*2+1][MAX2];
        
        rundex(root, arrx);
    }
}

void findQuery(int root, int a, int b, int x, int y, int& max1, int& max2) {
    if (y<a || x>b || x>y) { //range invalid
        max1 = -1;
        max2 = -1;
    } else if (x == a && y == b) { //match range
        max1 = heap[root][MAX1];
        max2 = heap[root][MAX2];
    } else {
        int arry[4];
        int mid = (a+b)/2;
        int xs=x, ys=y;
        
        if (xs <= mid) xs = mid+1; 
        if (ys > mid) ys = mid;
        
        findQuery(root*2, a, mid, x, ys, arry[0], arry[1]);
        findQuery(root*2+1, mid+1, b, xs, y, arry[2], arry[3]);
        
        int m = -1;
        int id = 0;
        for (int i=0; i<4; i++) {
            if (arry[i] > m) {
                m = arry[i];
                id = i;
            }
        }
        
        max1 = m;
        arry[id] = -1;
        
        m=-1;
        id=0;
        for (int i=0; i<4; i++) {
            if (arry[i] > m) {
                m = arry[i];
                id = i;
            }
        }
        max2 = m;
    }
}

void updateQuery(int start, int nv) {
    
    heap[start][MAX1] = nv;
    int arrx[4];
    while (start > 1) {
        
        arrx[0] = heap[(start/2)*2][MAX1];
        arrx[1] = heap[(start/2)*2][MAX2];
        
        arrx[2] = heap[(start/2)*2+1][MAX1];
        arrx[3] = heap[(start/2)*2+1][MAX2];
        
        rundex(start/2, arrx);
        
        start /= 2;
    }
}

void display_tree(int root, int a, int b) {
    printf("<%d-%d>\n", heap[root][MAX1], heap[root][MAX2]);
    if (a!=b) {
        //printf("<%d-%d>\n", heap[root][MAX1], heap[root][MAX2]);
        display_tree(root*2, a, (a+b)/2);
        display_tree(root*2+1, (a+b)/2+1, b);
    }
}

int main() {
    int n, q, x, y, m1, m2;
    char c;
    scanf("%d", &n);
    for (int i=0; i<n; i++) {
        scanf("%d", &arr[i]);
    }
    make_tree(1, 0, n-1);
    
    scanf("%d", &q);
    getchar();
    while (q--) { 
        scanf("%c %d %d", &c, &x, &y);
        if (c == 'Q') {
            findQuery(1, 0, n-1, x-1, y-1, m1, m2);
            printf("%d\n", m1+m2);
        } else {
            updateQuery(heapremap[x-1], y);
            //printf("heapmap=%d\n", heapremap[x-1]);
        }
        getchar();
    }
    return 0;
}
