#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int fac[8];

int main() {
    char in[25];
    unsigned long long mz;
    
    while (scanf("%s", in) != EOF) {
        
        for (int i=0; i<8; ++i) fac[i]=0;
        mz=1;
        
        for (int i=0; in[i] != '\0'; ++i) {
            if (in[i] > '1') {
                switch (in[i]) {
                    case '2': fac[2]++; break;
                    case '3': fac[3]++; break;
                    case '4': fac[2]+=2; break;
                    case '5': fac[5]++; break;
                    case '6': fac[2]++; fac[3]++; break;
                    case '7': fac[7]++; break;
                    case '8': fac[2]+=3; break;
                    case '9': fac[3]+=2; break;
                    default: break;
                }
            }
            if (in[i] != '0') mz *= (in[i]-'0');
        }
        /*
        if (mz == 1) {
            printf("1\n");
            continue;
        }
        */
        if (fac[3]&1 || fac[7]&1) {
            printf("0\n");
        } else {
        
            int B = (fac[5]+1)<<2;
            /*
            if (B&1) {
                if (fac[2]&1) {
                    printf("%d\n", (B-1)>>1);
                } else {
                    printf("%d\n", (B+1)>>1);
                }
            } else {
                printf("%d\n", B>>1);
            }
            
            */
            
            if (B&7 == 0) {
                printf("%d\n", B>>3);
            } else {
                printf("%d\n", (B+4)>>3);
            }
            
            
            
        }
    }
}