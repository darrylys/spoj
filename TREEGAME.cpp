#include<stdio.h>

#define MAXH 16

char tree[1<<MAXH];

const char UNDEF = 0;
const char ONE = '1';
const char ZERO = '0';

char answer_leaf_value(int cidx, int limit) {
    int sibling, lc, rc, next, sibl;
    
    while (cidx) {
        //printf("%d\n", cidx);
        if (cidx&1) { //right child
            sibling = cidx-1;
        } else { //left child
            sibling = cidx+1;
        }
        
        if (tree[sibling] == UNDEF) {
            tree[cidx] = ONE;
            
            //check children
            while ((cidx<<1) < limit) {
                lc = cidx<<1;
                
                if (tree[lc] == UNDEF) {
                    next = lc;
                    sibl = lc+1;
                } else {
                    next = lc+1;
                    sibl = lc;
                }
                
                if (tree[sibl] == ONE && tree[cidx] == ONE) {
                    tree[next] = ZERO;
                } else {
                    tree[next] = ONE;
                }
                
                cidx = next;
            }
            
            return (tree[cidx]);
            
        } else { //check parent
            cidx >>= 1;
        }
    }
    
    return 'X';         //some error occurred
}

int main() {
    int h, leaf, begin_index;
    
    scanf("%d", &h);
    begin_index = (1<<h)-1;
    
    for (int i=1; i<(1<<h); ++i) {
        scanf("%d", &leaf);
        
        putchar(answer_leaf_value(begin_index+leaf, (1<<(h+1))));
        putchar(' ');
    }
    putchar('\n');
    return 0;
}