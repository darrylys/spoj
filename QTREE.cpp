#include<stdio.h>
#include<vector>

#define MAXN 10010

using namespace std;

vector<int> E[MAXN];
vector<int> W[MAXN];
vector<int> I[MAXN];

int parent[MAXN];
int treesize[MAXN];
int data[MAXN];
int edx[MAXN];
int remap[MAXN];

int homechain[MAXN];        //chain id
int homepos[MAXN];
int chainhead[MAXN];

int visitedchain[MAXN];
bool chainflag[MAXN];

int pos;
int num_of_chain;
int samechain;

int segmt[3*MAXN];

void explore(int x, int dad) {
    
    if (parent[x] != -1) return;
    
    parent[x] = dad;
    treesize[x] = 1;
    
    for (int i=0; i<E[x].size(); ++i) {
        if (E[x][i] != dad) {
            explore(E[x][i], x);
            treesize[x] += treesize[E[x][i]];
        }
    }
}

void heavy_light(int x, int dad, int weight, int edge_id, int chain_id, bool new_chain) {
    if (new_chain) {
        chain_id = num_of_chain++;
        chainhead[chain_id] = x;
    }
    homechain[x] = chain_id;
    data[pos] = weight;
    homepos[x] = pos;
    edx[edge_id] = pos;
    pos++;
    
    int max = -1;
    int maxid = -1;
    for (int i=0; i<E[x].size(); i++) {
        if (E[x][i] != dad && max < treesize[E[x][i]]) {
            max = treesize[E[x][i]];
            maxid = i;
        }
    }
    
    if (maxid != -1) {
        heavy_light(E[x][maxid], x, W[x][maxid], I[x][maxid], chain_id, false);
    }
    
    for (int i=0;i<E[x].size();i++) {
        if (E[x][i] != dad && i != maxid) {
            heavy_light(E[x][i], x, W[x][i], I[x][i], -1, true);
        }
    }
}

void build_tree(int root, int a, int b) {
    if (a == b) {
        segmt[root] = data[a];
        remap[a] = root;
    } else {
        int lc = root<<1, mid = (a+b)>>1;
        
        build_tree(lc, a, mid);
        build_tree(lc+1, mid+1, b);
        
        segmt[root] = (segmt[lc] > segmt[lc+1]) ? segmt[lc] : segmt[lc+1];
    }
}

int _query(int root, int a, int b, int x, int y) {
    if (a == x && y == b) {
        return segmt[root];
    } else if (x>b || y<a || x>y) {
        return -1;
    } else {
        int lc = root<<1, mid = (a+b)>>1;
        int xs = x, ys = y;
        
        if (xs < mid+1) xs = mid+1;
        if (ys > mid) ys = mid;
        
        int left = _query(lc, a, mid, x, ys);
        int right = _query(lc+1, mid+1, b, xs, y);
        
        //printf("left=%d, right=%d\n", left, right);
        
        return (left > right) ? left : right;
    }
}

int mark_chain(int a, int& off) {
    
    int start = a;
    
    while (start > 0) {
        
        if (chainflag[homechain[start]] ) {
            samechain = homechain[start];
            return start;
        }
        
        chainflag[ homechain[start] ] = true;
        visitedchain[off++] = homechain[start];
        
        start = parent[ chainhead[ homechain[start] ] ];
    }
    
    return -1;
}

int QUERY_(int a, int b, int n) {
    if (a == b) return 0;

    memset(chainflag, false, num_of_chain*sizeof(bool));
    
    int off = 0;
    
    mark_chain(a, off);
    
    int ea = off;
    int lb = mark_chain(b, off);
    
    //printf("lb=%d\n", lb);
    
    int eb = off;
    int max = -1;
    int st = a;
    
//    printf("eb-ea = %d\n", eb-ea);
    for (int i=0; i<ea; i++) {
        if (visitedchain[i] != samechain) {
            int q = _query(1, 0, n-1, homepos[ chainhead[ homechain [st]]], homepos[st]);
            st = parent[ chainhead[ homechain [st]]];
            
            if (max < q) {
                max = q;
            }
        } else {
            int q;
            int aa = homepos[lb];
            int bb = homepos[st];
            
            if (aa < bb) q = _query(1, 0, n-1, homepos[lb]+1, homepos[st]);
            else q = _query(1, 0, n-1, homepos[st]+1, homepos[lb]);
            
            if (max < q) {
                max = q;
            }
            
            break;
        }
    }
    
    st = b;
    for (int i=ea; i<eb; i++) {
        int q = _query(1, 0, n-1, homepos[ chainhead[ homechain [st]]], homepos[st]);
        st = parent[ chainhead[ homechain [st]]];
        
        if (max < q) {
            max = q;
        }
    }
    
    return max;
}

void CHANGE_(int index, int nv) {
    int indata = remap[edx[index]];
    
    segmt[indata] = nv;
    indata >>= 1;
    
    while (indata) {
        int lc = indata<<1;
        
        segmt[indata] = (segmt[lc] > segmt[lc+1]) ? segmt[lc] : segmt[lc+1];
        
        indata>>=1;
    }
}

void print_heap(int root, int a, int b, int space = 0) {
    if ( a== b) {
        while (space--) putchar(' ');
        printf("[%d,%d] => %d\n", a, b, segmt[root]);
    } else {
        for (int i=0;i<space;i++) putchar(' ');
        printf("[%d,%d] => %d\n", a, b, segmt[root]);
        print_heap(root*2, a, (a+b)/2, space+4);
        print_heap(root*2+1, (a+b)/2+1, b, space+4);
    }
}

void print_array(char* msg, int* array, int a, int b) {
    printf("%s", msg);
    for (int i=a; i<=b; i++) {
        printf("%d ", array[i]);
    }
    printf("\n\n");
}

int main() {
    int testcase, n, a, b, w;
    char txt[10];
    
    scanf("%d", &testcase);
    
    while (testcase--) {
        scanf("%d", &n);
        
        memset(parent, -1, sizeof (parent));
        
        for (int i=1; i<n; i++) {
            scanf("%d %d %d", &a, &b, &w);
            
            E[a].push_back(b);
            W[a].push_back(w);
            I[a].push_back(i);
            
            E[b].push_back(a);
            W[b].push_back(w);
            I[b].push_back(i);
        }
        
        pos = 0; num_of_chain = 0;
        
        explore(1, 0);
        heavy_light(1, 0, -1, 0, 0, true);
        build_tree(1, 0, n-1);
        
/*        printf("num_of_chains: %d\n", num_of_chain);
        print_array("data:\n", data, 0, n);
        print_array("homechain:\n", homechain, 0, n);
        print_array("chainhead:\n", chainhead, 0, n);
        print_array("treesize:\n", treesize, 0, n);
        print_array("parent:\n", parent, 0, n);
        print_array("edx:\n", edx, 0, n);
        print_array("homepos:\n", homepos, 0, n);*/

        while (scanf("%s", txt) && txt[0] != 'D') {
            scanf("%d %d", &a, &b);
            if (txt[0] == 'Q') {
                printf("%d\n", QUERY_(a,b,n));
            } else {
                CHANGE_(a, b);
            }
        }
        
        for (int i=1; i<=n; i++) {
            E[i].clear();
            W[i].clear();
            I[i].clear();
        }
        
        if (testcase) putchar('\n');
    }
    return 0;
}