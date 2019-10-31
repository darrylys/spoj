#include<stdio.h>

#define MAXNM 100010

char A[MAXNM];
char B[MAXNM];

inline int min(int a, int b) {
    return (a<b)?a:b;
}

int getclosest0(char* buf, int n, int inc, int start) {
    int d = 0;
    for (int i=start; i!=n; i+=inc) {
        if (buf[i] == '0') {
            return d;
        } else {
            d++;
        }
    }
    return d;
}

int getnumof1(char* buf, int n) {
    int x = 0;
    for (int i=0; i<n; ++i) {
        x += buf[i]-'0';
    }
    return x;
}

int main() {
    int t, na, nb, la, lb, ra, rb;
    scanf("%d", &t);
    while (t--) {
        scanf("%d %s", &na, A);
        scanf("%d %s", &nb, B);
        
        int a_no1 = getnumof1(A, na);
        int b_no1 = getnumof1(B, nb);
        
        printf("%d ", (a_no1 && b_no1) ? (a_no1 + b_no1 - 1) : 0);
        
        int ahas0 = getclosest0(A, na, 1, 0);
        int bhas0 = getclosest0(B, nb, 1, 0);
        if (ahas0 == na && bhas0 == nb) {
            printf("%d\n", a_no1 + b_no1 - 1);
        } else if (ahas0 == na) {
            printf("%d\n", b_no1);
        } else if (bhas0 == nb) {
            printf("%d\n", a_no1);
        } else {
            la = ahas0;
            lb = bhas0;
            
            ra = getclosest0(A, 0, -1, na-1);
            rb = getclosest0(B, 0, -1, nb-1);
            
            int dx1 = lb*(A[0]-'0');
            int dy1 = la*(B[0]-'0');
            int dx2 = rb*(A[na-1]-'0');
            int dy2 = ra*(B[nb-1]-'0');
            
            printf("%d\n", min(dx1, dy1) + min(dx2, dy2));
            
        }
    }
    return 0;
}
