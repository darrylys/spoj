#include<cstdio>
#define N 5000
#define MOD 1988

int table[N+2][N+2];

void buildTable() {
    //inits
    table[1][1] = table[2][2] = table[3][3] = 1;
    table[2][1] = table[3][1] = table[3][2] = 1;

    //building
    for (int i=4; i<=N; i++) {
        table[i][1] = 1;
        table[i][2] = i/2;
        for (int j=3; j<i; j++) {
            table[i][j] = table[i-1][j-1] + table[i-j][j];
            table[i][j] %= MOD;
        }
        table[i][i] = 1;
    }
}

void printTable() {
    for (int i=1; i<=N; i++) {
        for (int j=1; j<=N; j++) {
            printf("%3d ", table[i][j]);
        }
        putchar('\n');
    }
}

int main() {
    buildTable();
    //printTable();
    int a, b;
    while (scanf("%d%d",&a,&b) && a) {
        printf("%d\n", table[a][b]);
    }
    return 0;
}
