#include<cstdio>

#define CONVERT(a,b) (b==2)?2:a
#define MAX(a,b) (a>b)?a:b

int main() {
    int item[4] = {0,0,0,0};
    
    int n, a,b;
    int pizza = 1;
    scanf("%d", &n);
    while (n--) {
        scanf("%d/%d", &a, &b);
        item[CONVERT(a,b)]++;
    }
    
    pizza += item[3]; //all 3 need 1 pizza
    item[1] = MAX(0, item[1] - item[3]); //match 3-1
    
    pizza += item[2]/2;
    if (item[2]%2) {
        item[1] = MAX(0, item[1] - 2); //match 2-1-1
        pizza++;
    }
    
    pizza += item[1]/4;
    
    if (item[1]%4) pizza++;
    
    printf("%d\n", pizza);
    return 0;
}