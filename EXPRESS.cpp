#include<cstdio>
#include<cstring>
#include<queue>

#define N 10005

using namespace std;

typedef struct {
    char mode;
    int size;
    int child[2];
} Node;

char qdex[N];
char stack_name[N];
int stack_pos[N];
Node node[N];
char postfix[N];

void construct_tree(char* str, int n) {
    int top = 0; //points next empty
    
    for (int i=0; i<n; i++) {
        if (str[i] <= 'Z') { //operators
            --top;
            char right = stack_name[top];
            int rpos = stack_pos[top];
            
            --top;
            char left = stack_name[top];
            int lpos = stack_pos[top];
            
            node[i].mode = str[i];
            node[i].child[0] = (lpos);
            node[i].child[1] = (rpos);
            node[i].size = 2;
            
            node[rpos].mode = right;
            node[lpos].mode = left;
        } else {
            node[i].size = 0;
        }
        stack_name[top] = str[i];
        stack_pos[top] = i;
        top++;
    }
}

void print_tree(int root) {
    if (node[root].size == 0) {
        putchar(node[root].mode);
    } else {
        print_tree(node[root].child[0]);
        print_tree(node[root].child[1]);
        putchar(node[root].mode);
    }
}

int rename_tree(int root) {
    queue<int> qs;
    qs.push(root);
    int cntr = 0;
    while (!qs.empty()) {
        int q = qs.front(); qs.pop();
        
        qdex[cntr++] = node[q].mode;
        
        if (node[q].size) {
            qs.push(node[q].child[0]);
            qs.push(node[q].child[1]);
        }
    }
    
    return cntr;
}

int main() {
    int test, len;
    scanf("%d", &test);
    while (test--) {
        scanf("%s", postfix);
        len = strlen(postfix);
        
        construct_tree(postfix, len);
        int last = rename_tree(len-1);
        
        for (int i=last-1; i>=0; i--) {
            putchar(qdex[i]);
        }
        putchar('\n');
    }
    return 0;
}