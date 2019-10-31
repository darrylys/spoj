#include<cstdio>

int getsum(int a) {
    int res = 0;
    int sgn = 1;
    int temp;
    int arr[10], cntr;
    for (int i=1; i<=a; i++) {
        temp = i;
        cntr=0;
        while (temp > 0) {
            arr[cntr++] = temp%10;
            temp /= 10;
        }
        for (int j=cntr-1; j>=0; j--) {
            res += sgn*(arr[j]);
            sgn *= -1;
        }
    }
    return res;
}

int main() {
    int y;
    for (y=120; y<= 129; y++)
        printf("%d\n", getsum(y));
}
