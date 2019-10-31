#include<stdio.h>
#include<string.h>


// THIS IS BASICALLY CHEATING!!! BRUTE FORCED TO FIND THE FIBONACCI PATTERN
// IN THE WORLD OF MOD 1000000007 (found cycle length of 2000000016)
// AND IN THE WORLD OF MOD 2000000016 found fibonacci cycle length of 329616
// THINGS BECAME SOOOO SIMPLE AFTER KNOWING THESE INFORMATION
#define OUCK 2000000016
#define INCK 329616
#define MOD 1000000007
#define ll long long

typedef struct {
    int m[2][2];
} Mat;

Mat mul(Mat& a, Mat& b, int mod) {
    Mat c;
    for (int i=0; i<2; ++i) {
        for (int j=0; j<2; ++j) {
            c.m[i][j] = 0;
            for (int k=0; k<2; ++k) {
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

int getn(char* sn, int mod) {
    int sum=0;
    int len = strlen(sn);
    for (int i=0; i<len; ++i) {
        sum = (int)(((ll)sum*10 + sn[i]-'0')%mod);
    }
    return sum;
}

Mat getid() {
    Mat id;
    id.m[0][0] = id.m[1][1] = 1;
    id.m[0][1] = id.m[1][0] = 0;
    return id;
}

Mat getbase() {
    Mat b;
    b.m[0][0] = b.m[0][1] = b.m[1][0] = 1;
    b.m[1][1] = 0;
    return b;
}

int main() {
    int t, n;
    char strn[105];
    Mat ID = getid();
    Mat base = getbase();
    
    scanf("%d", &t);
    while (t--) {
        scanf("%s", strn);
        if (strlen(strn) == 1 && strn[0] <= '1') {
            printf("%c\n", strn[0]);
            continue;
        }
        
        //printf("strn=%s\n", strn);
        n = getn(strn, INCK);
        //printf("n=%d\n", n);
        Mat e = mexp(n, OUCK, ID, base);
        //printf("ee=%d\n", e.m[1][0]);
        Mat c = mexp(e.m[1][0], MOD, ID, base);
        printf("%d\n", c.m[1][0]);
    }
}