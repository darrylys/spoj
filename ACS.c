#include<stdio.h>
#define COL 5679
#define ROW 1235

int colperm[COL];
int rowperm[ROW];
int colrev[COL];
int rowrev[ROW];

int swap(int* arr, int* rev, int a, int b) {
    int temp;

    temp = rev[arr[a]];
    rev[arr[a]] = rev[arr[b]];
    rev[arr[b]] = temp;

    temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

int main() {
    int i, j, x, y, nx, ny, res, z;
    for (i=1;i<ROW; i++) rowperm[i] = rowrev[i] = i;
    for (i=1;i<COL; i++) colperm[i] = colrev[i] = i;

    char c;
    while ((c=getchar())!=EOF) {
        switch (c) {
            case 'R':
                scanf(" %d %d", &x, &y);
                swap(rowperm, rowrev, x, y);
            break;

            case 'C':
                scanf(" %d %d", &x, &y);
                swap(colperm, colrev, x, y);
            break;

            case 'Q':
                scanf(" %d %d", &x, &y);
                res = (rowperm[x]-1)*(COL-1)+colperm[y];
                printf("%d\n", res);
            break;

            case 'W':
                scanf(" %d", &z);
                int row = (z-1)/(COL-1);
                int col = (z-1)-(row)*(COL-1);
                row++;
                col++;
                printf("%d %d\n", rowrev[row], colrev[col]);
            break;

            default:
            break;
        }
    }
    return 0;
}
