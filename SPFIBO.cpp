#include<stdio.h>

#define ll long long

ll bitlen[100];
ll fibo[100];
ll fibo_one[100];

// not N but actual number
ll rec_calc(ll Exn, int pos) {
    ll onebits = 0;
    ll remN = Exn;
    ll n = 0;
    while (remN) {
        if (remN >= fibo[pos]) {
            remN -= fibo[pos];
            onebits += n + fibo_one[pos];
            n = remN;
        }
        --pos;
    }
    return onebits;
}

int rem_ones_calc(ll N, int pos, ll axn) {
    ll laN = N - bitlen[pos-1] - 1;
    int co_pos = pos - laN%pos;
    
    int sc = 0;
    for (int i=pos; i>=co_pos; --i) {
        if (axn >= fibo[i]) {
            axn -= fibo[i];
            sc++;
        }
    }
    return sc;
}

int main() {
    ll N;
    scanf("%lld", &N);
    
    fibo[0] = 1;
    fibo[1] = 1;
    
    bitlen[0] = 0;
    
    int pos = 1;
    for ( ; ; ++pos) {
        
        bitlen[pos] = bitlen[pos-1] + fibo[pos-1]*pos;
        if (pos > 1) fibo[pos] = fibo[pos-1] + fibo[pos-2];
        //printf("bitlen[%d]=%lld\n", pos, bitlen[pos]);
        if (bitlen[pos] > N) {
            break;
        }
    }
    
    fibo_one[1] = 0;
    fibo_one[2] = 1;
    for (int i=3; i<=pos; ++i) {
        fibo_one[i] = fibo_one[i-1] + fibo[i-2] + fibo_one[i-2];
    }
    
    ll acN = fibo[pos] + (N-bitlen[pos-1]-1)/pos;
    
    ll bef = rec_calc(acN, pos);
    int wth = rem_ones_calc(N, pos, acN);
    
    printf("%lld\n", bef+wth);
    
    return 0;
}
