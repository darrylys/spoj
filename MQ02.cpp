#include<stdio.h>
#include<string.h>

int sumarray[1000010];
int maxleng0[1000010];

void pra(int* v, int l) {
    printf("====================\n");
    for (int i=0; i<l; ++i) {
        printf("%d ", v[i]);
    }
    printf("\n====================\n");
}

inline int max(int a, int b) {
    return (a>b)?a:b;
}

int getstring() {
    char c;
    int val;
    int idx=1;
    sumarray[0] = 0;
    while ((c=getchar())=='\n' || c=='\r');
    do {
        
        if (c>='a' && c<='z') {
            val=c-'a'+1;
        } else if (c>='A' && c<='Z') {
            val=c-'A'+51;
        } else {
            val=32;
        }
        
        sumarray[idx] = sumarray[idx-1] + val;
        idx++;
        
        c=getchar();
    } while (c!='\n' && c!='\r');
    
    //printf("SUMARRAY\n");
    //pra(sumarray, idx);
    
    return idx;
}

int getint() {
    char c;
    int s=0;
    while ((c=getchar())<'0' || c > '9');
    do {
        s=s*10+c-'0';
        c=getchar();
    } while (c>='0' && c<='9');
    return s;
}

void mapmod(int m, int len) {
    memset(maxleng0, -1, (m+1)*sizeof(maxleng0[0]));
    
    for (int i=1; i<len; ++i) { //sumarray starts from 1 and ends in stringlength+1
        maxleng0[sumarray[i]%m] = max(maxleng0[sumarray[i]%m], i-1);
    }
    
    //printf("MAXLEN0ARRAY\n");
    //pra(maxleng0, len);
}

int main() {
    int t;
    t=getint();
    while(t--){
        int len = getstring();
        int m = getint(), k=getint();
        //printf("%d %d %d\n", len, m, k);
        int tempmax, tempi;
        mapmod(m, len);
        
        tempmax=-1;
        tempi=0;
        for (int i=1, want; i<len; ++i) {
            
            want = (k+sumarray[i-1])%m;
            if (maxleng0[want]-(i-1) > tempmax) {
                tempmax=maxleng0[want]-(i-1);
                tempi=i-1;
                
                if (i >= len-tempmax) {
                    break;
                }
            }
            
        }
        
        if (tempmax == -1) printf("-1\n");
        else {
            printf("%d %d\n", tempi, tempmax+1);
        }
    }
    return 0;
}
