#include<stdio.h>
#include<string.h>

int to_string(int c, char* arr) {
    
    int cntr = 0;
    while (c) {
        arr[cntr++] = (c%10)+'0';
        c /= 10;
    }
    return cntr;
}

int smallest_absurdity(int c) {
    int d = c/20;
    
    char strleft[13];
    char strright[13];
    
    int dleft = to_string(c-d, strleft);
    int dright = to_string(c+d, strright);
    
    //printf("dleft=%d, dright=%d\n", dleft, dright);
    int digs, ld;
    
    while (dright > dleft) strleft[dleft++] = '0';
    
    for (int i=dright-1, digs = 1; i>=0; i--) {
        if (strleft[i] == strright[i]) digs++;
        else {
            if ('5' > strleft[i] && '5' <= strright[i] && strleft[i] > '0') {
                return 2*digs-1;
            } else if (strleft[i] == '5') {
                
                for (int j=i-1; j>=0; j--) {
                    if (strleft[j] > '0') {
                        return 2*digs;
                    }
                }
                
                return 2*digs-1;
            } else if (strleft[i] == '0') {
                
                for (int j=i-1; j>=0; j--) {
                    if (strleft[j] > '0') {
                        if (strright[i] >= '5') return 2*digs-1;
                        else return 2*digs;
                    }
                }
                
                if (strleft[i+1] == '5') return (2*(digs-1)-1);
                else return 2*(digs-1);
                
            } else {
                return 2*digs;
            }
        }
    }
    return 1000; //only [1,19] can go here. they MUST BE not absurd.
}

int get_absurdity(int c) {
    
    int digs = 0;
    int f = -1, lastdig;
    
    while (c) {
        if (c % 10) {
            if (f == -1) {
                lastdig = c%10;
                f = 0;
            }
            digs++;
        } else {
            if (f == 0) digs++;
        }
        c /= 10;
    }
    
    if (lastdig == 5) return digs*2-1;
    else return digs*2;
}

bool brute_force(int c) {
    int d = c/20;
    
    int cb = get_absurdity(c), n;
    
    for (int i=c-d; i<=c+d; i++) {
        n = get_absurdity(i);
        
        if (cb > n) {
            return true;
        }
    }
    return false;
}

int main() {
    int testcase, c, sm, ab;
    int mode = 1;
    
    scanf("%d", &testcase);
    while (testcase--) {
        scanf("%d", &c);
        
        
        
        if (mode == 1) {
            sm = smallest_absurdity(c);
            ab = get_absurdity(c);
            //printf("sm=%d ab=%d\n", sm, ab);
            if (ab > sm) printf("absurd\n");
            else printf("not absurd\n");
        } else {
            if (brute_force(c)) {
                printf("absurd\n");
            } else {
                printf("not absurd\n");
            }
        }
        
        //putchar('\n');
    }
    return 0;
}