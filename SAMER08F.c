#include<stdio.h>

int main(int argc, char** argv) {
    int arr[110], i;
    arr[1] = 1;
    for (i=2; i<=100; i++) {
        arr[i] = arr[i-1] + i*i;
    }
    int c;
    while(scanf("%d",&c)&&c) printf("%d\n", arr[c]);
    return 0;
}
