#include<stdio.h>
#include<string.h>

void print(int* arr, int n) {
    for (int i=0; i<n; i++) printf("%4d ", arr[i]);
    putchar('\n');
}

int solve(char* exp, int n) {
    int map[8] = {0,0,0,0,0,0,0,0};
    map['C'%8] = 12;
    map['H'%8] = 1;
    map['O'%8] = 16;
    
    int stack[200];
    int top = 0;
    
    int total;
    stack[top++] = (int)'(';
    //printf("%d\n", stack[0]);
    exp[n] = ')';
    //print(stack, top);
    for (int i=0; i<=n; i++) {
        //print(stack, top);
        if (exp[i] == (int)'(') {
            stack[top++] = (int)'(';
        } else if (exp[i] >= 'A' && exp[i] <= 'Z') {
            stack[top++] = map[exp[i]%8];
        } else if (exp[i] >= '0' && exp[i] <= '9') {
            int now = stack[--top];
            now *= (exp[i]-'0');
            stack[top++] = now;
        } else {
            top--;
            total = 0;
            for (; stack[top] != (int)'(';) {
                total += stack[top--];
            }
            stack[top++] = total;
        }

    }
    
    return stack[0];
}

int main() {
    char exp[150];
    scanf("%s", exp);
    printf("%d\n", solve(exp, strlen(exp)));
    /*
    while (scanf("%s", exp) != EOF) {
        printf("%d\n", solve(exp, strlen(exp)));
    }*/
    return 0;
}