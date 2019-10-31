#include<cstdio>
#include<cstring>

int num[10];
char str[1005];

void display_num(char last) {
    bool nostr;
    nostr = true;
    for (int i=9; i>0; i--) {
        while (num[i]--) {
            putchar(i+'0');
            nostr = false;
        }
    }
    if (nostr) putchar('0');
    else {
        while (num[0]--) {
            putchar('0');
        }
        putchar(last);
    }
    putchar('\n');
}

void run_f(int a, int b,  bool& found) {
    for (int i=a; i<9; i+=3) {
        if (num[i]) {
            num[i]--;
            found = true;
            break;
        }
    }
    if (!found) {
        for (int i=b; i<9 && !found; i+=3) {
            for (int j=i; j<9 && !found; j+=3) {
                if (i == j) {
                    if (num[i] >= 2) {
                        num[i] -= 2;
                        found = true;
                    }
                } else {
                    if (num[i] >= 1 && num[j] >= 1) {
                        num[i]--;
                        num[j]--;
                        found = true;
                    }
                }
            }
        }
    }
}

int main() {
    int testcase, sum;
    scanf("%d", &testcase);
    char last; bool found;
    while (testcase--) {
        scanf("%s", str);
        int len = strlen(str);
        memset(num, 0, 10*sizeof(int));
        
        for (int i=0; i<len; i++) {
            num[str[i]-'0']++;
        }
        sum = 0;
        for (int i=1; i<10; i++) {
            sum += i*num[i];
        }
        found = true;
        if (num[0] > 0) {
            num[0]--;
            last = '0';
        } else if (num[5] > 0) {
            num[5]--;
            last = '5';
        } else {
            found = false;
        } 
        if (found) {
            if (sum%3 == 0) {
                found = true;
            } else if (sum%3 == 1) {
                found = false;
                run_f(1,2,found);
            } else {
                found = false;
                run_f(2,1,found);
            }
        }
        if (found) display_num(last);
        else printf("impossible\n");
    }
}