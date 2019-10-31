//complexity: O(n log^2 n)
//idea: modifying mergesort

#include<stdio.h>

#define MAXN 100010
#define LOGN 18
#define MAXINT 2147483647
#define MIN3(a,b,c) min(a,min(b,c))

int array[LOGN][MAXN];

int min(int a, int b) {
    return (a<b)?a:b;
}

int max(int a, int b) {
    return (a>b)?a:b;
}

int bsearch(int* arr, int a, int b, int p, int k) {
    int u=a, v=b+1, c;
    
    while (u<v) {
        c = (u+v)>>1;
        if (k > arr[c]) {
            u = c+1;
        } else if (k < arr[c]) {
            v = c;
        } else {
            return c;
        }
    }
    return u-1;
}

int bsearch_left(int* arr, int a, int b, int p, int k, int val) {
    int u=a, v=b+1, c;
    
    while (u<v) {
        c = (u+v)>>1;
        if (k < val-arr[c]+p) {
            u = c+1;
        } else if (k > val-arr[c]+p) {
            v = c;
        } else {
            return c;
        }
    }
    return u-1;
}


int solver(int a, int b, int p, int k, int level) {
    if (a == b) {
        array[level][a] = array[0][a];
        return -1;
    } else {
        int mid = (a+b)>>1, border, ls, rs, minv = MAXINT;
        int left = solver(a, mid, p, k, level+1);
        int right = solver(mid+1, b, p, k, level+1);
        
        //for (int i=a; i<=b; i++) {
        //    printf("%d ", array[level+1][i]);
        //}
        //putchar('\n');
        
        for (int i=mid+1; i<=b; i++) {
            
            //find border
            border = bsearch(array[level+1], a, mid, p, array[level+1][i]);
            
            //find smallest value atleast k in left side
            ls = bsearch_left(array[level+1], a, border, 0, k, array[level+1][i]);
            //ls--;
            
            //find smallest value atleast k in right side
            rs = bsearch_left(array[level+1], border+1, mid, p, k, array[level+1][i]);
            //rs--;
            
            //printf("a=%d, b=%d, border=%d, ls=%d, rs = %d, ", a, b, border, ls, rs);
            
            ls = min((ls>=a && ls<=border)?array[level+1][i]-array[level+1][ls]:MAXINT, 
                (rs>border && rs<=mid)?array[level+1][i]-array[level+1][rs]+p:MAXINT);
            
            //printf("new ls=%d\n", ls);
            
            if (minv > ls) minv = ls;
        }
        
        //putchar('\n');
        
        //merge (using mergesort)
        int lp = a, rp = mid+1, pt = a;
        
        while (lp <= mid && rp <= b) {
            if (array[level+1][lp] < array[level+1][rp]) {
                array[level][pt] = array[level+1][lp];
                lp++;
            } else {
                array[level][pt] = array[level+1][rp];
                rp++;
            }
            pt++;
        }
        
        for (; lp<=mid; lp++) {
            array[level][pt++] = array[level+1][lp];
        }
        
        for (; rp<=b; rp++) {
            array[level][pt++] = array[level+1][rp];
        }
        
        if (left < 0 && right < 0) return minv;
        if (left < 0) return min(right, minv);
        if (right < 0) return min(left, minv);
        return MIN3(left, right, minv);
    }
}

int main() {
    int test, n, k, p, r, a, sum, minv = MAXINT;
    scanf("%d", &test);
    
    while (test--) {
        scanf("%d %d %d", &n, &k, &p);
        sum = 0;
        array[0][0] = 0;
        for (int i=0; i<n; i++) {
            scanf("%d", &a);
            //sum += a;
            //sum %= p;
            array[0][i+1] = (array[0][i] + a)%p;
            //if (sum >= k) minv = min(sum, minv);
            //printf("%d ", sum);
        }
        //putchar('\n');
        
        r = solver(0, n, p, k, 0);
        //printf("%d\n", min(minv,r));
        printf("%d\n", r);
    }
    return 0;
}