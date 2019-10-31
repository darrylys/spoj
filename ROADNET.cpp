#include<cstdio>

int roadmap[205][205];

int main() {
    int t, n, a;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                scanf("%d", &roadmap[i][j]);
            }
        }
        for (int i=0; i<n; i++) {
            for (int j=i+1; j<n; j++) {
                bool sebelah = true;
                for (int k=0; k<n; k++) {
                    if (k!=i && 
                        k!=j && 
                        (roadmap[i][k] + roadmap[k][j] == roadmap[i][j])) {
                        sebelah = false;
                        break;
                    }
                }
                if (sebelah) printf("%d %d\n", i+1, j+1);
            }
        }
        if (t>0) printf("\n");
    }
    return 0;
}