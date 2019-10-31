#include<stdio.h>
#include<string.h>

#define MAXN 100010

int stack[MAXN];
int blame[MAXN];
int degree_in[MAXN];
char flag[MAXN];

const char T = 'T';
const char U = 'U';
const char F = 'F';

//0-based

int getint() {
    char c = getchar();
    int n = 0;
    
    while (c < '0' || c > '9') c = getchar();
    
    while (c >= '0' && c <= '9') {
        n = n*10 + c-'0';
        c = getchar();
    }
    return n;
}

int clean_cycle(int start_node) {
    int top = 0, topelem, fs = 0;
    
    stack[top++] = start_node;
    
    while (top) {
        topelem = stack[--top];
        
        if (blame[topelem] == topelem) { //self-loop
            flag[topelem] = F;
            ++fs;
        } else {
            if (flag[blame[topelem]] == T) {
                flag[topelem] = F;
                --degree_in[blame[topelem]];
                ++fs;
            } else if (flag[blame[topelem]] == F) {
                flag[topelem] = T;
            } else {
                flag[topelem] = T;
                flag[blame[topelem]] = F;
                --degree_in[blame[blame[topelem]]];
                ++fs;
                
                if (degree_in[blame[blame[topelem]]] == 0) {
                    stack[top++] = blame[blame[topelem]];
                }
            }
        }
    }
    
    return fs;
}

int solve(int n) {
    memset(degree_in, 0, n*sizeof(int));
    memset(flag, U, n*sizeof(char));
    
    int top=0, topelem, fs = 0;
    
    for (int i=0; i<n; ++i) {
        ++degree_in[blame[i]];
    }
    
    for (int i=0; i<n; ++i) {
        if (degree_in[i] == 0) {
            stack[top++] = i;
        }
    }
    
    //wipe out nodes with degree_in = 0
    while (top) {
        topelem = stack[--top];
        
        if (blame[topelem] == topelem) { //self-loop
            flag[topelem] = F;
            ++fs;
        } else {
        
            if (flag[blame[topelem]] == T) {
                flag[topelem] = F;
                --degree_in[blame[topelem]];
                ++fs;
            } else if (flag[blame[topelem]] == F) {
                flag[topelem] = T;
            } else {
                flag[topelem] = T;
                flag[blame[topelem]] = F;
                --degree_in[blame[blame[topelem]]];
                ++fs;
                
                if (degree_in[blame[blame[topelem]]] == 0) {
                    stack[top++] = blame[blame[topelem]];
                }
            }
        }
    }
    
    //since no more nodes with zero_in_degree, the rest must be in 1-way cycles
    //clean redundant cycles
    for (int i=0; i<n; ++i) {
        if (flag[i] == U) {
            fs += clean_cycle(i);
        }
    }
    
    return fs;
}

int main() {
    int test, n, a;
    test = getint();
    
    while (test--) {
        n = getint();
        
        for (int i=0; i<n; ++i) {
            a = getint();
            blame[i] = a-1;
        }
        
        printf("%d\n", solve(n));
    }
    return 0;
}