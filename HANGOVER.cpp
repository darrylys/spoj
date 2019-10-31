#include<cstdio>

int get_n(double c) {
    double result = 0.0;
    int i;
    for (i=2;result<c;i++) {
        result+=1/(double)i;
    }
    return i-2;
}

int main() {
    double value;
    while (true) {
        scanf("%lf", &value);
        if (value!=0.0)
            printf("%d card(s)\n", get_n(value));
        else break;
    }
    return 0;
}
