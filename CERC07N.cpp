#include<cstdio>
#include<cstring>

// b=negative
int negdiv(int a, int b) {
    if (a >= 0) return a/b;
    else {
        int rest = (-a)%(-b);
        if (rest) {
            int up = -a + (-b - rest);
            return up/(-b);
        } else {
            return (-a/(-b));
        }
    }
}

int mod(int a, int b) {
    return a - negdiv(a,b)*b;
}

int main() {
    int a, b, pntr, start, res;
    char stack[50], num[50], e;
    while (true) {
        e = getchar();
        if (e == 'e') break;
        else if (e == 't') {
            scanf("o%d %d", &b, &a);
            if (a == 0) printf("0\n");
            else {
                pntr = 0;
                while (a) {
                    stack[pntr++] = mod(a,b)+'0';
                    a = negdiv(a,b);
                }
                while (pntr--) putchar(stack[pntr]);
                putchar('\n');
            }
        } else if (e == 'f') {
            scanf("rom%d %s", &b, num);
            start = 1; res = 0;
            pntr = strlen(num);
            while (pntr--) {
                res = res + start*(num[pntr]-'0');
                start = start * b;
            }
            printf("%d\n", res);
        }
    }
    return 0;
}
