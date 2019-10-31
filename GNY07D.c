#include<stdio.h>

char mtr[25][25];
char smpl[25][25];
char bin[5];
char result[90];


char tochar(char* bin) {
    int i=5, mul=1, result=0;
    while (i--) {
        result+=(bin[i]-'0')*mul;
        mul*=2;
    }
    if (result==0) return ' ';
    else return result+'A'-1;
}

int main() {
    int N, R, C;
    scanf("%d",&N);
    int i, j, k, limxright, limyup, x, y, limxleft, limydown, cntr=1;
    int first;
    
    while (N--) {
        scanf("%d%d",&R,&C);
        i=j=k=0;
        getchar();
        while (i<R*C) {
            mtr[j][k] = getchar();
            k++;
            if (k==C) {
                j++;
                k=0;
            }
            i++;
        }
        for (i=0;i<R;i++)
            for (j=0;j<C;j++) smpl[i][j] = '-';
        limxright = C;
        limydown = R;
        limxleft=-1;
        limyup=-1;
        k=0;i=0;j=0;x=0;y=0;
        first = 1;
        while (k<R*C-(R*C)%5) {
            for (i=0;i<5;i++) {
                bin[i] = mtr[y][x];
                smpl[y][x] = 'x';
                if ((y==0 || smpl[y-1][x] != '-') && (x+1 != C && smpl[y][x+1] == '-')) {
                    x+=1;
                } else if ((x+1 == C || smpl[y][x+1] != '-') && (y+1 != R && smpl[y+1][x] == '-')) {
                    y+=1;
                } else if ((y+1==R || smpl[y+1][x] != '-') && (x-1 >= 0 && smpl[y][x-1] == '-')) {
                    x-=1;
                } else {
                    y-=1;
                }
                k++;
            }
            result[j++] = tochar(bin);
        }
        result[j] = '\0';
        for (i=j-1;j>=0;i--) {
            if (result[i]!=' ') break;
        }
        result[i+1] = '\0';
        printf("%d %s\n", cntr++, result);
    }
    return 0;
}

