#include<cstdio>
#define l long long
#define NO_OPE 0

int main() {
    char ope = NO_OPE;
    l garage;
    int t;
    scanf("%d",&t);
    l operand;
    while(t--){
        ope = NO_OPE;
        while (true) {
            scanf("%lld", &operand);
            if (ope == NO_OPE) {
                garage = operand;
            } else {
                switch (ope) {
                    case '-':
                        garage -= operand;
                    break;
                    
                    case '+':
                        garage += operand;
                    break;
                    
                    case '*':
                        garage *= operand;
                    break;
                    
                    case '/':
                        garage /= operand;
                    break;
                }
            }
            while ((ope=getchar())==' ');
            if (ope == '=') {
                printf("%lld\n", garage);
                break;
            }
        }
    }
}