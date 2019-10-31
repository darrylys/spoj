#include<stdio.h>
int main(){
    int n, d=0, i;
    scanf("%d", &n);
    while (n--){
        scanf("%d",&i);
        d^=i;
    }
    printf("%d\n", d);
}