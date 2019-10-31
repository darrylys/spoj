#include<stdio.h>

#define ll long long

typedef struct {
    int m[3][3];
} Mat;

Mat getid() {
    Mat id;
    for (int i=0; i<3; ++i) {
        for (int j=0; j<3; ++j) {
            id.m[i][j] = i==j;
        }
    }
    return id;
}

Mat getbase() {
    Mat b;
    b.m[0][0] = 1;
    b.m[0][1] = 0;
    b.m[0][2] = 0;
    b.m[1][0] = 1;
    b.m[1][1] = 4;
    b.m[1][2] = 1;
    b.m[2][0] = 0;
    b.m[2][1] = -1;
    b.m[2][2] = 0;
    return b;
}

Mat mul(Mat& a, Mat& b, int mod) {
    Mat c;
    for (int i=0; i<3; ++i) {
        for (int j=0; j<3; ++j) {
            c.m[i][j] = 0;
            for (int k=0; k<3; ++k) {
                c.m[i][j] = (int)(((ll)c.m[i][j] + ((ll)a.m[i][k] * b.m[k][j])%mod)%mod);
            }
        }
    }
    return c;
}

Mat mexp(int exp, int mod, Mat& ID, Mat& base) {
    if (exp==0) {
        return ID;
    }
    if (exp==1) {
        return base;
    }
    
    Mat half = mexp(exp>>1, mod, ID, base);
    if (exp&1) {
        Mat half2 = mul(half, half, mod);
        return mul(half2, base, mod);
    } else {
        return mul(half, half, mod);
    }
}

int main() {
    Mat ID = getid();
    Mat BASE = getbase();
    
    int t, N, M, I, J, K, sum;
    scanf("%d", &t);
    while(t--) {
        BASE.m[2][1]=-1;
        scanf("%d %d %d %d %d", &N, &M, &I, &J, &K);
        if (N&M&1) {
            if (N==1) {
                printf("%d\n", J&1);
            } else {
                if ((I&1) == (J&1)) {
                    if (I&1) { //1|3
                        //printf("odd I=%d, J=%d\n", I, J);
                        int rspace = (M-J)>>1;
                        int lspace = (J-1)>>1;
                        
                        BASE.m[2][1] += K;
                        Mat rmt = mexp(rspace, K, ID, BASE);
                        Mat lmt = mexp(lspace, K, ID, BASE);
                        
                        //l-1
                        sum = (int)(((ll)lmt.m[1][0]+lmt.m[2][0])*((ll)rmt.m[1][1]+rmt.m[2][1])%K);
                        
                        //r-1
                        sum = (int)((sum + (int)(((ll)lmt.m[1][1]+lmt.m[2][1])*((ll)rmt.m[1][0]+rmt.m[2][0])%K))%K);
                        
                        //nor
                        sum = (int)((sum + (int)(((ll)lmt.m[1][1]+lmt.m[2][1])*((ll)rmt.m[1][1]+rmt.m[2][1])%K))%K);
                        
                        printf("%d\n", sum);
                    } else { //2
                        //printf("even I=%d, J=%d\n", I, J);
                        int rspace = (M-J-1)>>1;
                        int lspace = (J-2)>>1;
                    
                        BASE.m[2][1] += K;
                        Mat rmt = mexp(rspace, K, ID, BASE);
                        Mat lmt = mexp(lspace, K, ID, BASE);
                        
                        //rside
                        int rs = ((rmt.m[1][1]+rmt.m[2][1])%K + (rmt.m[1][0]+rmt.m[2][0])%K )%K;
                        int ls = ((lmt.m[1][1]+lmt.m[2][1])%K + (lmt.m[1][0]+lmt.m[2][0])%K )%K;
                        
                        sum = (int)((2LL*rs*ls)%K);
                        
                        printf("%d\n", sum);
                    }
                } else {
                    printf("0\n");
                }
            }
        } else {
            printf("0\n");
        }
    }
    return 0;
}
