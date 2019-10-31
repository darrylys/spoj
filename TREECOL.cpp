#include<stdio.h>
#include<string.h>

// index from 1 -> 0=dead
#define R 0
#define G 1
#define B 2
#define MAXX 10005
#define max3(a,b,c) max((a),max((b),(c)))
#define min3(a,b,c) min((a),min((b),(c)))

int amax[MAXX][3];
int amin[MAXX][3];
int tree[MAXX][2];

int max(int a, int b) { return (a>b)?a:b; }
int min(int a, int b) { return (a<b)?a:b; }

int eat(int next, char root) {
    if (root == '\n') { return 0; }
    if (root == '0') {
        tree[next][0] = tree[next][1] = 0;
        return next+1;
    }
    if (root == '1') {
        tree[next][0] = next+1;
        tree[next][1] = 0;
        return eat(next+1, getchar());
    }
    if (root == '2') {
        tree[next][0] = next+1;
        int m = eat(next+1, getchar());
        tree[next][1] = m;
        return eat(m, getchar());
    }
    return 0;
}

int _rec(int root, int color) {
    if (root == 0) { return 0; }
    
    if (amax[root][color] != -1) return amax[root][color];
    
    if (tree[root][1] == 0) {
        if (color==0) {
            amax[root][color] = max(_rec(tree[root][0], 1), _rec(tree[root][0], 2));
        } else if (color==1) {
            amax[root][color] = max(_rec(tree[root][0], 0), _rec(tree[root][0], 2)) + 1;
        } else {
            amax[root][color] = max(_rec(tree[root][0], 0), _rec(tree[root][0], 1));
        }
    } else {
        if (color==0) {
            amax[root][color] = max(_rec(tree[root][0], 1)+ _rec(tree[root][1], 2),_rec(tree[root][0], 2)+ _rec(tree[root][1], 1));
        } else if (color==1) {
            amax[root][color] = max(_rec(tree[root][0], 0)+ _rec(tree[root][1], 2),_rec(tree[root][0], 2)+ _rec(tree[root][1], 0))+1;
        } else {
            amax[root][color] = max(_rec(tree[root][0], 0)+ _rec(tree[root][1], 1),_rec(tree[root][0], 1)+ _rec(tree[root][1], 0));
        }
    }
    
    return amax[root][color];
}

int _rem(int root, int color) {
    if (root == 0) {
        return 0;
    }
    
    if (amin[root][color] != -1) return amin[root][color];
    
    if (tree[root][1] == 0) {
        if (color==0) {
            amin[root][color] = min(_rem(tree[root][0], 1), _rem(tree[root][0], 2));
        } else if (color==1) {
            amin[root][color] = min(_rem(tree[root][0], 0), _rem(tree[root][0], 2)) + 1;
        } else {
            amin[root][color] = min(_rem(tree[root][0], 0), _rem(tree[root][0], 1));
        }
    } else {
        if (color==0) {
            amin[root][color] = min(_rem(tree[root][0], 1)+ _rem(tree[root][1], 2),_rem(tree[root][0], 2)+ _rem(tree[root][1], 1));
        } else if (color==1) {
            amin[root][color] = min(_rem(tree[root][0], 0)+ _rem(tree[root][1], 2),_rem(tree[root][0], 2)+ _rem(tree[root][1], 0))+1;
        } else {
            amin[root][color] = min(_rem(tree[root][0], 0)+ _rem(tree[root][1], 1),_rem(tree[root][0], 1)+ _rem(tree[root][1], 0));
        }
    }
    
    return amin[root][color];
}

void rec(int root) {
    for (int i=0; i<3; ++i) {
        amax[root][i] = _rec(root, i);
        amin[root][i] = _rem(root, i);
    }
}

void printtree(int root, int mk) {
    
    
    for (int i=0; i<mk; ++i) printf(" ");
    printf("%d\n", root);
    
    if (root == 0) return;
    printtree(tree[root][0], mk+2);
    printtree(tree[root][1], mk+2);
}

int main() {
    
    int t;
    scanf("%d", &t);
    int next=1;
    char in;
    while (t--) {
        memset(amax, -1, sizeof(amax[0][0])*MAXX*3);
        memset(amin, -1, sizeof(amin[0][0])*MAXX*3);
        
        getchar();
        
        eat(1, getchar());
        
        rec(1);
        
        printf("%d %d\n", max3(amax[1][0], amax[1][1], amax[1][2]), min3(amin[1][0], amin[1][1], amin[1][2]));
        
    }
}