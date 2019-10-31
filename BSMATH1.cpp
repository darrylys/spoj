#include<stdio.h>
#include<string.h>

#define DIG 82
#define NI 1002
#define FORU(i,a,b) for(int i=a; i<=b; i++)
#define FORD(i,a,b) for(int i=a; i>=b; i--)

typedef struct {
    int digit[DIG];
    int length;
} Number;

Number number[NI][3];
char tempstr[DIG];
char op[NI];

int max(int a, int b) { return (a>b)?a:b; }

char showInt(int a) {
    if (a <= 9) return (char)a + '0';
    else return (char)(a - 10 + 'A'); 
}

int getVal(char c) {
    if (c <= '9') return (int)(c - '0');
    else return (int)(c - 'A' + 10);
}

Number add(Number &a, Number &b, int base) {
    Number c;
    int carry = 0, sum, length = max(a.length, b.length);
    FORU(i,0,length-1) {
        sum = a.digit[i] + b.digit[i] + carry;
        if (sum >= base) {
            sum -= base;
            carry = 1;
        } else {
            carry = 0;
        }
        c.digit[i] = sum;
    }
    if (carry > 0) {
        c.digit[length] = carry;
        c.length = length+1;
    } else c.length = length;
    
    return c;
}

Number substract(Number &a, Number &b, int base) {
    Number c;
    int carry = 0, subs, length = max(a.length, b.length);
    FORU(i,0,length-1) {
        subs = a.digit[i] - b.digit[i] - carry;
        if (subs < 0) {
            subs += base;
            carry = 1;
        } else {
            carry = 0;
        }
        c.digit[i] = subs;
    }
    int len;
    for (len=length-1;len>=1;len--) {
        if (c.digit[len]) break;
    }
    c.length = len+1;
    return c;
}

bool isEq(Number &a, Number &b) {
    if (a.length != b.length) return false;
    for (int i=0; i<a.length; i++) if (a.digit[i] != b.digit[i]) return false;
    return true;
}

char inputReverse(int a, int k) {
    char c;
    
    while (c=getchar()) if ((c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')) break;
    int p = 0;
    tempstr[p++] = c;
    while (c=getchar()) {
        if (c == EOF || c == ' ' || c == '\n' || 
            c == '\r' || c == '+' || c == '-' || c == '=') {
            break;
        }
        tempstr[p++] = c;
    }
    
    tempstr[p] = '\0';
    
    memset(number[a][k].digit, 0, DIG*sizeof(int));
    for (int i=0; i<p; i++) {
        number[a][k].digit[p-i-1] = getVal(tempstr[i]);
    }
    number[a][k].length = p;
}

void inputQuestion(int ii) {
    char lastread = inputReverse(ii, 0);
    if (lastread == '+' || lastread == '-') {
        op[ii] = lastread;
    } else {
        char c;
        while (c = getchar()) {
            if (c == '+' || c == '-') {
                break;
            }
        }
        op[ii] = c;
    }
    inputReverse(ii , 1);
}

void inputSample(int ii) {
    inputQuestion(ii);
    inputReverse(ii, 2);
}

void printArray(Number &a) {
    for (int i=a.length-1; i>=0; i--) {
        putchar(showInt(a.digit[i]));
    }
}

int main() {
    int testcase, base, n, sect = 1;
    bool maxbase;
    Number t;
    scanf("%d", &testcase);
    while (testcase--) {
        //inputs
        inputSample(0);
        scanf("%d", &n);
        for (int i=1; i<=n; i++) {
            inputQuestion(i);
            number[i][2].length = 0;
        }
        
        //base calculation
        base = -1;
        maxbase = false;
        for (int i=0; !maxbase && i<=2 ; i++) {
            for (int j=0;!maxbase && j<number[0][i].length; j++) {
                if (base < number[0][i].digit[j]+1) base = number[0][i].digit[j]+1;
                if (base == 36) maxbase = true;
            }
        }
        for (int i=1; !maxbase && i<=n; i++) {
            for (int j=0; !maxbase && j<2; j++) {
                for (int k=0; !maxbase && k<number[i][j].length; k++) {
                    if (base < number[i][j].digit[k]+1) base = number[i][j].digit[k]+1;
                    if (base == 36) maxbase = true;
                }
            }
        }
        //minimal base obtained: base
        if (op[0] == '+') {
            for (; base<=36; base++) {
                t = add(number[0][0], number[0][1], base);
                if (isEq(number[0][2], t)) break;
            }
        } else {
            for (; base<=36; base++) {
                t = substract(number[0][0], number[0][1], base);
                if (isEq(number[0][2], t)) break;
            }
        }
        
        printf("SECTION %d (BASE %d)\n", sect++, base);
        FORU(i,1,n) {
            printf("  ");
            printArray(number[i][0]);
            printf(" %c ", op[i]);
            printArray(number[i][1]);
            printf(" = ");
            if (op[i] == '+') number[i][2] = add(number[i][0], number[i][1], base);
            else number[i][2] = substract(number[i][0], number[i][1], base);
            printArray(number[i][2]);
            putchar('\n');
        }
    }
    return 0;
}
