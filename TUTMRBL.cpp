#include<stdio.h>

#define NUM 0
#define EXP 1

bool flag[4000];
int prime[2000];
int list[2000][2];

int make_prime() {
    int cntr = 0, i;
    
    flag[0] = flag[1] = true;
    prime[0] = 2;
    cntr=1;
    
    for (i=3; i*i <= 4000; i+=2) {
        if (!flag[i]) {
            prime[cntr++] = i;
            for (int j=i*i; j<4000; j+= (i<<1)) {
                flag[j] = true;
            }
        }
    }
    
    for (; i<4000; i+=2) {
        if (!flag[i]) prime[cntr++] = i;
    }
    
    return cntr;
}

int main() {
    int nop = make_prime();
    int n, num, exp, ptr, c;
    
    while (scanf("%d", &n) && n) {
        
        num = n;
        ptr = 0;
        for (int i=0; i<nop && num>1; i++) {
            
            if (num%prime[i] == 0) {
                exp = 0;
                while (num%prime[i] == 0) {
                    num /= prime[i];
                    exp++;
                }
                list[ptr][NUM] = prime[i];
                list[ptr][EXP] = exp;
                ptr++;
            }
        }
        
        if (num > 1) {
            list[ptr][NUM] = num;
            list[ptr][EXP] = 1;
            ptr++;
        }
        
        printf("%d =", n);
        for (int i=0; i<ptr; i++) {
            
            for (int j=1; j<list[i][EXP]; j++) {
                printf(" %d *", list[i][NUM]);
            }
            
            printf(" %d", list[i][NUM]);
            if (ptr-i > 1) {
                printf(" *");
            }
        }
        
        putchar('\n');
        
        c = 0;
        for (int i=1; i*i <= n; i++) {
            if (n%i == 0) {
                c++;
            }
        }
        
        printf("With %d marbles, %d different rectangles can be constructed.\n", n, c);
    }
    return 0;
}