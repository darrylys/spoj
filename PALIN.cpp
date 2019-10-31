#include<cstdio>

char num[1000005];

void halfinc_cpy(int *len) {
    int carry = 1;
    for (int i=(*len-1)/2; i>=0; i--) {
        num[i] += carry;
        if (num[i] >= '9'+1) {
            num[i] -= 10;
            carry = 1;
        } else {
            carry = 0;
        }
    }
    //printf("insidehalf_cpy()\n");
    if (carry) {
        (*len)++;
        for (int i=1; i<*len; i++) {
            num[i] = num[i-1];
        }
        num[0] = '1';
    }
    //printf("insidehalf_cpy()\n");
    int sl, sr;
    if ((*len)%2) {
        sr = *len/2+1;
        sl = sr-2;
    } else {
        sr = *len/2;
        sl = sr-1;
    }
    //printf("insidehalf_cpy()\n");
    for (;sl>=0;sl--,sr++) {
        num[sr] = num[sl];
    }
    //printf("insidehalf_cpy()\n");
}

bool isbigger(int *len) {
    int sr, sl;
    if ((*len)%2) {
        sr = *len/2+1;
        sl = sr-2;
    } else {
        sr = *len/2;
        sl = sr-1;
    }
    //printf("insideis_bigger()\n");
    while (sl>=0) {
        if (num[sl] > num[sr]) {
            for (;sl>=0;sl--,sr++) {
                num[sr] = num[sl];
            }
            return true;
        } else if (num[sl] < num[sr]) {
            halfinc_cpy(len);
            return false;
        }
        sl--; sr++;
    }
    //printf("insideis_bigger()\n");
    halfinc_cpy(len);
    //printf("insideis_bigger()\n");
    return false;
}

int main() {
    int t,cntr;
    char c;
    scanf("%d",&t);
    getchar();
    while(t--){
        //printf("\t1\n");
        while ((c=getchar())=='0');
        if (c == '\n') {
            printf("1\n");
            continue;
        }
        num[0] = c;
        cntr = 1;
        //printf("\t2\n");
        while ((c=getchar())!='\n' && c != EOF){
            num[cntr++] = c;
        }
        isbigger(&cntr);
        for (int i=0; i<cntr; i++) putchar(num[i]);
        putchar('\n');
        //printf("\t3\n");
    }
}
