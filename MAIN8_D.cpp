#include<stdio.h>
#include<string.h>

#define ll long long

int main() {
    char str[50];
    int t;
    scanf("%d", &t);
    while (t--) {
        scanf("%s", str);
        
        int stc = 1;
        
        ll exc = 0LL;
        int len = strlen(str);
        int nocount = 0;
        int inp;
        
        exc += (1LL << len);
        
        for(int i=0; i<len; ++i) {
            nocount = 0;
            for (inp=i+1; inp<len; ++inp) {
                if (str[inp] != str[inp-i-1]) {
                    nocount = 1;
                    break;
                }
            }
            //printf("%d. checked=%s\n", i, str+i+1);
            if (str[i+1]!='\0' && !nocount) {
                exc += (1LL << (len-i-1));
            }
        }
        printf("%lld\n", exc);
    }
    return 0;
    
}
