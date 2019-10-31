#include<stdio.h>
#include<string.h>

#define DGT 1<<10
#define SGM 1<<13
#define UNUSED 0
#define MAX 1000000000

int _min(int a, int b) {
    return (a<b)?a:b;
}

// paranoid...
int state[DGT][SGM];
char inputr[DGT];
char input[DGT];

int memo(int n, int sum) {
    //printf("bef (%d, %d)=%d\n", n, sum, state[n][sum]);
    
    if (n==0) {
        if (sum==0) return state[0][0] = 1;
        else return state[0][sum] = MAX;
    }

    if (n < 0) return MAX;
    if (sum < 0) return MAX;
    
    if (state[n][sum] != UNUSED) {
        return state[n][sum];
    }
    
    int mini = MAX;
    int tsum = 0;
    int mul = 1;
    //int exp = 0;
    int cexp = 0;
    for (int i=1; ; ++i) {
        if (n-i<0) break;
        //if (input[n-i]-'0') {
            tsum += (input[n-i]-'0')*mul;
            if (mul < 10000) mul*=10;
            //mul = _min(10000, mul*10);
            
            if (tsum>sum) break;
            mini = _min(mini, memo(n-i, sum-tsum));
        /*} else {
            mul = _min(10000, mul*10);
            mini = _min(mini, memo(eq, n-i, sum-tsum));
        }*/
    }
    
    state[n][sum]=mini+1;
    //printf("aff (%d, %d)=%d\n", n, sum, state[n][sum]);
    
    return state[n][sum];
}

int main() {
    //memset(state, UNUSED, sizeof state);
    
    //printf("%d\n", state[382][4182]);
    
    scanf("%s", inputr);
    int len = strlen(inputr);
    int eq;
    for (int i=len-1; i>=0; --i) {
        if (inputr[i] == '=') {
            eq = i;
            break;
        }
    }
    
    int sum = 0;
    for (int i=eq+1; i<len; ++i) {
        sum = sum*10 + inputr[i]-'0';
    }
    
    int maxn = 0;
    int zeros = 0;
    for (int i=0; i<eq; ++i) {
        input[maxn++]=inputr[i];
        if (inputr[i]-'0' == 0) {   
            zeros++;
        } else {
            zeros = 0;
        }
        if (zeros > 4) {
            --maxn;
        }
    }
    
    /*for (int i=0; i<maxn; ++i) {
        putchar(input[i]);
    }
    printf("\n");*/
    
    /*int tsum;
    int mul;
    int mini;
    
    tsum = 0;
    mul = 1; 
    */
    printf("%d\n", memo(maxn, sum)-2);
    
    return 0;
}