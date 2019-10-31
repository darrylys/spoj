/*
AC, SPOJ 0.00s
algorithm: inclusion-exclusion

first, we remove all minx requirements, thus changing N as follows:
N -= mina + minb + minc;

and transposing the range of A from [mina, maxa] to [0, maxa-mina]. Apply this to B and C also			(1)

now, the equation is A + B + C = N with all variables transposed
variable C will fill whatever gap A + B set so, it is excluded from analysis

list of possible values for A and B are ( C will make A+B+C = N. So, it is not a free variable )
A B C
0 0 N
0 1 N-1
0 2 N-2
...
0 N 0
1 0 N-1
1 1 N-2
...
1 N-1 0
... and so on ...
...
N 0 0

inclusion-exclusion
we can see that the total possible combination will be: (N+1)[when A=0] + (N)[when A=1] + (N-1)[when A=2] + ... + 1 [when A=N] = { (N+1)*(N+2)/2 }
This does not see the bad values where A/B/C is above their respective upper bound.

so, following inclusion-exclusion:
let f(X) = (X+1)*(X+2)/2 following the above analysis

result = f(All combination) - f(A error) - f(B error) - f(C error) + f(A&B error) + f(A&C err) + f(B&C err) - f(A&B&C err)
with X err means that the minimum value of X in equation A+B+C=N is above the upper bound. X > maxx-minx.

we can calculate these with exactly the same way we transposed earlier (1). Recall that we remove the minimum values...
In this case, we also want to find where X is above a certain minimum value (maxx-minx) which is exactly the same thing.

Final remark, take caution of MOD.

*/

#include <stdio.h>

#define ll long long
#define MOD 1000000007

ll f(ll N) {
	if (N < 0) return 0;
	return ((N+1) * (N+2) / 2)%MOD;
}

int main() {
	int T; ll N, maxa, maxb, maxc, mina, minb, minc, A, B, C, R;
    
    scanf("%d", &T);
    
    while (T--) {
        scanf("%lld %lld%lld %lld%lld %lld%lld", &N, &mina, &maxa, &minb, &maxb, &minc, &maxc);
		
		//printf("N=%lld [%lld, %lld] [%lld, %lld] [%lld, %lld]\n", N, mina, maxa, minb, maxb, minc, maxc);
		
		N -= mina + minb + minc;
		A = maxa - mina;
		B = maxb - minb;
		C = maxc - minc;
		
		//printf("N=%lld, f(N)=%lld\n", N, f(N));
		
		R = (f(N) - f(N-A-1) - f(N-B-1) - f(N-C-1) + f(N-A-B-2) + f(N-A-C-2) + f(N-B-C-2) - f(N-A-B-C-3) + 10LL * MOD)%MOD;
		printf("%lld\n", R);
	}
}
