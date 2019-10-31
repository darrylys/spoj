#include<stdio.h>

#define ull unsigned long long

inline ull longrun(int sx, int sy, int fx, int fy) {
    ull n = fx-sx;
    return (n+1)*(n+2)*(n+3)/6 - n - 1;
}

inline ull shortrun(int sx, int sy, int fx, int fy) {
    return fx-sx+1;
}

ull csg(int sx, int sy, 
        int nx, int ny, 
        int mx, int my,
        int fx, int fy) {
    return shortrun(sx, sy, nx-1, ny) * longrun(nx+1, ny, fx, fy) + 
           longrun(sx, sy, mx-1, my) * shortrun(mx+1, my, fx, fy);
}

int main() {
    int t;
    ull k;
    scanf("%d", &t);
    while (t--) {
        scanf("%llu", &k);
        
        int u=4, v=10001, c;
        while (u<v) {
            c = (u+v)/2;
            ull chv = csg(0,0, c/2 ,1, c/2 ,3, c-1, 4);
            if (chv > k) {
                v = c;
            } else if (chv < k) {
                u = c+1;
            } else {
                u = c;
                break;
            }
        }
        printf("%d\n", u);
    }
}
