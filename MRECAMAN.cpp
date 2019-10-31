#include<cstdio>

int Recaman[500001];
bool flag[3020000];

void generate_sequence() {
    Recaman[0] = 0;
    for (int i=1;i<=500000;i++) {
        if (Recaman[i-1]-i > 0 && !flag[Recaman[i-1]-i]) {
            Recaman[i] = Recaman[i-1] - i;
        } else {
            Recaman[i] = Recaman[i-1] + i;
        }
        flag[Recaman[i]] = true;
    }
}

int main() {
    generate_sequence();
    int k;
    while (scanf("%d", &k)) {
        if (k!=-1) {
            printf("%d\n", Recaman[k]);
        } else return 0;
    }
}
