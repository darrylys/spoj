#include<cstdio>
#define MAXN 20010
#define INC 0
#define DATA 1

int data[MAXN*4][2];

void build_tree(int node, int start, int end) {
    if (start == end) {
        data[node][INC] = data[node][DATA] = 0;
    } else {
        data[node][INC] = data[node][DATA] = 0;
        build_tree(node*2, start, (start+end)/2);
        build_tree(node*2+1,(start+end)/2+1,end);
    }
}

void search(int node, int num, int start, int end, int cardno) {
    //if (node >= MAXN*4) printf("node=>%d\n", node);
    if (start == end) {
        data[node][DATA] = cardno;
        data[node][INC] ++;
    } else {
        if (num + data[node*2][INC] <= (start+end)/2) {
            data[node*2][INC]++;
            search(node*2, num, start, (start+end)/2, cardno);
        } else {
            data[node*2+1][INC]++;
            search(node*2+1, num+ data[node*2][INC], (start+end)/2+1, end, cardno);
        }
    }
}

void dfs(int node, int start, int end) {
    if (start == end) {
        printf("%d", data[node][DATA]);
    } else {
        dfs(node*2, start, (start+end)/2);
        printf(" ");
        dfs(node*2+1, (start+end)/2+1, end);
    }
}

int main() {
    int tc;
    scanf("%d",&tc);
    while (tc--) {
        int n;
        scanf("%d",&n);
        int r=0;
        build_tree(1, 0, n-1);
        for (int k=1; k<=n; k++) {
            r = (r+k)%(n-k+1);
            search(1, r, 0, n-1, k);
        }
        dfs(1, 0, n-1);
        putchar('\n');
    }
    return 0;
}
