#include<cstdio>

char num1[1000005];
char num2[1000005];

char play(char* n1, int len1, char* n2, int len2) {
    if (len1 < len2) return '<';
    else if (len1 > len2) return '>';
    else {
        for (int i=0; i<len1; i++) {
            if (n1[i] < n2[i]) return '<';
            else if (n1[i] > n2[i]) return '>';
        }
        return '=';
    }
}

int main() {
    int cntr = 0, len1, len2;
    char c;
    while (true) {
        num1[0] = num2[0] = '0';
        cntr = 0;
        
        c=getchar();
        if (c == '*') break;
        while (c == '0') c=getchar();
        if (c != ' ') {
            num1[cntr++] = c;
            while ((c=getchar())!=' ') {
                num1[cntr++] = c;
            }
            len1 = cntr;
            num1[len1] = 0;
        } else {
            len1 = 1;
            num1[1] = 0;
        }
        
        //printf("num1=%s\n", num1);
        cntr=0;
        c=getchar();
        //printf("2nd c is %c\n", c);
        while (c == '0') c=getchar();
        if (c != '\n') {
            num2[cntr++] = c;
            while ((c=getchar())!='\n') {
                num2[cntr++] = c;
            }
            len2 = cntr;
            num2[len2] = 0;
        } else {
            len2 = 1;
            num2[1] = 0;
        }
        //printf("num2=%s\n", num2);
        putchar(play(num1, len1, num2, len2));
        putchar('\n');
        //getchar();
    }
}
