#include<stdio.h>

#define MAXN 100005
#define LOGN 18
#define MAXINT (1<<30)

int array[LOGN][MAXN];
int g_min, g_cand;

void msort(int a, int b, int level) {
    if (a < b) {
        int mid = (a+b)>>1;
        msort(a, mid, level+1);
        msort(mid+1, b, level+1);
        
        int lp = a, rp = mid+1, p = a;
        
        while (lp <= mid && rp <= b) {
            if (array[level+1][lp] < array[level+1][rp]) {
                array[level][p] = array[level+1][lp];
                lp++;
            } else {
                array[level][p] = array[level+1][rp];
                rp++;
            }
            p++;
        }
        
        for (; lp<=mid; lp++) {
            array[level][p++] = array[level+1][lp];
        }
        
        for (; rp<=b; rp++) {
            array[level][p++] = array[level+1][rp];
        }
    } else {
        array[level][a] = array[0][a];
    }
}

int bsearch(int* arr, int key, int start, int end) {
    int u=start, v=end+1, c;
    
    while (u<v) {
        c = (u+v)>>1;
        if (key > arr[c]) {
            u = c+1;
        } else if (key < arr[c]) {
            v = c;
        } else {
            return c;
        }
    }
    return u;
}

void printAR(int* arr, int a, int b) {
    for (int i=a; i<=b; i++) printf("%d ", arr[i]);
    putchar('\n');
}

int query(int key, int a, int b, int x, int y, int level) {
    if (a == x && y == b) {
        int index = bsearch(array[level], key, a, b);
        //printf("array: ");
        //printAR(array[level], a, b);
        //printf("index=%d, key=%d, a=%d, b=%d\n", index, key, a, b);
        if (index <= b && index >= a) {
            if (g_min > array[level][index]) {
                //printf("g_min = %d\n", g_min);
                g_min = array[level][index];
            }
        }
        return index-a;
    } else if (x>b || y<a) {
        return 0;
    } else {
        int mid = (a+b)>>1;
        int xs = x, ys = y;
        if (xs <= mid) xs = mid+1;
        if (ys > mid) ys = mid;
        
        int left = query(key, a, mid, x, ys, level+1);
        int right = query(key, mid+1, b, xs, y, level+1);
        
        return left+right;
    }
}

void print_array(int a, int b, int level) {
    if (a == b) {
        printf("%3d ", array[level][a]);
    } else {
        for (int i=a; i<=b; i++) {
            printf("%3d ", array[level][i]);
        }
        putchar('\n');
        print_array(a, (a+b)/2, level+1);
        print_array((a+b)/2+1, b, level+1);
        putchar('\n');
    }
}

int main() {
    int n, m, i, j, k, u, v, c, ikey, val;
    scanf("%d %d", &n, &m);
    
    for (int i=0; i<n; i++) {
        scanf("%d", &array[0][i]);
    }
    
    msort(0,n-1,0);
    
    //print_array(0,n-1,0);
    
    while (m--) {
        scanf("%d %d %d", &i, &j, &k);
        
        u=0; v=n;
        while (u<v) {
            g_min = MAXINT;
            c = (u+v)>>1;
            ikey = array[0][c];
            val = query(ikey, 0, n-1, i-1, j-1, 0);
            //printf("val = %d, ikey=%d\n", val, ikey);
            if (k-1 > val) {
                u = c+1;
            } else if (k-1 < val) {
                v = c;
            } else {
                break;
            }
        }
        printf("%d\n", g_min);
    }
    return 0;
}