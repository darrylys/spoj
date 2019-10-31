#include<stdio.h>

#define ll long long

int main() {
    int t, z;
    ll N;
    
    scanf("%d", &t);
    while (t--) {
        scanf("%lld", &N);
        
        z = 0;
        N--;
        
        while (N) {
            if (N%4 == 2) {
                N-=2;
                continue;
            }
            
            if (N%4 == 0) {
                N/=4;
                continue;
            }
            
            z = 1;
            break;
        }
        printf("%s\n", !z ? "Ivica" : "Marica");
    }
}