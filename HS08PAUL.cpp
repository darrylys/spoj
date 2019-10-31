#include<stdio.h>
#include<string.h>

#define TRUE false
#define FALSE true

bool oflag[10000000];
int nums[10000000];
bool sys[10000000];
bool flag[100005];
/*
void sieve(int L,int U) {
    int i,j,d;
    d=U-L+1; 
    
    memset(flag, TRUE, d*sizeof(bool));
    for (i=(L%2!=0);i<d;i+=2) flag[i]=FALSE;
    for (i=3;i*i<=U;i+=2) {
        if (i>L && flag[i-L] == FALSE) continue;
        j=L/i*i; if (j<L) j+=i;
        if (j==i) j+=i; 
        j-=L; 
        for (;j<d;j+=i) flag[j]=FALSE;
    }
    if (L<=1) flag[1-L]=FALSE;
    if (L<=2) flag[2-L]=TRUE;
    
    for (i=0; i<d; i++) oflag[L+i] = !flag[i];
}
*/

void make_prime() {
    oflag[0] = oflag[1] = true;
    for (int i=3; i*i < 10000000; i+=2) {
        if (!oflag[i]) {
            for (int j=i*i; j<10000000; j+= (i<<1)) oflag[j] = true;
        }
    }
}
/*
void make_prime2() {
    int s, e;
    for (s = 0, e = s+100000; e<=10000000; s+=100000, e = s+100000) {
        //printf("%d %d\n", s, e);
        sieve(s,e);
    }
}
*/
void filter() {
    nums[2] = 1;
    nums[3] = 1;
    sys[3] = false;
    sys[2] = true;
    int r;
    for (int i=1; i*i < 10000000; i++) {
        for (int j=1; i*i + j*j*j*j < 10000000; j++) {
            r = i*i + j*j*j*j;
            if (r&1 && !oflag[r]) {
                sys[r] = true;
            }
        }
    }
    
    for (int i=5; i < 10000000; i+=2) {
        if (sys[i]) {
            nums[i] = nums[i-2] + 1;
        } else {
            nums[i] = nums[i-2];
        }
    }
}

int main() {
    make_prime();
    filter();
    int t, n;
    scanf("%d", &t);
    while (t--) {
        scanf("%d", &n);
        printf("%d\n", nums[(n&1 || n==2)?n:n-1]);
    }
}