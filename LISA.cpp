//implementation: DP-MCM

#include<cstdio>
#include<cstring>
#define ll unsigned long long int

ll min[105][105];
ll max[105][105];
char exp[105];

void print(int n) {
    printf("MIN \n");
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            printf("%3llu", min[i][j]);
        }
        putchar('\n');
    }
    printf("MAX \n");
    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++) {
            printf("%3llu", max[i][j]);
        }
        putchar('\n');
    }
}

int main() {
    int t, len, num;
    ll mmin, mmax, temp1, temp2;
    char op;
    scanf("%d",&t);
    while(t--) {
        scanf("%s",exp);
        len = strlen(exp);
        num = (len+1)/2;

        for (int i=0; i<num;i++) {
            min[i][i] = max[i][i] = exp[i*2]-'0';
        }

        for (int lem = 1; lem < num; lem++) {
            int sep;
            for (int i=0; i<(num-lem);i++) {
                sep = i;
                op = exp[i*2+1];
                if (op == '+') {
                    mmin = min[i][sep] + min[sep+1][i+lem];
                    mmax = max[i][sep] + max[sep+1][i+lem];
                } else if (op == '*') {
                    mmin = min[i][sep] * min[sep+1][i+lem];
                    mmax = max[i][sep] * max[sep+1][i+lem];
                }

                for (sep = i+1; sep < i+lem; sep++) {
                    op = exp[2*sep+1];
                    if (op == '+') {
                        temp1 = min[i][sep] + min[sep+1][i+lem];
                        temp2 = max[i][sep] + max[sep+1][i+lem];
                    } else if (op == '*') {
                        temp1 = min[i][sep] * min[sep+1][i+lem];
                        temp2 = max[i][sep] * max[sep+1][i+lem];
                    }
                    if (temp1 < mmin) mmin = temp1;
                    if (temp2 > mmax) mmax = temp2;
                }
                min[i][i+lem] = mmin;
                max[i][i+lem] = mmax;
            }
        }
        //print(num);
        printf("%llu %llu\n", max[0][num-1],min[0][num-1]);
    }
    return 0;
}
