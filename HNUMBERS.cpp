#include<stdio.h>

/*int prime[80] = {
    2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,
    103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,
    199,211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,
    313,317,331,337,347,349,353,359,367,373,379,383,389,397 };
*/
int nfactor[10];
int prime[100];
char flag[400];

int getprime() {
    
    int f = 0;
    prime[f++] = 2;
    for (int i=3; i*i <= 100000; i+=2) {
        if (!flag[i]) {
            prime[f++] = i;
            for (int j=i*i; j<400; j+=i) {
                flag[j] = 1;
            }
        }
    }
    return f;
}

int factor(int n, int* fac, int nprimes) {
    
    int val = n;
    int i = 0;
    int fc = 0;
    while (i<nprimes) {
        
        if (val%prime[i] == 0) {
            fac[fc++] = prime[i];
            do { 
                val /= prime[i];
            } while (val%prime[i] == 0);
        }
        i++;
    }
    if (val > 1) {
        fac[fc] = val;
        fc++;
    }
    return fc;
}

int main() {
    
    int t, n, m, dsum, z, tp, ct, sg;
    
    int nprimes = getprime();
    
    scanf("%d", &t);
    while(t--) {
        scanf("%d %d", &n, &m);
        //printf("getvalue\n");
        int facs = factor(n, nfactor, nprimes);
        /*printf("facs=%d\n", facs);
        if (facs == 1 && nfactor[0] == n) { //prime!
            printf("%d\n", m);
        } else {
            */
            dsum = 0;
            for (int i=1; i<(1<<facs); ++i) {
                
                z = i;
                tp = 1;
                ct = 0;
                sg = 0;
               // printf("expanding %d ==== ", z);
                while (z) {
                    if (z%2==1) {
                        tp *= nfactor[ct];
                      //  printf("%d ", nfactor[ct]);
                        sg++;
                    }
                    ct++;
                    z/=2;
                }
                
              //  printf(" === ct=%d tp=%d\n", ct, tp);
                
                if (sg%2==1) {
                    dsum += m/tp;
                } else {
                    dsum -= m/tp;
                }
                //printf(" === dsum = %d\n", dsum);
            }
            printf("%d\n", m-dsum);
        //}
    }
    
    return 0;
}
