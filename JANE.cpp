#include<stdio.h>
#include<set>
#include<algorithm>
#include<iterator>

#define MAXN 100010
#define SEI set<ll>::iterator
#define ll long long

using namespace std;

int stack_j[2*MAXN];
int stack_t[2*MAXN];
int jane[MAXN], tarj[MAXN];
int tree[MAXN];
int pdx[MAXN];

set<ll> visited;

int dir[4][2] = {{-1,-1},{-1,1},{1,-1},{1,1}};

int abs(int a) {
    if (a < 0) return -a;
    else return a;
}

int getint() {
    char c = getchar(); int n=0;
    
    while (c > '9' || c < '0') c = getchar();
    while (c <= '9' && c >= '0') {
        n = n*10 + c-'0';
        c = getchar();
    }
    return n;
}

bool cmp(int a, int b) {
    if (jane[a] < jane[b]) return true;
    else if (jane[a] > jane[b]) return false;
    else return tarj[a] < tarj[b];
}

int run_dfs(int n, int d) {
    int ptr = 0;
    int lastpair = 0;
    int nj, nt;
    
    stack_j[ptr] = 0; //insert seed
    stack_t[ptr] = 0;
    ptr++;
    
    for (int i=1; i<n; ++i) {
        if (abs(tree[i]-tree[i-1]) <= d) { //insert adj valid pairs
//            jane[lastpair] = i;
//            tarj[lastpair] = i+1;
            
            stack_j[ptr] = i-1;
            stack_t[ptr] = i;
            ++ptr;
//            ++lastpair;
        }
    }
    
    int jane_idx, tarj_idx;
    ll code;
//    printf("ptr=%d\n", ptr);
//    bool f = true;
    while (ptr) {
        jane_idx = stack_j[ptr-1];
        tarj_idx = stack_t[ptr-1];
        --ptr;
        
//        if (f) {
            nj = jane_idx, nt = tarj_idx;
            code = nj*(ll)MAXN + nt;
            SEI setiter = visited.find(code);
            if (setiter == visited.end()) {
                visited.insert(code);
                if (nj < nt) {
                    jane[lastpair] = nj+1;
                    tarj[lastpair] = nt+1;
                    ++lastpair;
                }
            }
//            f = false;
//        }
        
//        printf("jane=%d, tarj=%d\n", jane_idx, tarj_idx);
        
        for (int i=0; i<4; ++i) {
            nj = jane_idx + dir[i][0];
            nt = tarj_idx + dir[i][1];
            if (nj >= 0 && nj < n && nt >= 0 && nt < n && nj <= nt) {
                if (abs(tree[nj]-tree[nt]) <= d) {
                    code = nj*(ll)MAXN + nt;
                    SEI setiter = visited.find(code);
                    if (setiter == visited.end()) {
                        visited.insert(code);
                        stack_j[ptr] = nj;
                        stack_t[ptr] = nt;
                        
                        if (nj < nt) {
                            jane[lastpair] = nj+1;
                            tarj[lastpair] = nt+1;
                            ++lastpair;
                        }
                        ++ptr;
                    }
                }
            }
        }
    }
    return lastpair;
}

int main() {
    int n, d;
    
    n = getint();
    d = getint();
    
    for (int i=0; i<n; ++i) {
        tree[i] = getint();
    }
    
    int lp = run_dfs(n, d);
    
    for (int i=0; i<lp; ++i) {
        pdx[i] = i;
    }
    
    sort(pdx, pdx+lp, cmp);
    
    for (int i=0; i<lp; ++i) {
        printf("%d %d\n", jane[pdx[i]], tarj[pdx[i]]);
    }
    return 0;
}
