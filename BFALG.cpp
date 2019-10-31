#include<stdio.h>

#define SQRT 32000
#define NUM 0
#define EXP 1
#define P 0
#define A 1
#define B 2
#define EQ 0
#define LT 1
#define GT 2
#define ll long long

int prime[SQRT];
bool flag[SQRT];
int factor[3][50][2];
int fibseq[46];

void makefib() {
    fibseq[0] = 0;
    fibseq[1] = 1;
    for (int i=2; i<=45; i++) {
        fibseq[i] = fibseq[i-1] + fibseq[i-2];
    }
}

typedef struct {
    int m[2][2];
} Box;

typedef struct {
    int a;
    int b;
} Pair;

int big_mod(int base, int exp, int mod) {
    if (exp == 0) return 1;
    if (exp == 1) return base%mod;
    else {
        if (exp%2 == 0) {
            int res = big_mod(base, exp>>1, mod);
            return (int)((((ll)res%mod)*((ll)res%mod))%mod);
        } else {
            int res = big_mod(base, exp>>1, mod);
            return (int)((((((ll)res%mod)*((ll)res%mod))%mod)*((ll)base%mod))%mod);
        }
    }
}

int gcd(int a, int b) {
    if (b == 0) return a;
    else return gcd(b, a%b);
}

int lcm(int a, int b) {
    return (int)((ll)a*b/gcd(a,b));
}

Box make_base() {
    Box base;
    base.m[0][0] = 1;
    base.m[0][1] = 1;
    base.m[1][0] = 1;
    base.m[1][1] = 0;
    
    return base;
}

Box multiply(Box &a, Box &b, int MOD) {
    Box c;
    c.m[0][0] = (int)(((ll)a.m[0][0]*b.m[0][0] + (ll)a.m[0][1]*b.m[1][0])%((ll)MOD));
    c.m[0][1] = (int)(((ll)a.m[0][0]*b.m[0][1] + (ll)a.m[0][1]*b.m[1][1])%((ll)MOD));
    c.m[1][0] = (int)(((ll)a.m[1][0]*b.m[0][0] + (ll)a.m[1][1]*b.m[1][0])%((ll)MOD));
    c.m[1][1] = (int)(((ll)a.m[1][0]*b.m[0][1] + (ll)a.m[1][1]*b.m[1][1])%((ll)MOD));
    return c;
}

int fast_exp(int base, int n) {
    if (n == 0) return 1;
    if (n == 1) return base;
    int a = fast_exp(base,n>>1);
    if (n&1) {
        return a*a*base;
    } else {
        return a*a;
    }
}

Box fibo(int n, Box &base, int mod) {
    if (n == 1) {
        return base;
    }
    Box c = fibo(n>>1, base, mod);
    if (n&1) { //odd
        Box mid = multiply(c, base, mod);
        return multiply(c, mid, mod);
    } else { //even
        return multiply(c,c,mod);
    }
}

int int_fibo(int n, Box &base, int mod) {
    Box c = fibo(n, base, mod);
    return c.m[0][1];
}

void factorize(int n, int NOP, int id) {
    int cntr = 0;
    int num = n;
    int e = 0;
    int p = 1;
    while (cntr < NOP && num > 1) {
        
        if (num % prime[cntr] == 0) {
            e = 0;
            while (num % prime[cntr] == 0) {
                num /= prime[cntr];
                e++;
            }
            factor[id][p][NUM] = prime[cntr];
            factor[id][p][EXP] = e;
            p++;
        }
        cntr++;
    }
    if (num > 1) {
        factor[id][p][NUM] = num;
        factor[id][p][EXP] = 1;
        p++;
    }
    factor[id][0][0] = p;
}

int make_prime() {
    int i, cntr = 1;
    prime[0] = 2;
    for (i=3; i*i <= SQRT; i+=2) {
        if (!flag[i]) {
            prime[cntr++] = i;
            for (int j=i*i; j< SQRT; j+= (i<<1)) {
                flag[j] = true;
            }
        }
    }
    
    for (; i<SQRT; i+=2) {
        if (!flag[i]) prime[cntr++] = i;
    }
    return cntr;
}

Pair find_cycl2(int a, int p, int nop, int id, bool factorP) {
    Pair result;
    int sid, idx;
    int max = 0;
    int precycle, cyclelen;
    factorize(a, nop, id);
    if (factorP) factorize(p, nop, P);
    
    sid = 1;
    cyclelen=1;
    
    for (int i=1; i<factor[P][0][0]; i++) {
        cyclelen *= fast_exp(factor[P][i][NUM], factor[P][i][EXP]-1)
                    * (factor[P][i][NUM]-1);
    }
    
    result.a = 100;
    result.b = cyclelen;
    return result;
}

