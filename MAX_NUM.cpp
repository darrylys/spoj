#include<stdio.h>
#include<string.h>

#define MAXN 100010

char data[MAXN];
char stack[MAXN];

void doz(int n, int _k) {
    int top = 0;
    int k = _k;
    stack[top++] = 'a';
    char c;
    for (int i=0; i<=n; ++i) { //data[n] = 'a';
        c = stack[top-1];
        if (data[i] <= c) {
            stack[top++] = data[i];
        } else {
            while (k && top && data[i] > c) {
                --top;
                c = stack[top-1];
                k--;
            }
            if (k == 0) {
                for (; i<n; ++i) {
                    stack[top++] = data[i];
                }
                stack[top++] = '\0';
                return;
            }
            stack[top++] = data[i];
        }
    }
}

int main() {
    int t, k, n;
    scanf("%d", &t);
    while (t--) {
        scanf("%s %d", data, &k);
        n = strlen(data);
        data[n] = 'a';
        doz(n,k);
        printf("%s\n", stack+1);
    }
    return 0;
}
