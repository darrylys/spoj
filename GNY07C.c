#include<stdio.h>
#include<string.h>

char matrix[25][25];
char str[90];
char bin[5];

void tobin(int val, char* bin) {
    int i=5;
    while (i--) {
        bin[i] = (val&0x01)+'0';
        val>>=1;
    }
}

int main() {
    int N, R, C, i, j, len, x, y,cntr=1;

    scanf("%d",&N);
    while (N--) {
        scanf("%d%d",&R,&C);
        getchar();
        gets(str);
        len = strlen(str);
        for (i=0;i<R;i++)
            for (j=0;j<C;j++) matrix[i][j] = '-';
        x=0;
        y=0;
        for (i=0;i<len;i++) {
            if (str[i] == ' ')
                tobin(0, bin);
            else
                tobin(str[i]-'A'+1, bin);
            for (j=0;j<5;j++) {
                matrix[y][x] = bin[j];
                if ((y==0 || matrix[y-1][x] != '-') && (x+1 != C && matrix[y][x+1] == '-')) {
                    x+=1;
                } else if ((x+1 == C || matrix[y][x+1] != '-') && (y+1 != R && matrix[y+1][x] == '-')) {
                    y+=1;
                } else if ((y+1==R || matrix[y+1][x] != '-') && (x-1 >= 0 && matrix[y][x-1] == '-')) {
                    x-=1;
                } else {
                    y-=1;
                }
            }
        }
        printf("%d ", cntr++);
        for (i=0;i<R;i++)
            for (j=0;j<C;j++) {
                if (matrix[i][j]=='-') putchar('0');
                else putchar(matrix[i][j]);
            }
        putchar('\n');
    }
    return 0;
}

