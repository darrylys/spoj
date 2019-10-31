#include<stdio.h>

#define MAXN 35

int arr[2][MAXN];
int move[3*MAXN];

void flip(int &c, int from, int n) {
    
    for (int i=from+1; i<n; ++i) {
        arr[c^1][i] = arr[c][i];
    }
    
    for (int i=from, j=0; i>=0; --i, ++j) {
        //printf("i=%d, j=%d\n", i, j);
        arr[c^1][j] = -arr[c][i];
    }
    
    c ^= 1;
}

void printarray(int* arr, int n) {
    for (int i=0;i<n;i++) printf("%d ", arr[i]);
    putchar('\n');
}

int main() {
    int test, n, step = 0, now_processed, idx, d, cn=0;
    int c = 1;
    
    scanf("%d", &test);
    
    while (test--) {
        scanf("%d", &n);
        //printf("n=%d\n", n);
        c = 0;
        for (int i=0; i<n; i++) {
            scanf("%d", &arr[c][i]);
        }
        
        now_processed = n;
        step = 0;
        while (now_processed) {
            //printf("now_processed=%d\n", now_processed);
            //printf("1\n");
            //check where is the target
            for (int i=0; i<n; i++) {
                if (arr[c][i] == now_processed || arr[c][i] == -now_processed) {
                    idx = i;
                    break;
                }
            }
            
            //printf("2\n");
            //if the target is in index > 0
                //if target is in intended index and sign=positive, process next pile
                //else flip (++step)
            // else next step
            if (idx > 0) {
                if (idx == now_processed-1 && arr[c][idx] > 0) {
                    --now_processed;
                    continue;
                } else {
                    //printf("2a\n");
                    //printf("\nupper before:\n");
                    //printarray(arr[c], n);
                    flip(c, idx, n);
                    //printf("2b\n");
                    move[step++] = idx+1;
                    
                    //printf("\nupper after:\n");
                    //printarray(arr[c], n);
                }
            }
            
            //printf("3\n");
            //check, if the target's sign = +, flip (++step) else continue to next step
            if (idx == 0 && now_processed==1) {
                if (arr[c][0] < 0) {
                    arr[c][0] = -arr[c][0];
                    move[step++] = 1;
                }
                break;
            } else {
                if (arr[c][0] > 0) {
                    arr[c][0] = -arr[c][0];
                    move[step++] = 1;
                }
            }
            
            //printf("4\n");
            //flip
            if (now_processed > 1) {
                //printf("\nlower before:\n");
                //printarray(arr[c], n);
                
                //printf("\nlower after:\n");
                flip(c, now_processed-1, n);
                //printarray(arr[c], n);
                move[step++] = now_processed;
            }
            
            //printf("5\n");
            //process next pile.
            --now_processed;
        }
        
        printf("%d %d", ++cn, step);
        for (int i=0; i<step; i++) {
            printf(" %d", move[i]);
        }
        putchar('\n');
    }
    return 0;
}