#include<stdio.h>

int textl[100010];

int getstrlen() {
    
    char c;
    int strlen=0;
    while ((c=getchar())<'a' || c>'z');
    do {
        strlen++;
    } while ((c=getchar())>='a' && c <= 'z');
    return strlen;
}

int getint() {
    int x=0;
    char sgn=1;
    char c;
    while ((c=getchar())=='\n' || c=='\r' || c==' ');
    do {
        if (c=='-') {
            sgn=-1;
        } else {
            x = x*10 + c-'0';
        }
    } while ((c=getchar())>='0' && c <= '9');
    return x*sgn;
}

int loopv1(int N, int L, int w) {
    int reql = 1;
    int sum=0;
    for (int i=0; i<N; ++i) {
        if (sum + textl[i] + 1 <= w + 1) {
            sum = sum + textl[i] + 1;
        } else {
            sum = textl[i] + 1;
            reql++;
        }
        if (reql > L) {
            return 1;
        }
    }
    return -1;
}

int main() {
    int L, N, maxwl, lsum;
    while(1) {
        L=getint();
        N=getint();
        if (L==-1 && N==-1) break;
        maxwl=-1;
        lsum=0;
        for (int i=0; i<N; ++i) {
            textl[i] = getstrlen();
            lsum += textl[i];
            if (maxwl < textl[i]) maxwl = textl[i];
        }
        //printf("maxwl=%d\n", maxwl);
        lsum += N-1;
        if (L >= N) {
            printf("%d\n", maxwl);
        } else {
            int u=maxwl, v=lsum+1, c, tr;
            while(u<v) {
                c=(u+v)>>1;
                //printf("u=%d, v=%d, c=%d\n", u, v, c);
                tr = loopv1(N,L,c);
                if (tr == -1) {
                    v=c;
                } else {
                    u=c+1;
                }
            }
            printf("%d\n", u);
        }
    }
}