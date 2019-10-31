#include<stdio.h>
#include<string.h>

#define ull unsigned long long

int min(int a, int b) {
    return (a<b)?a:b;
}

ull exp3[30];

void makeEXP3() {
    exp3[0] = 1;
    for (int i=1; i<30; ++i) exp3[i] = exp3[i-1]*3;
}

ull pow3(int exp) {
    if (exp<0) return 0;
    else return exp3[exp];
}

int chknum(char* N) {
    int len = strlen(N);
    
    for (int i=0; i<len/2; ++i) {
        if (N[i] != N[len-1-i] || !(N[i] <= '1' || N[i] == '8')) {
            return 0;
        }
    }
    
    if (len&1) {
        int i= len/2;
        if (!(N[i] <= '1' || N[i] == '8')) {
            return 0;
        }
    }
    return 1;
}

bool cmp(char* N, char* mN, int len) {
    for (int i=0; i<len; ++i) {
        if (N[i] < mN[i]) {
            return false;
        } else if (N[i] > mN[i]) {
            return true;
        }
    }
    return true;
}

ull calcv(char* N) {
    int len = strlen(N);
    
    //printf("len=%d\n", len);
    ull le3 = 0;
    ull beflen = 0;
    
    if (len>1) {
        beflen = 3;
        for (int i=2; i<len; ++i) {
            beflen += 2LL*pow3(i/2-(!(i&1)));
        }
    }
    
    char dig[3] = {'0','1','8'};
    
    char mN[50];
    mN[len] = '\0';
    
    char cloop=1;
    
    int lim = len/2;
    for (int i=0; i<lim && cloop; ++i) {
        
        switch (N[i]) {
            case '0': {
                mN[i] = mN[len-i-1]= '0';
            } break;
            
            case '1': {
                // 0-> fine IFF i>0
                if (i) {
                    le3 += pow3(len/2-i-1+ (len&1));
                }
                
                //1 -> match
                mN[i] = mN[len-i-1] = '1';
                /*if (N[len-i-1] < '1') {
                    cloop = 0;
                }*/
            } break;
            
            case '8': {
                //0+1 -> fine
                if (i) {
                    le3 += 2LL*pow3(len/2-i-1 + (len&1));
                } else {
                    le3 += pow3(len/2-i-1 +(len&1));
                }
                
                //8 -> match
                mN[i] = mN[len-i-1] = '8';
                /*if (N[len-i-1] < '8') {
                    cloop = 0;
                }*/
            } break;
            
            case '9': {
                // ALL ok, then finish!
                if (i) {
                    le3 += pow3(len/2-i + (len&1));
                } else {
                    le3 += 2LL*pow3(len/2-i-1 + (len&1));
                }
                
                mN[i] = mN[len-i-1] = '9';
                cloop = 0;
            } break;
            
            default: {
                // 0+1 is fine, cannot do 234567!
                le3 += pow3(len/2-i-1 + (len&1));
                
                if (i) {
                    le3 += pow3(len/2-i-1 + (len&1));
                }
                
                mN[i] = mN[len-i-1] = N[i];
                cloop = 0;
            } break;
        }
    }
    
    if (cloop) {
        if (len&1) {
            bool rcmp = true;
            for (int d=0; rcmp && d<3 && dig[d]<=N[len/2]; ++d) {
                mN[len/2] = dig[d];
                rcmp = cmp(N, mN,len);
                if (rcmp) {
                    le3++;
                }
            }
        } else {
            le3 += cmp(N,mN,len);
        }
    } 
    /*
    if (len&1) {
        for (int d=0; cloop && d<3 && dig[d]<=N[len/2]; ++d) {
            le3++;
        }
    } else {
        le3 += cloop;
    
    }
    */
    return le3+beflen;
}

int main() {
    int t; char A[50], B[50], bB[50], bA[50];
    makeEXP3();
    scanf("%d", &t);
    while (t--) {
        scanf("%s %s", A, B);
        
        //printf("A=%s, B=%s\n", A, B);
        
        if (A[0] == '0') {
            printf("%llu\n", calcv(B));
        } else {
            //printf("CALCV(B)=%llu\n", calcv(B));
            //printf("CALCV(A)=%llu\n", calcv(A));
            //printf("CHKNUM(A)=%llu\n", chknum(A));
            printf("%llu\n", calcv(B) - calcv(A) + chknum(A));
        }
        //printf("============\n");
    }
    return 0;
}
