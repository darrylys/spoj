#include<stdio.h>
#include<string.h>

//#define DEBUG

typedef struct {
    int a[205];
} ARZ;

char text[210];
int zid[210];

ARZ getID() {
    ARZ arz;
    for (int i=1; i<=200; ++i) {
        arz.a[i] = i;
    }
    return arz;
}

ARZ msmul(ARZ& a, ARZ& b, int n) {
    ARZ c;
    for (int i=1; i<=n; ++i) {
        c.a[i] = b.a[a.a[i]];
    }
    return c;
}

ARZ msexp(ARZ& base, int exp, ARZ& ID, int n) {
    if (exp == 0) return ID;
    if (exp == 1) return base;
    
    ARZ half = msexp(base, exp>>1, ID, n);
    
    ARZ mhalf = msmul(half, half, n);
    
    if (exp & 1) {
        mhalf = msmul(mhalf, base, n);
    }
    
    return mhalf;
}

int main() {
    int n, k;
    ARZ ID = getID();
    ARZ base;
    ARZ fr;
    
    while (scanf("%d", &n) && n) {
        for (int i=1, v; i<=n; ++i) {
            scanf("%d", &v);
            base.a[v] = i;
        }
        
        #ifdef DEBUG
        printf("base.a[");
        for (int i=1; i<=n; ++i) {
            printf("%d ", base.a[i]);
        }
        printf("]\n");
        #endif
        
        while (scanf("%d", &k) && k) {
            
            char c=getchar();
            int tid = 0;
            while ((c=getchar()) != '\n' && c != '\r') {
                text[tid++] = c;
            }
            
            for (int i=tid; i<n; ++i) {
                text[i] = ' ';
            }
            text[n] = '\0';
            
            #ifdef DEBUG
            printf("text=%s\n", text);
            #endif
            
            fr = msexp(base, k, ID, n);
            
            for (int i=0; i<n; ++i) {
                putchar(text[fr.a[i+1]-1]);
            }
            putchar('\n');
        }
        
        putchar('\n');
    }
    return 0;
}
