#include<stdio.h>
#include<string.h>

const char digit[] = {"0123456789ABCDEF"};

int main() {
    char num[8], from[5], to[5];
    int basefrom, baseto;
    int len, mul, i, j, source, totaldigits;
    while (scanf("%s%s%s", num, from, to)!=EOF) {
        basefrom=0;
        baseto=0;
        mul = 1;
        len = strlen(from);
        for (i=len-1;i>=0;i--) {
            basefrom+=(from[i]-'0')*mul;
            mul*=10;
        }
        len = strlen(to);
        mul = 1;
        for (i=len-1;i>=0;i--) {
            baseto+=(to[i]-'0')*mul;
            mul*=10;
        }
        len = strlen(num);
        source=0;
        mul=1;
        for (i=len-1;i>=0;i--) {
            if (num[i]>='0' && num[i]<='9') {
                source+=(num[i]-'0')*mul;
            } else if (num[i]>='A' && num[i]<='F') {
                source+=(num[i]-55)*mul;
            }
            mul*=basefrom;
        }
        totaldigits=6;
        for (i=0;i<7;i++) num[i] = ' ';
        do {
            if (totaldigits<0) {
                printf("  ERROR\n");
                goto error;
            }
            num[totaldigits--] = digit[source%baseto];
            source/=baseto;
        } while (source > 0);
        printf("%s\n", num);

        error:
        ;
    }
    return 0;
}
