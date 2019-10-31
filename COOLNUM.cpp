
#include<stdio.h>
#include<math.h>

int scf[1000];

int bsearch(int* arr, int key, int end) {
    int u=0, v=end, c;
    while (1) {
        c = (u+v)/2;
        if (u>=v) {
            return u-1;
        }
        if (key > arr[c]) {
            u=c+1;
        } else if (key < arr[c]) {
            v = c;
        } else {
            return c;
        }
    }
}

int main() {
    int f=0;
    for (int i=1; i*i*i<=100000000; ++i) {
        int sq = (int)floor(sqrt(i*i*i));
        if (sq*sq == i*i*i) {
            scf[f++] = sq*sq;
            //printf("%d ", sq*sq);
        }
    }
    //printf("\n");
    int a, b;
    scanf("%d%d", &a, &b);
    //int lb = bsearch(scf, a, f);
    //int ub = bsearch(scf, b, f);
    //printf("lb=%d, ub=%d\n", lb, ub);
    //printf("%d\n", ub-lb+1);
    int count = 0;
    for (int i=0; i<f; ++i) {
        if (scf[i] >= a && scf[i] <= b) {
            count++;
        }
    }
    printf("%d\n", count);
}


/*
N = x^2 && y^3
max x = 10^4
max y ~= 10^3

x^2 = y^3

loop.
y -> check y^3, find x^2.
put in container.

binary search!
*/