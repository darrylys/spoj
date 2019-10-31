#include<stdio.h>
#include<string.h>

#define N 1030
#define ll long long

int matrix[N][N];
int bag[N][N];

void init(int n) {
    for (int i=0; i<=n; i++) {
        memset(matrix[i], 0, (n+1)*sizeof(int));
        memset(bag[i], 0, (n+1)*sizeof(int));
    }
}

void updateCol(int row, int col, int val, int maxRow, int maxCol) {
    while (col <= maxCol) {
        matrix[row][col] = matrix[row][col] + val;
        col += (col & -col);
    }
}

void updateRow(int row, int col, int val, int maxRow, int maxCol) {
    int oldval = bag[row][col];
    while (row <= maxRow) {
        updateCol(row, col, val - oldval, maxRow, maxCol);
        row += (row & -row);
    }
}

void update(int row, int col, int val, int maxRow, int maxCol) {
    updateRow(row, col, val, maxRow, maxCol);
    bag[row][col] = val;
}

int find_sum_col(int r, int c) {
    int sum = 0;
    while (c > 0) {
        sum = sum + matrix[r][c];
        c -= (c & -c);
    }
    return sum;
}

int find_sum_row(int r, int c) {
    int sum = 0;
    while (r > 0) {
        sum = sum + find_sum_col(r,c);
        r -= (r & -r);
    }
    return sum;
}

//driver
int find_sum(int r, int c) {
    return find_sum_row(r,c);
}

//interface function
int findSum(int r1, int c1, int r2, int c2) {
    return find_sum(r2,c2) - find_sum(r2, c1-1) - find_sum(r1-1, c2) + find_sum(r1-1, c1-1); 
}

int main() {
    int test, r, c, r1, c1, r2, c2, n;
    int v;
    scanf("%d", &test);
    char cmd[5];
    while (test--) {
        scanf("%d", &n);
        init(n);
        while (1) {
            scanf("%s", cmd);
            if (cmd[0] == 'E') break;
            if (cmd[1] == 'E') { //set
                scanf("%d%d%d", &c, &r, &v);
                update(r+1, c+1, v, n, n);
            } else { //sum
                scanf("%d%d%d%d", &c1, &r1, &c2, &r2);
                printf("%d\n", findSum(r1+1,c1+1,r2+1,c2+1));
            }
        }
        printf("\n");
    }
    return 0;
}