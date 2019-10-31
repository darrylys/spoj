#include<cstdio>
#define LIM 1572864
#define MOD 1 << 20

int arr[LIM+2];

int main() {
    arr[1] = arr[2] = 1;
    for (int i=3; i<=LIM; i++) {
        arr[i] = arr[i-1]+arr[i-2];
        arr[i]%=(MOD);
    }
    //printf("lim = %d\n", arr[LIM]);
    int c,n,m;
    scanf("%d", &c);
    while (c--) {
        scanf("%d %d",&n,&m);
        int p = 3*(1<<(m-1));
        n = n%p + 1;
        n %=p;
        
        //printf("n=%d, arr[n]=%d\n",n, arr[n]%(1<<m));
        printf("%d\n",arr[n]%(1<<m));
    }
    return 0;
}