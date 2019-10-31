#include<stdio.h>
#include<stdlib.h>

#define ll long long

int xs[100], ys[100], vs[100];

int adj(int v) {
    if (v%11) {
        return (int)((ll)10*v/11+1);
    } else {
        return (int)((ll)10*v/11);
    }
}

int cmp(const void * a, const void * b) {
    return ( xs[*(int*)a] - xs[*(int*)b] );
}

int ndigits(int t) {
    int n=0;
    while(t) {
        t/=10;
        n++;
    }
    return n;
}

int main() {
    int t, n, tmp;
    int d, dr, dl, ar, al;
    int sol;
    int exp[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};
    
    scanf("%d", &t);
    while(t--) {
        scanf("%d", &d);
        
        n = ndigits(d);
        
        sol = 0;
        
        if (d % 2) {
            // can only kill the last digit.
            al = adj(d);
            xs[sol] = al;
            ys[sol] = al/10;
            if (xs[sol] + ys[sol] == d) {
                vs[sol] = sol;
                sol++;
            }
            
        } else {
            for (int i=1; i<=n; ++i) { //check for each thrown away
                dl = d / exp[n-i];
                dr = d % exp[n-i];
                
                //1
                ar = dr/2;
                al = adj(dl);
                xs[sol] = al*exp[n-i]+ar;
                ys[sol] = al/10*exp[n-i]+ar;
                if (xs[sol] + ys[sol] == d && al) {
                    vs[sol] = sol;
                    ++sol;
                }
                
                if (i<n) {
                    //2
                    ar = (exp[n-i]+dr)/2;
                    al = adj(dl-1);
                    xs[sol] = al*exp[n-i]+ar;
                    ys[sol] = al/10*exp[n-i]+ar;
                    if (xs[sol] + ys[sol] == d && al) {
                        vs[sol] = sol;
                        ++sol;
                    }
                }
            }
            
        }
        
        qsort(vs, sol, sizeof(int), cmp);
        int xsol = 0;
        int x=-1;
        for (int i=0; i<sol; ++i) {
            if (xs[vs[i]] != x) {
                x = xs[vs[i]];
                xsol++;
            }
        }
        
        
        printf("%d\n", xsol);
        x = -1;
        for (int i=0, a, b; i<sol; ++i) {
            if (x != xs[vs[i]]) {
                a = ndigits(xs[vs[i]]);
                b = ys[vs[i]]?ndigits(ys[vs[i]]):1;
                //printf("::: a=%d, b=%d\n", a, b );
                printf("%d + ", xs[vs[i]]);
                for (int j=b; j<a-1; j++) {
                    putchar('0');
                }
                printf("%d = %d\n", ys[vs[i]], d);
                x = xs[vs[i]];
            }
            //printf("%d + %d = %d\n", xs[vs[i]], ys[vs[i]], d);
        }
    }
    return 0;
}
