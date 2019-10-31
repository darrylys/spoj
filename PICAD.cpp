#include<cstdio>
#include<cstdlib>

#define MAXINT (int)1e9
#define N 5005
#define START false
#define END true

typedef struct {
    int point;
    bool kind;
} Man;

Man man[N*2];

int _min(int a, int b) { return (a<=b)?a:b; }
int _max(int a, int b) { return (a>=b)?a:b; }

int cmp(const void *o1, const void *o2) {
    Man* a = (Man*)o1;
    Man* b = (Man*)o2;
    
    int r = a->point - b->point;
    if (!r) {
        return (int)(a->kind) - (int)(b->kind);
    }
    return r;
}

int main() {
    int p, k, a, b, n, tn;
    int start, end, max, mul, min, prev;
    while (scanf("%d%d", &p, &k)==2) {
        scanf("%d", &n);
        tn = 0;
        for (int i=0; i<n; i++) {
            scanf("%d%d", &a, &b);
            if ((a >= p && a <= k) || 
                (b >= p && b <= k) || 
                (a < p && b > k)) {
                man[tn].point = _max(a,p);
                man[tn].kind = START;
                tn++;
                man[tn].point = _min(b, k);
                man[tn].kind = END;
                tn++;
            }
        }
        man[tn].point = -1;
        man[tn].kind = END;
            
        if (tn == 0) printf("0 0\n");
        else {
            qsort(man, tn, sizeof(man[0]), cmp);
            max = 0;
            min = MAXINT;
            mul = 0;
            if (man[0].point > p || man[tn-1].point < k) {
                min = 0;
            }
            for (int i=0; i<tn;) {
                prev = man[i].point;
                if (man[i].kind == START) {
                    start = 0;
                    while (man[i].point == prev && 
                              man[i].kind == START) {
                        start++;
                        i++;
                    }
                    mul += start;
                    if (mul > max) max = mul;
                    if (mul < min) min = mul;
                } else {
                    end = 0;
                    while (prev == man[i].point && 
                            man[i].kind == END) {
                        end++;
                        i++;
                    }
                    if (man[i].point == -1) {
                        if (man[i-1].point < k) mul -= end;
                    } else mul -= end;
                    if (mul < min) min = mul;
                }
                //printf("i=%d min=%d max=%d\n", i, min, max);
            }
            printf("%d %d\n", min, max);
        }
    }
    return 0;
}