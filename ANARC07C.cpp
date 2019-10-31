#include<stdio.h>

#define MAXN 1005

int ring[MAXN][MAXN];
int copy[4*MAXN];

int getint() {
    char c = getchar(); int n = 0;
    
    while (c < '0' || c > '9') c = getchar();
    while (c >= '0' && c <= '9') {
        n = n*10 + c-'0';
        c = getchar();
    }
    return n;
}

//num = ring_number zero based.
bool check_ring(int n, int num, int starting_number) {
    
    int rsl = n - 2*num, c = 0;
    int row = num;
    int col = num;
    int startpos;
    
    if (rsl == 1) {     //one ring case
        if (ring[row][col] == n*row + col + 1) {
            return true;
        } else {
            return false;
        }
    }
    
    //copy and find
    //topside
    for (int i=col+1; i<col+rsl; ++i) {
        copy[c++] = ring[row][i];
    }
    
    //rightside
    for (int i=row+1; i<row+rsl; ++i) {
        copy[c++] = ring[i][col+rsl-1];
    }
    
    //downside
    for (int i=col+rsl-2; i>=col; --i) {
        copy[c++] = ring[row+rsl-1][i];
    }
    
    //leftside
    for (int i=row+rsl-2; i>=row; --i) {
        copy[c++] = ring[i][col];
    }
    
    /*for (int i=0; i<c; ++i) {
        printf("%d ", copy[i]);
    }
    
    putchar('\n');*/
    
    startpos = -1;
    for (int i=0; i<c; ++i) {
        if (copy[i] == starting_number) {
            startpos = i;
            break;
        }
    }
    
    //printf("startpos = %d\n", startpos);
    
    if (startpos == -1) return false;
    
    //printf("----\n");
    
    int next, now;
    //trace for top (must increment by 1)
    for (int i=1; i<rsl; ++i) {
        next = (i+startpos)%c;
        now = (i-1+startpos)%c;
        
        if (copy[next] != copy[now]+1) {
            return false;
        }
    }
    
    //printf("----\n");
    
    //trace right side (must increment by n)
    startpos = next;
    for (int i=1; i<rsl; ++i) {
        next = (i+startpos)%c;
        now = (i-1+startpos)%c;
        
        if (copy[next] != copy[now]+n) {
            return false;
        }
    }
    
    //printf("----\n");
    
    //trace under side (must dec by 1)
    startpos = next;
    for (int i=1; i<rsl; ++i) {
        next = (i+startpos)%c;
        now = (i-1+startpos)%c;
        
        if (copy[next] != copy[now]-1) {
            return false;
        }
    }
    
    //printf("----\n");
    
    //trace left side (must dec by n)
    startpos = next;
    for (int i=1; i<rsl; ++i) {
        next = (i+startpos)%c;
        now = (i-1+startpos)%c;
        
        if (copy[next] != copy[now]-n) {
            return false;
        }
    }
    
    //printf("----end\n");
    
    return true;
}

int main() {
    int test = 1;
    
    int n, nor; bool result;
    int starting_number;
    
    while (true) {
        n = getint();
        if (n == 0) break;
        for (int i=0; i<n; ++i) {
            for (int j=0; j<n; ++j) {
                ring[i][j] = getint();
            }
        }
        
        if (n == 1) {
            printf("%d. NO\n", test++);
            continue;
        }
        
        if (n&1) {
            nor = n/2;
        } else {
            nor = n/2-1;
        }
        
        result = true;
        starting_number = 1;
        for (int i=0; result && i<=nor; ++i) {
            result &= check_ring(n, i, starting_number);
            starting_number += n+1;
        }
        
        printf("%d. %s\n", test++, result ? "YES" : "NO");
    }
    
    return 0;
}