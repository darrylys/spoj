#include<cstdio>
#include<cstring>
#define CN 30

typedef struct {
    char code;
    int left;
    int right;
} Node;

bool value[CN];
bool flag[CN];
int map[CN];
int stackop[150]; //posisi parent
int stackch[150]; //sisa anaknya
char stackope[150]; //kode parent
bool stackval[150]; //hitung postfix
int counter;
char postfix[150];
char exp[150];
Node node[150]; //tree

void binary_counter() {
    for (int i=CN-1; i>=0; i--) {
        if (value[i]) {
            value[i] = false;
        } else {
            value[i] = true;
            break;
        }
    }
}

void dfs(int root) {
    if (root == -1) {
        return;
    } else {
        dfs(node[root].left);
        dfs(node[root].right);
        postfix[counter++] = node[root].code;
    }
}

int main() {
    int test, diff, dx;
    scanf("%d", &test);
    while (test--) {
        scanf("%s", exp);
        int len = strlen(exp);
        
        memset(value, false, CN*sizeof(bool));
        memset(flag, false, CN*sizeof(bool));
        for (int i=0; i<len; i++) {
            node[i].left = node[i].right = -1;
        }
        int cntr = 1;
        int top = 0;
        int ch;
        stackop[top] = 0;
        if (exp[0] == 'N') stackch[top] = 1;
        else stackch[top] = 2;
        node[0].code = exp[0];
        stackope[top] = exp[0];
        top++;
        diff = 0;
        dx = CN-1;
        for (int i=1; i<len; i++) {
            if (exp[i] <= 'Z') {
                int parent = stackop[top-1];
                char op = stackope[top-1];
                if (op == 'N') {
                    node[parent].left = cntr;
                    stackch[top-1]--;
                } else {
                    if (node[parent].left == -1) {
                        node[parent].left = cntr;
                        stackch[top-1]--;
                    } else {
                        node[parent].right = cntr;
                        stackch[top-1]--;
                    }
                }
                
                node[cntr].code = exp[i];
                if (stackch[top-1] == 0) {
                    top --;
                }
                
                if (exp[i] == 'N') ch = 1;
                else ch = 2;
                stackch[top] = ch;
                stackop[top] = cntr;
                stackope[top] = exp[i];
                top++;
                cntr++;
            } else {
                if (!flag[exp[i]-'a']) {
                    map[exp[i]-'a'] = dx;
                    flag[exp[i]-'a'] = true;
                    diff++;
                    dx--;
                }
                int parent = stackop[top-1];
                char op = stackope[top-1];
                if (op == 'N') {
                    node[parent].left = cntr;
                    stackch[top-1]--;
                } else {
                    if (node[parent].left == -1) {
                        node[parent].left = cntr;
                        stackch[top-1]--;
                    } else {
                        node[parent].right = cntr;
                        stackch[top-1]--;
                    }
                }
                
                node[cntr].code = exp[i];
                if (stackch[top-1] == 0) {
                    top --;
                }
                cntr++;
            }
        }
        counter = 0;
        dfs(0);
        postfix[counter] = '\0'; //postfix notation
        //printf("%s\n", postfix); stackval
        bool taut = true;
        for (int i=0; i<(1<<diff); i++) {
            top = 0;
            for (int j=0; j<counter; j++) {
                if (postfix[j] >= 'a') {
                    stackval[top] = value[map[postfix[j]-'a']];
                    top++;
                } else {
                    switch (postfix[j]) {
                        case 'N':
                            stackval[top-1] = !stackval[top-1];
                            break;
                        case 'C':
                            stackval[top-2] = stackval[top-2] && stackval[top-1];
                            top--;
                            break;
                        case 'D':
                            stackval[top-2] = stackval[top-2] || stackval[top-1];
                            top--;
                            break;
                        case 'E':
                            stackval[top-2] = stackval[top-2] == stackval[top-1];
                            top--;
                            break;
                        case 'I':
                            if (stackval[top-2]) stackval[top-2] = stackval[top-1];
                            else stackval[top-2] = true;
                            top--;
                            break;
                    }
                }
            }
            if (!stackval[0]) {
                taut = false;
                break;
            }
            binary_counter();
        }
        if (taut) printf("YES\n");
        else printf("NO\n");
    }
    return 0;
}