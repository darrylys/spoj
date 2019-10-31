#include<stdio.h>

#define ll long long
#define MOD 100000007

int fn[400010];

int getfn(int n) {
    if (n<=0) return 0;
    else return fn[n];
}

int main() {
    int t;
    char c;
    scanf("%d", &t);
    while (t--) {
        int prevnum = 0;
        int ans = 1;
        int idx = 1;
        fn[1] = 1;
        int mul; //hit times
        int num; //pressed num
        int tpe;
        while ((c=getchar())=='\n' ||c == '\r');
        do {
            if (c == -1) break;
            if (c < 'p') {
                mul = (c-'a')%3+1;
                num = (c-'a')/3+2;
                tpe = 3;
            } else if (c < 't') {
                mul = (c-'a'+1)%4+1;
                num = 7;
                tpe = 4;
            } else if (c < 'w') {
                mul = (c-'a'-1)%3+1;
                num=8;
                tpe = 3;
            } else {
                mul=(c-'a'-2)%4+1;
                num=9;
                tpe = 4;
            }
            while (mul--) {
                if (num == prevnum) {
                    if (idx > 1) {
                        fn[idx] = ((getfn(idx-1)<<1) - getfn(idx-tpe-1) + MOD)%MOD;
                        idx++;
                    }
                } else {
                    if (idx > 1) {
                        ans = (int)(((ll)ans * getfn(idx-1))%MOD);
                    }
                    prevnum = num;
                    idx=2;
                }
            }
        } while ((c=getchar()) != '\n' && c != '\r');
        printf("%d\n", (int)(((ll)ans * getfn(idx-1))%MOD));
    }
}