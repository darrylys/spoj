// impl BFS

#include<cstdio>
#include<queue>
#define N 200

using namespace std;
char field[N][N];
int score[N][N];
bool checked[N][N];

int dir[4][2] = {{0,1},{0,-1},{-1,0},{1,0}};

int main() {
    int test, row, col, x, y, xp, yp;
    queue<int> xs,ys;
    scanf("%d",&test);
    while(test--) {
        scanf("%d%d",&row,&col);
        getchar();
        for (int i=0; i<row; i++) {
            for (int j=0; j<col; j++) {
                score[i][j] = 0;
                checked[i][j] = false;
            }
        }
        for (int i=0;i<row;i++) {
            for (int j=0;j<col;j++) {
                field[i][j] = getchar();
                if (field[i][j] == '1') {
                    xs.push(j);
                    ys.push(i);
                    checked[i][j] = true;
                    score[i][j] = 0;
                }
            }
            getchar();
        }
/*
        printf("checked = \n");
        for (int i=0;i<row;i++) {
            for (int j=0;j<col;j++) {
                printf("%d", checked[i][j]);
            }
            putchar('\n');
        }

        printf("score = \n");
        for (int i=0;i<row;i++) {
            for (int j=0;j<col;j++) {
                printf("%d", score[i][j]);
            }
            putchar('\n');
        }
*/
        while (!xs.empty()) {
            x = xs.front();
            y = ys.front();
            xs.pop(); ys.pop();
            for (int i=0;i < 4; i++) {
                xp = x + dir[i][0];
                yp = y + dir[i][1];
                if (xp >= 0 && xp < col && yp >= 0 && yp < row &&
                    !checked[yp][xp]) {
                    checked[yp][xp] = true;
                    score[yp][xp] = score[y][x] + 1;
                    xs.push(xp); ys.push(yp);
                }
            }
        }

        for (int i=0; i<row; i++) {
            printf("%d",score[i][0]);
            for (int j=1; j<col; j++) {
                printf(" %d", score[i][j]);
            }
            putchar('\n');
        }
    }
    return 0;
}
