#include<cstdio>
#include<queue>
#define N 15

using namespace std;
int way[N][N];
char table[N][N];

int main() {
    int n;
    scanf("%d",&n);
    getchar();
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            table[i][j] = getchar();
        }
        getchar();
    }
    way[0][0] = 1;
    queue<int> xs;
    queue<int> ys;
    xs.push(0); ys.push(0);
    while (!xs.empty()) {
        int x = xs.front();
        int y = ys.front();
        xs.pop(); ys.pop();
        if (table[y][x] == '0') continue;
        if (y+table[y][x]-'0' < n) {
            way[y+table[y][x]-'0'][x]++;
            xs.push(x);
            ys.push(y+table[y][x]-'0');
        }
        if (x+table[y][x]-'0' < n) {
            way[y][x+table[y][x]-'0']++;
            xs.push(x+table[y][x]-'0');
            ys.push(y);
        }
    }
    printf("%d", way[n-1][n-1]);
    return 0;
}
