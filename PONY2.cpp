#include<stdio.h>
#include<string.h>

#define ll long long

int main() {
    int t;
    char S[110];
    ll fun[110];
    ll N;
    
    scanf("%d", &t);
    while (t--) {
        scanf("%s %lld", S, &N);
        
        // fill table
        int len = strlen(S);
        fun[len] = 1;
        for (int i=len-1; i>=0; --i) {
            fun[i] = 0;
            if (S[i] != '0') {
                if (S[i+1] != '0') {
                    fun[i] = fun[i+1];
                }
                if (i+1<len && ((S[i]-'0')*10 + (S[i+1]-'0') <= 26)) {
                    fun[i] += fun[i+2];
                }
            }
        }
        
        /*printf("FUN: \n");
        for (int i=0; i<=len; ++i) {
            printf("%lld ", fun[i]);
        }
        printf("===\n");*/
        
        // traverse tree
        for (int i=0; i<len; ) {
            //check S[i] and S[i+1] (IF POSSIBLE)
            
            // no way to have letter > 30! must be single letter!
            if (S[i] > '2') {
                putchar(S[i]-'0'+'a'-1);
                i++;
            } else {
                if (S[i+1] != '0') {
                    if (N > fun[i+1]) { //need check doubles
                        N -= fun[i+1];
                        putchar((S[i]-'0')*10+(S[i+1]-'0') + 'a'-1);
                        i += 2;
                    } else { //within
                        putchar(S[i]-'0'+'a'-1);
                        i++;
                    }
                } else {
                    putchar((S[i]-'0')*10 + 'a'-1);
                    i +=2; //next is '0', ignore this!
                }
            }
        }
        putchar('\n');
    }
}