// AC in MOON1, 0.02 s
// AC in MOON2, 8.76 s, 8.05 s
// AC in MOON2, 4.93 s with opti in precomputing invmod just as needed (not computing all 1mill but just the maximum R in input)
// algo uses a lot of math.
// the old formula in MOON1 can be derived further.
// expand the sigma part in MOON1 algo and a pattern can be derived from there.

/*
final formula:

x = (a)/(a-1)
1. + (a^N (N+1)^R - 1^R) * (x + x^2 + x^3 + ... + x^R)								(F(1, x))
2. - (a^N (N+2)^R - 2^R) * (    x^2 + 2x^3 + 3x^4 + ... + (R-1)x^R)					(F(2, x))
3. + (a^N (N+3)^R - 3^R) * (          x^3 + 3x^4 + 6x^5 + 10x^6 + ... + (?)x^R)		(F(3, x))
....
R+1. 

a pattern emerges from the x part
the coefficients are basically binomial coefficients
1	1	1	1	1	1	1 ...
1	2	3	4	5	6	7 ...
1	3	6	10	15	21	28 ...
1	4	10	20	35	56	84 ...
1	5	15	35	70	126	210 ...
...
...

these polynomials can be quickly calculated by a simple observation
assuming the polynomial we want to solve is some other than F(1, x)

F(n, x) - x*F(n, x) is always F(n-1, x) - Le(n-1, x) - Le(n, x). | n>1
and F(1, x) --> base case is (x^(R+1)-1)/(x-1)
with Le is last element function. The coefficient of x^R.
Le is in fact binomial function multiplied by x (see the above table)

*/


#include <stdio.h>

#define MOD (1000000007)
#define ll long long
#define MAXR (1000005)

int CR[MAXR];
int Aexp[MAXR];
int arrInvMod[MAXR];

ll bigmod(int base, int exp, int mod) {
	if (exp == 0 || base == 1) return 1;
	if (exp == 1) return base;
	
	ll half = bigmod(base, exp>>1, mod);
	half = (half*half)%mod;
	if (exp&1) {
		half = (half*base)%mod;
	}
	return half;
}

//ll invmod(int x) {
//	return bigmod(x, MOD-2, MOD);
//}

// calc C(R, X+1) from C(R, X)
int nextC(int CRX, int R, int X) {
	return (int)( ( ( (ll)CRX * (R-X+MOD) )%MOD * 
		/*bigmod(X+1, MOD-2, MOD)*/ arrInvMod[X+1]  )%MOD );
}

int main() {
	//for (int i=1; i<MAXR; ++i) {
	//	arrInvMod[i] = (int)bigmod(i, MOD-2, MOD);
	//}
	
	// precalculate the factorials and inverted factorials.
	
	int T, N, a, R;
	ll A, invAm1, inv1mA, sum, Fs, Fsw, aeN;
	
	int bigR = 0;
	
	scanf("%d", &T);
	while (T--) {
		scanf("%d %d %d", &N, &a, &R);
		
		if (bigR < R) {
			for (int i=bigR+1; i<=R; ++i) {
				arrInvMod[i] = (int)bigmod(i, MOD-2, MOD);
			}
			bigR = R;
		}
		
		
		A = (((ll)a)*bigmod(a-1, MOD-2, MOD))%MOD;
		invAm1 = bigmod(A-1, MOD-2, MOD);
		inv1mA = MOD-invAm1;
		
		sum = 0;
		
		CR[0] = 1;
		Aexp[0] = 1;
		for (int i=1; i<=R; ++i) {
			//CR[i] = nextC(CR[i-1], R, i-1);
			// this step can be omitted if factorials are ready
			CR[i] = nextC(CR[i-1], R+1, i-1);
			Aexp[i] = (int)(((ll)Aexp[i-1] * A)%MOD);
		}
		Aexp[R+1] = (int)(((ll)Aexp[R]*A)%MOD);
		aeN = bigmod(a, N, MOD);
		
		// false at i=R+1, the fs = 0;
		for (int i=1; i<=R+1; ++i) {
			
			// how to omit the bigmod here??
			ll coef = (aeN * bigmod(N+i, R, MOD) - 
				bigmod(i, R, MOD) + MOD)%MOD;
			
			if (i == 1) {
				// initial condition (correct)
				Fs = (invAm1 * (Aexp[R+1] + MOD-1))%MOD;
				
			} else {
				//Fs = (inv1mA * ((Fs - (((ll)CR[i-2]*Aexp[R+2-i])%MOD) - 
				//	(((ll)CR[i-1]*Aexp[R+2-i])%MOD) + 2LL*MOD)%MOD) )%MOD;
				ll tempd = ((ll)Aexp[R+2-i] * (CR[i-1]/* + CR[i-2]*/))%MOD;
				Fs = (inv1mA * (Fs - tempd + MOD))%MOD;
				
			}
			
			Fsw = (Fs * Aexp[i])%MOD;
			
			//printf("Fs[%d]=%lld\n", i, Fsw);
			
			coef = (coef * Fsw)%MOD;
			
			if (i&1) {
				sum += coef;
			} else {
				sum += (MOD-coef);
			}
			
			sum %= MOD;
		}
		
		printf("%lld\n", sum%MOD);
	}
	
	return 0;
}
