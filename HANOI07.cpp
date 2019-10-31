#include<stdio.h>

#define ll long long int

ll data[2502][65][75];
bool flag[2502][65][75];
//ll just_print;
//ll na;
//ll one;

ll find(int n, int h, int m) {
    if (m == 0) {
        //++na;
        flag[n][h][m] = true;
        return (data[n][h][m] = 0);
    }
    
    if (n < 0) {
        //++na;
        return 0;
    }
    
    if (n >= 0 && h == 1) {
        //++one;
        flag[n][h][m] = true;
        return (data[n][h][m] = 1);
    }
    
    if (flag[n][h][m]) {
        //++just_print;
        return data[n][h][m];
    }
    
    ll right = find(n-m-1, h-1, m+1);
    ll left = find(n-m+1, h-1, m-1);
    
    flag[n][h][m] = true;
    return (data[n][h][m] = left + right);
}

int main() {
    int t, n, h, m;
    scanf("%d", &t);
    while (t--) {
        //just_print = na = one = 0;
        scanf("%d %d %d", &n, &h, &m);
        if (n >= 2500) n = 2500;
        printf("%lld\n", find(n-m, h, m));
        
        //printf("just prints = %lld, not_availables = %lld, ones = %lld\n", 
        //    just_print, na, one);
    }
    return 0;
}