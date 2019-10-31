#include<stdio.h>
#include<string.h>

#define ll long long

char str[1002];
int twos[1002];
int mod;
int sum;
int ps;

int main() {
    int t;
    
    scanf("%d", &t);
    while (t--) {
        scanf("%s %d", str, &mod);
        
        int len = strlen(str);
        
        twos[0] = 1;
        for (int i=1; i<len; ++i) {
            twos[i] = (twos[i-1]<<1)%mod;
        }
        
        sum = 0;
        ps = 1;
        for (int i=len-1; i>=0 ; --i) {
            sum = (int)(((ll)sum + (( ( (ll)(str[i]-'0')*ps )%mod )*twos[i])%mod )%mod);
            ps = (11LL * ps)%mod;
        }
        
        printf("%d\n", sum);
    }
}
