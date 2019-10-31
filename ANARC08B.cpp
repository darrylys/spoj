#include<cstdio>
#include<cstring>

int numcode[10] = {63,10,93,79,106,103,119,11,127,107};
char num[2][15];
char in[100];

char codetonum(int code) {
    switch(code) {
        case 63: return 0;
        case 10: return 1;
        case 93: return 2;
        case 79: return 3;
        case 106: return 4;
        case 103: return 5;
        case 119: return 6;
        case 11: return 7;
        case 127: return 8;
        case 107: return 9;
    }
}

int main() {
    int len;
    int now;
    int sw = 0;
    int cntr=0;
    int mul, n[2];
    bool flag;
    while (scanf("%s",in)) {
        sw = cntr = 0;
        if (strcmp(in,"BYE")) {
            len = strlen(in);
            //printf("alen=%d\n", len);
            for (int i=0; i<len; i+=3) {
                if (in[i] == '+') {
                    //printf("cntr=%d\n", cntr);
                    num[sw][cntr] = '\0';
                    i-=2;
                    sw++;
                    cntr=0;
                    continue;
                }
                if (in[i] == '=') {
                    num[sw][cntr] = '\0';
                    break;
                }
                now = (in[i]-'0')*100 + (in[i+1]-'0')*10 + (in[i+2]-'0');
                num[sw][cntr] = codetonum(now)+'0';
                cntr++;
            }
            for (int x=0; x<2; x++) {
                n[x] = 0;
                mul = 1;
                len = strlen(num[x]);
                //printf("len=%d\n", len);
                while (len--) {
                    n[x] += (int)(num[x][len]-'0')*mul;
                    mul*=10;
                }
            }
            int res = n[0]+n[1];
            //printf("res=%d 0=%d 1=%d\n", res, n[0], n[1]);
            int a=res, dgt=-1;
            mul = 1;
            while (a>0) {
                a/=10;
                dgt++;
            }
            while (dgt>0) {
                mul*=10;
                dgt--;
            }
            a=0;
            int leadzero=0;
            flag = true;
            while (res>0) {
                if (flag && res%10 == 0) leadzero++;
                else {
                    a+=(res%10)*mul;
                    flag = false;
                }
                mul /= 10;
                res /= 10;
            }
            printf("%s", in);
            while (a>0) {
                printf("%03d", numcode[a%10]);
                a/=10;
            }
            while (leadzero--) printf("%03d", numcode[0]);
            putchar('\n');
        } else break;
    }
}