//not used since it gives WA but don't know where is the bug.
Pair find_cycl(int a, int p, int nop, int id, bool factorP) {
    Pair result;
    int sid, idx;
    int max = 0;
    int precycle, cyclelen;
    factorize(a, nop, id);
    if (factorP) factorize(p, nop, P);
    
    sid = 1;
    cyclelen = 1;
    for (int i=1; i<factor[P][0][0]; i++) {
        
        if (sid >= factor[id][0][0]) {
            cyclelen *= fast_exp(factor[P][i][NUM], factor[P][i][EXP]-1)
                            * (factor[P][i][NUM]-1);
            continue;
        }
        
        if (sid < factor[id][0][0]) {
            if (factor[id][sid][NUM] == factor[P][i][NUM]) {
                if (factor[P][i][EXP] > factor[id][sid][EXP]) {
                    int diff = factor[P][i][EXP] - factor[id][sid][EXP];
                    int step;
                    if (diff % factor[id][sid][EXP] == 0) {
                        step = diff/factor[id][sid][EXP];
                    } else {
                        step = diff/factor[id][sid][EXP]+1;
                    }
                    if (max < step) max = step;
                } else {
                    if (max < 0) max = 0;
                }
                sid++;
            } else { //take notes
                cyclelen *= fast_exp(factor[P][i][NUM], factor[P][i][EXP]-1)
                            * (factor[P][i][NUM]-1);
            }
        }
        
    }
    
    precycle = max+1;
    result.a = precycle;
    result.b = cyclelen;
    return result;
}

int compare(int n, int val) {
    int i;
    for (i=0; i<n; i++) {
        if (fibseq[i] > val) {
            return GT;
        }
    }
    if (fibseq[n] > val) return GT;
    if (fibseq[n] == val) return EQ;
    else return LT;
}

int main() {
    int nop = make_prime();
    makefib();                  //generate small fibonaci numbers
    int test, a, b, p, n, fn, cycl, prec, exp, part1, part2, cn = 1;
    scanf("%d", &test);
    Pair aa, bb;
    Box base = make_base();
    while (test--) {
        scanf("%d %d %d %d", &a, &b, &p, &n);
        aa = find_cycl2(a,p,nop,A,true);
        bb = find_cycl2(b,p,nop,B,false);
        
        //printf("a = %d, precycle=%d, cyclelength=%d\n", a, aa.a, aa.b);
        //printf("b = %d, precycle=%d, cyclelength=%d\n\n", b, bb.a, bb.b);
        
        //for number a, take f(n)?
        //special case, n = 1,2,3
        if (n <= 3) {
            if (n==1) part1 = a;
            else if (n==2) part1 = 1;
            else part1 = a;
        } else {
            cycl = aa.b; prec = aa.a;
            int cmp = compare(n-2, prec);
            //printf("cmp = %d\n", cmp);
            if (cmp == GT) {
                fn = int_fibo(n-2, base, cycl);
                //printf("a.fn = %d, a.cycl=%d, a.prec=%d\n", fn, cycl, prec);
                fn -= prec%cycl;
                if (fn < 0) fn += cycl; //fn <-- v
                exp = fn + prec;
                part1 = big_mod(a, exp, p);
            } else { //smaller than 30
                part1 = big_mod(a, fibseq[n-2], p);
            }
        }
        //printf("part1 = %d\n", part1);
        
        //for number b, take f(n+1)?
        //special case, n=1,2
        if (n <= 2) {
            if (n==1) part2 = 1;
            else part2 = b;
        } else {
            cycl = bb.b; prec = bb.a;
            int cmp = compare(n-1, prec);
            //printf("cmp = %d\n", cmp);
            if (cmp == GT) {
                fn = int_fibo(n-1, base, cycl);
                //printf("b.fn = %d, a.cycl=%d, a.prec=%d\n", fn, cycl, prec);
                fn -= prec%cycl;
                if (fn < 0) fn += cycl; //fn <-- v
                exp = fn + prec;
                part2 = big_mod(b, exp, p);
            } else { //if fibonaci is smaller than 30, just BRUTE FORCE
                part2 = big_mod(b, fibseq[n-1], p);
            }
        }
        //printf("part2 = %d\n", part2);
        printf("Case #%d: %d\n", cn++, (int)(((ll)part1 * part2)%p));
        
        //putchar('\n');
    }
    return 0;
}