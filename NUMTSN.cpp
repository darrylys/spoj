#include<stdio.h>
#include<string.h>

#define ll long long
#define MOD 1000000007

int C[53][53];
int _7e[53];

inline int max(int a, int b) {
    return (a>b)?a:b;
}

inline int max3(int a, int b, int c) {
    return max(a, max(b, c));
}

void buildC() { //ok
    C[0][0] = 1;
    for (int i=1; i<=51; ++i) {
        C[i][i] = C[i][0] = 1;
        for (int j=1; j<i; ++j) {
            C[i][j] = (C[i-1][j] + C[i-1][j-1])%MOD;
        }
    }
}

void build7e() { //ok
    _7e[0] = 1;
    for (int i=1; i<=51; ++i) {
        _7e[i] = (int)((7LL*_7e[i-1])%MOD);
    }
}

int freedigit(int n) { //ok
    int sum = 0;
    int tsum1 = 0;
    int tsum2 = 0;
    for (int i=1; i<=n/3; ++i) {
        tsum1 = (int)(((((ll)C[n][3*i]*C[3*i][i])%MOD*C[2*i][i])%MOD*_7e[n-3*i])%MOD);
        if (n-3*i-1 < 0) tsum2 = 0;
        else tsum2 = (int)(((((ll)C[n-1][3*i]*C[3*i][i])%MOD*C[2*i][i])%MOD*_7e[n-3*i-1])%MOD);
        sum = ((ll)sum + tsum1 - tsum2 + MOD)%MOD;
    }
    return sum;
}

int fixeddigit(int frn, bool zero, int* fixed, int di) {
    int ld = di-1;
    int spd = ld/3;
    ld += (int)zero;
    int nd = ld-spd;
    
    int m3 = max3(fixed[3], fixed[6], fixed[9]);
    int rem = 3*m3-fixed[3]-fixed[6]-fixed[9];
    
    //printf("ld=%d, spd=%d, nd=%d, frn=%d, m3=%d, rem=%d, fixed=[%d %d %d]\n", ld, spd, nd, frn, m3, rem, fixed[3], fixed[6], fixed[9]);
    
    //nd
    int ndsum = 0;
    int s3 = m3-fixed[3];
    int s6 = m3-fixed[6];
    if (m3 == 0) {
        s3++;
        s6++;
        rem = 3;
    }
    for (int i=rem; i<frn; i+=3) {
        ndsum = (int)((ndsum + ((((ll)C[frn-1][i]*C[i][s3])%MOD*C[i-s3][s6])%MOD*_7e[frn-i-1])%MOD)%MOD);
        s3++;
        s6++;
    }
    ndsum = (int)(((ll)nd*ndsum)%MOD);
    
    //printf("ndsum=%d\n", ndsum);
    
    //spd
    int spdsum = 0;
    int spa[10];
    spa[3] = fixed[3];
    spa[6] = fixed[6];
    spa[9] = fixed[9];
    
    for (int i=1, spm3, sprem, sps3, sps6, pd; i<=spd;++i) {
        pd = i*3;
        spa[pd]++;
        spm3 = max3(spa[3], spa[6], spa[9]);
        sprem = 3*spm3-spa[3]-spa[6]-spa[9];
        sps3 = spm3-spa[3];
        sps6 = spm3-spa[6];
        
        for (int i=sprem; i<frn; i+=3) {
            spdsum = (int)((spdsum + ((((ll)C[frn-1][i]*C[i][sps3])%MOD*C[i-sps3][sps6])%MOD*_7e[frn-i-1])%MOD)%MOD);
            sps3++;
            sps6++;
        }
        
        spa[pd]--;
    }
    
    //printf("spdsum=%d\n", spdsum);
    
    return (ndsum+spdsum)%MOD;
}

int calc(char* val) {
    int len = strlen(val);
    //printf("val=%s, len=%d\n", val, len);
    int sum = 0;
    for (int i=3; i<len; ++i) {
        sum = (sum + freedigit(i))%MOD;
    }
    //printf("sum=%d\n", sum);
    
    int fixed[10] = {0,0,0,0,0,0,0,0,0,0};
    
    for (int i=0; i<len; ++i) {
        int tsum = fixeddigit(len-i, i>0, fixed, val[i]-'0');
        fixed[val[i]-'0']++;
        
        sum = (sum + tsum)%MOD;
    }
    
    if (fixed[3] == fixed[6] && fixed[6] == fixed[9] && fixed[3]) {
        sum ++;
    }
    
    return sum%MOD;
}

void decr(char* val) {
    int len = strlen(val);
    int carry = 1;
    for (int i=len-1; i>=0; --i) {
        val[i] = val[i]-carry;
        if (val[i] < '0') {
            carry = 1;
            val[i] += 10;
        } else {
            carry = 0;
            break;
        }
    }
    int p = 0;
    while (p<len-1 && val[p] == '0') {
        ++p;
    }
    
    for (int i=p; i<len; ++i) {
        val[i-p] = val[i];
    }
    
    val[len-p] = '\0';
}

int main() {
    int t;
    char A[52];
    char B[52];
    
    buildC();
    build7e();
    
    scanf("%d", &t);
    while (t--) {
        scanf("%s %s", A, B);
        
        decr(A);
        
        /*
        printf("A=%s, B=%s\n", A, B);
        for (int i=1; i<20; ++i) {
            printf("%d. %d\n", i, freedigit(i));
        }
        */
        
        
        int lena = strlen(A);
        int lenb = strlen(B);
        
        int va = (lena >= 3) ? calc(A) : 0;
        int vb = (lenb >= 3) ? calc(B) : 0;
        
        //printf("va=%d, vb=%d ", va, vb);
        
        printf("%d\n", (vb-va+MOD)%MOD);
        
    }
    return 0;
}
