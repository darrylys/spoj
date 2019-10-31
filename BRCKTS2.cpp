#include<stdio.h>
#include<string.h>
#include<vector>

using namespace std;

#define N 350010
#define HN 175005
#define BLACK false
#define WHITE true
#define lu unsigned long long int

typedef struct {
    int h, w;
    lu area;
    bool color;
    vector<int> child;
} Node;

Node node[HN];
bool flag[HN];

//stacks
//char par_stack[HN];      //stack for parenthesis parsing
int idx_stack[HN];       //stack for index for construct tree
//int top_par;
int top_idx;
int next;

char skip_nl() {
    char c;
    while ((c=getchar()) == '\n' || c == '\r') continue;
    return c;
}

lu construct(char in, bool final) {
    //putchar(input);
    if (in == '(') {
        //par_stack[top_par++] = in;
        int parent = idx_stack[top_idx-1];
        if (!flag[parent]) {
            node[parent].child.clear();
            flag[parent] = true;
        }
        node[parent].child.push_back(next);
        idx_stack[top_idx++] = next;
        next++;
    } else {
        int idx = idx_stack[--top_idx]; //current index
        //--top_par;
        
        if (!flag[idx]) {
            node[idx].child.clear();
            flag[idx] = true;
        }
        if (node[idx].child.size() == 0) { //base case
            if (final) return 1;
            node[idx].h = node[idx].w = node[idx].area = 1;
        } else {    //has children
            int minh = 1, minw = 1;
            int cs = node[idx].child.size();
            
            minw += cs;
            for (int i=0; i<cs; i++) {
                minw += node[node[idx].child[i]].w;
            }
            
            int max = -1;
            for (int i=0; i<cs; i++) {
                if (max < node[node[idx].child[i]].h) max = node[node[idx].child[i]].h;
            }
            
            lu total_area = 0;
            for (int i=0; i<cs; i++) {
                total_area = total_area + node[node[idx].child[i]].area;
            }
            
            if (final) return total_area;
            
            minh += max;
            
            node[idx].h = minh;
            node[idx].w = minw;
            node[idx].area = (lu)minh*minw - total_area;
        }
    }
    return 1234;    //just messing up
}

int main() {
    int test; char c;
    scanf("%d", &test);
    while (test--) {
        //inits
        //top_par = 0; 
        top_idx = 0;
        //par_stack[top_par++] = '(';
        idx_stack[top_idx++] = 0;
        flag[0] = true;
        node[0].child.clear();
        next = 1;
        memset(flag, false, HN*sizeof(bool));
        
        //loop
        while (1) {
            c = skip_nl();
            if (c == EOF) break;
            while (c != '\n' && c != '\r' && c != EOF) {
                construct(c, false);
                c = getchar();
            }
            printf("%llu\n", construct(')', true)); //final enclosing
            
            break;
        }
        if (c == EOF) break;
    }
    return 0;
}