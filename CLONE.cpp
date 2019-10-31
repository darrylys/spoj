//impl Map + Brute Force

#include<cstdio>
#include<map>
#include<utility>
#include<algorithm>
#include<string.h>

#define it map<ll, int>::iterator
#define ll unsigned long long int

using namespace std;

int getCode(char c) {
    switch(c) {
        case 'A': return 0;
        case 'C': return 1;
        case 'G': return 2;
        case 'T': return 3;
    }
}

ll tol(char* cod, int len) {
    ll mul = 1;
    ll total = 0;
    for (int i=len-1; i>=0; i--) {
        total = total + getCode(cod[i])*mul;
        mul *= 4;
    }
    return total;
}

int main() {
    int n, m;
    char code[25];
    map<ll, int> themap;
    int list[20010];

    while (scanf("%d %d", &n, &m) && n) {

        for (int i=0;i<n;i++) {
            scanf("%s",code);
            ll enc = tol(code, m);
            it iter = themap.find(enc);
            if (iter == themap.end()) {
                themap.insert(make_pair(enc, 0));
            } else {
                iter->second++;
            }
        }

        memset(list, 0, n*sizeof(int));
        for (it iter = themap.begin(); iter != themap.end(); ++iter) {
            list[iter->second]++;
        }

        for (int i=0;i<n;i++) {
            printf("%d\n", list[i]);
        }

        themap.clear();
    }
    return 0;
}
