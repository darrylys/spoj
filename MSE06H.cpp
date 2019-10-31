#include<stdio.h>
#include<string.h>
#include<cctype>

#define MAXN 1005
#define MAXM 1005
#define MAXK 1000005

int matrix[MAXN][MAXM]; //nxm
int edge[MAXK][2];

void mark(int r, int c, int maxRow, int maxCol) {
    int row = r, col = c;
    
    while (row <= maxRow) {
        col = c;
        
        while (col <= maxCol) {
            ++matrix[row][col];
            col += (col & -col);
        }
        
        row += (row & -row);
    }
}

int find_sum(int r, int c) {
    int row = r, col = c, sum = 0;
    
    while (row > 0) {
        col = c;
        
        while (col > 0) {
            sum += matrix[row][col];
            col -= (col & -col);
        }
        
        row -= (row & -row);
    }
    return sum;
}

int count(int r1, int c1, int r2) {
    return find_sum(r2, c1) - find_sum(r1-1, c1);
}

int getint() {
    int n=0;
    char c;
    while(!isdigit(c=getchar()));
    while(isdigit(c)){
        n=n*10+(c-'0');
        c=getchar();
    }
    return n;
}

int main() {
    int test, n, m, k, a, b, cntr=0;
    long long int sum;
    
    test = getint();
    
    while (test--) {
        n = getint();
        m = getint();
        k = getint();
        
        for (int i=1; i<=n; ++i) {
            memset(matrix[i], 0, (m+1)*sizeof(int));
        }
        
        //scanf("%d %d %d", &n, &m, &k);
        
        for (int i=0; i<k; ++i) {
            //scanf("%d %d", &a, &b);
            a = getint();
            b = getint();
            mark(a, b, n, m);
            edge[i][0] = a;
            edge[i][1] = b;
        }
        
        sum = 0;
        for (int i=0; i<k; i++) {
            sum = sum + count(edge[i][0]+1, edge[i][1]-1, n);
        }
        printf("Test case %d: %lld\n", ++cntr, sum);
    }
    return 0;
}