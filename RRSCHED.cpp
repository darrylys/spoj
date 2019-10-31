#include<stdio.h>
#include<algorithm>

using namespace std;

#define LL long long int
#define MAXN 50005

int node[3*MAXN];
int arr[MAXN];
int ptr[MAXN];
int remap[MAXN];
LL finish_time[MAXN];

bool cmp(int a, int b) {
    if (arr[a]<arr[b]) return true;
    else if (arr[a]>arr[b]) return false;
    else return a<b;
}

void build(int root, int a, int b) {
    if (a == b) {
        node[root] = 1;
        remap[a] = root;
    } else {
        int lc=root<<1, mid=(a+b)>>1;
        
        build(lc, a, mid);
        build(lc+1, mid+1, b);
        
        node[root] = node[lc] + node[lc+1];
    }
}

void delete_task(int task_id) {
    int st = remap[task_id], lc, rc, mid;
    
    node[st] = 0;
    st >>= 1;
    
    while (st) {
        lc = st<<1;
        rc = lc+1;
        
        node[st] = node[lc] + node[rc];
        st >>= 1;
    }
}

int find_intv(int root, int a, int b, int x, int y) {
    if (a == x && b == y) {
        return node[root];
    } else if (x>y || y<a || x>b) {
        return 0;
    } else {
        int lc=root<<1, mid=(a+b)>>1, xs=x, ys=y;
        if (xs<mid+1)xs=mid+1;
        if (ys>mid) ys=mid;
        
        int left = find_intv(lc, a, mid, x, ys);
        int right= find_intv(lc+1, mid+1, b, xs, y);
        
        return left+right;
    }
}

void print_tree(int root, int a, int b, int space=0) {
    for (int i=0;i<space;i++) putchar(' ');
    printf("value=%d\n", node[root]);
    if (a!=b) {
        print_tree(root*2, a, (a+b)/2, space+3);
        print_tree(root*2+1, (a+b)/2+1, b, space+3);
    }
}

int main() {
    int n, time_decr, val, running_task, last;
    LL current_time;
    
    scanf("%d", &n);
    for (int i=0; i<n; ++i) {
        scanf("%d", &arr[i]);
        ptr[i] = i;
    }
    
    build(1,0, n-1);
    
    sort(ptr, ptr+n, cmp);
    
    time_decr = 0;              //cycles elapsed
    current_time = 0;
    running_task = n;           //number of currently running tasks
    for (int i=0, p=ptr[i];i<n; ) {
        
        repeat:
        
        //update first value
        val = arr[p]-time_decr;
        
        //if value==1, prev+1 else make n-1 cycles till value=1; (prev+1+back)
        if (val == 1) {
            int prev = find_intv(1, 0, n-1, 0, p-1);
            finish_time[p] = current_time+prev+1;
            //printf("1. worked on: %d, prev=%d, current_time=%d\n", arr[p], prev, current_time);
            current_time = finish_time[p];
        } else {
            time_decr += val-1;                     //doing val-1 cycles
            current_time = current_time + (LL)running_task*(val-1);
            //printf("2. worked on: %d, current_time=%d, time_decr=%d, running_task=%d, val=%d\n"
            //    , arr[p], current_time, time_decr, running_task, val);
            goto repeat;
        }
        
        delete_task(p);
        //printf("the tree:\n");
        //print_tree(1, 0, n-1);
        
        //putchar('\n');
        --running_task;
        ++i;
        if (i >= n) break;
        //complete the cycle (back part)
        p=ptr[i];
        
        val = arr[p]-time_decr;
        //printf("downval=%d\n", val);
        while (val == 1) {
            int prev = find_intv(1, 0, n-1, ptr[i-1]+1, ptr[i]-1);
            finish_time[p] = current_time+prev+1;
            current_time = finish_time[p];
            //printf("loop-current_time=%d\n", current_time);
            delete_task(p);
            //printf("the tree:\n");
            //print_tree(1, 0, n-1);
            
            //putchar('\n');
            --running_task; ++i; p=ptr[i]; 
            if (i >= n) break;
            val = arr[p]-time_decr;
            //printf("p=%d\n", p);
        }
        
        int back = find_intv(1, 0, n-1, ptr[i-1]+1, n-1);
        current_time += back;
        //printf("down current_time = %d, back=%d\n", current_time, back);
        ++time_decr;
        
        
    }
    
    for (int i=0; i<n; ++i) {
        printf("%lld\n", finish_time[i]);
    }
    return 0;
}