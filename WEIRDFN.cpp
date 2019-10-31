#include<stdio.h>

#define N 201000
#define MAXINT (1<<30)
#define MININT -MAXINT
#define ll long long
#define MOD 1000000007

int leftheap[N];        //maxheap
int rightheap[N];       //minheap
int sizel;
int sizer;

void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

void insertBeforeMedian(int val) {
    leftheap[sizel] = val;
    
    int pos = sizel;
    
    while (pos > 0) {
        
        if (val > leftheap[pos>>1]) {
            leftheap[pos] = leftheap[pos>>1];
            pos >>= 1;
        } else {
            leftheap[pos] = val;
            break;
        }
    }
    sizel++;
}

int takeMax() {
    int ret = leftheap[1];
    
    int next;
    int now = 1;
    int currval = leftheap[sizel-1];
    leftheap[1] = currval;
    int i;
    int max;
    while (true) {
        i = now;
        max = MININT;
        
        if (leftheap[i] > max) {
            max = leftheap[i];
            next = i;
        }
        
        if ((i<<1) < sizel) {
            if (leftheap[i<<1] > max) {
                max = leftheap[i<<1];
                next = i<<1;
            }
        }
        
        if ((i<<1)+1 < sizel) {
            if (leftheap[(i<<1)+1] > max) {
                max = leftheap[(i<<1)+1];
                next = (i<<1)+1;
            }
        }
        
        if (next == now) {
            break;
        }
        
        swap(leftheap[now], leftheap[next]);
        now = next;
    }
    
    sizel--;
    
    return ret;
}

void insertAfterMedian(int val) {
    rightheap[sizer] = val;
    
    int pos = sizer;
    
    while (pos > 0) {
        
        if (val < rightheap[pos>>1]) {
            rightheap[pos] = rightheap[pos>>1];
            pos >>= 1;
        } else {
            rightheap[pos] = val;
            break;
        }
    }
    sizer++;
}

int takeMin() {
    int ret = rightheap[1];
    
    int next;
    int now = 1;
    int currval = rightheap[sizer-1];
    rightheap[1] = currval;
    int i;
    int min;
    while (true) {
        i = now;
        min = MAXINT;
        
        if (rightheap[i] < min) {
            min = rightheap[i];
            next = i;
        }
        
        if ((i<<1) < sizer) {
            if (rightheap[i<<1] < min) {
                min = rightheap[i<<1];
                next = i<<1;
            }
        }
        
        if ((i<<1)+1 < sizer) {
            if (rightheap[(i<<1)+1] < min) {
                min = rightheap[(i<<1)+1];
                next = (i<<1)+1;
            }
        }
        
        if (next == now) {
            break;
        }
        
        swap(rightheap[now], rightheap[next]);
        now = next;
    }
    
    sizer--;
    
    return ret;
}

int main() {
    leftheap[0] = MAXINT;
    rightheap[0] = MININT;
    sizel = 1;
    sizer = 1;
    
    int testcase;
    scanf("%d", &testcase);
    ll sum;
    int median;
    int f, a, b, c, n;
    while (testcase--) {
        scanf("%d %d %d %d\n", &a, &b, &c, &n);
        sizel = sizer = 1;
        sum = 1;
        median = 1;
        insertBeforeMedian(1);
        
        for (int i=2; i<=n; i++) {
            f = (int)(((ll)a*median + (ll)b*i + (ll)c)%MOD);
            sum = sum + f;
            
            if (f >= median) {
                insertAfterMedian(f);
            } else {
                insertBeforeMedian(f);
            }
            
            if (!(sizel == sizer || sizel == sizer+1)) {
                if (sizel > sizer) {
                    int r = takeMax();
                    insertAfterMedian(r);
                    median = leftheap[1];
                } else {
                    int r = takeMin();
                    insertBeforeMedian(r);
                    median = leftheap[1];
                }
            }
        }
        
        printf("%lld\n", sum);
    }
    
    return 0;
}