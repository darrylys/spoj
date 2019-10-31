// impl Complete-Search/Brute Force

#include<cstdio>
#define HANSEL 0
#define GRETEL 1
#define DRAW 2

int score[3];
char field[205][205];

int winner(int row, int col, int k) {
    char now = 'o';
    int turn = GRETEL;

    int combo;

    run:
    //horz
    if (col >= k) {
        for (int i=0; i<row; i++) {
            combo = 0;
            for (int j=0; j<col; j++) {
                if (field[i][j] == now) {
                    combo++;
                } else combo = 0;
                if (combo == k) return turn;
            }
        }
    }

    //vertz
    if (row >= k) {
        for (int i=0; i<col; i++) {
            combo = 0;
            for (int j=0; j<row; j++) {
                if (field[j][i] == now) {
                    combo++;
                } else combo = 0;
                if (combo == k) return turn;
            }
        }
    }

    //diagonals
    if (col >= k && row >= k) {
        //left-right
        //to-left
        for (int i=col-k; i>=0; i--) {
            int nowc = i;
            combo = 0;
            for (int j=0; nowc < col && j<row;j++, nowc++) {
                if (field[j][nowc] == now) combo++;
                else combo = 0;
                if (combo == k) return turn;
            }
        }

        //to-down
        for (int i=0; i<=row-k; i++) {
            int nowr = i;
            combo = 0;
            for (int j=0; j < col && nowr < row;j++, nowr++) {
                if (field[nowr][j] == now) combo++;
                else combo = 0;
                if (combo == k) return turn;
            }
        }

        //right-left
        for (int i=k-1; i<col; i++) {
            int nowc = i;
            combo = 0;
            for (int j=0; nowc >=0 && j < row;j++, nowc--) {
                if (field[j][nowc] == now) combo++;
                else combo = 0;
                if (combo == k) return turn;
            }
        }

        //to-down
        for (int i=0; i<=row-k; i++) {
            int nowr = i;
            combo = 0;
            for (int j=col-1; j >= 0 && nowr < row;j--, nowr++) {
                if (field[nowr][j] == now) combo++;
                else combo = 0;
                if (combo == k) return turn;
            }
        }
    }

    if (turn == GRETEL) {
        turn = HANSEL;
        now = 'x';
        goto run;
    }
    return DRAW;
}

int main() {
    int l, col, row, k;
    scanf("%d",&l);
    while(l--) {
        scanf("%d %d %d",&col,&row,&k);
        for (int i=0;i<row;i++) {
            scanf("%s",field[i]);
        }
        score[winner(row,col,k)]++;
    }
    printf("%d:%d\n", score[HANSEL], score[GRETEL]);
    return 0;
}
