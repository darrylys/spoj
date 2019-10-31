/*
AC 0.06s 6MB SPOJ

required concepts:
    Law of total expectation

Problem:
n = read_input();
ans = 0;
while(n > 0)
{
    ans = ans + 1;
    n = random() % n;
}
with random() is uniform random distribution
what is the expected value of "ans" variable above.

let E(N) is the expected "ans" 
E(N) = \sigma {i <- [0, (N-1)]} p(i) * ( 1 + E(i) )
p(i) is always 1/N due to uniformly distributed and anything % N will always result in 0 to N-1.

E(N) above can be simplified to:
E(N) = 1/N * \sigma {i <- [0, (N-1)]} ( 1 + E(i) )
     = 1/N * N + 1/N * \sigma {i <- [0, (N-1)]} ( E(i) )
     = 1 + 1/N * \sigma {i <- [0, (N-1)]} ( E(i) )

So, since N is 300000, just precompute everything from N = 0.
The sigma part can be cached along the way

Time: O(T + N)
Space: O(N)

I'm using "long double" instead of double to avoid precision issues.

*/

#include <stdio.h>

long double SE[300002];
long double E[300002];

int main() {
    E[0] = 0;
    SE[0] = 0;
    SE[1] = 0;
    for (int i=1; i<=300000; ++i) {
        E[i] = 1 + (long double)1 / i * SE[i];
        SE[i+1] = SE[i] + E[i];
    }
    int N, T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &N);
        printf("%.10Lf\n", E[N]);
    }
}
