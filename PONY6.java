/**
 * AC, 2.67s SPOJ
 * simple implementation:
 * algo:
 * G(k,r) = \sigma n^k / r^n
 * r*G(k,r) = \sigma n^k / r^(n-1)
 * from above equation, we can obtain G(k,r)*(r-1) as follows:
 * (r-1)*G(k,r) = 1 + (2^k - 1^k) / r + (3^k - 2^k) / r^2 + ...
 * expand the ((n+1)^k - n^k) using binomial expansion and regoup them gives the following equation:
 * G(k,r) = 1/(r-1) * (1 + \sigma i=1..k C(k,i) * G(k-i, r))					(1)
 * 
 * computing above directly will cost O(k^2) per test case which will timeout.
 * so, let x = 1/(r-1)															(2)
 * unroll the equations now (G(k) = G(k,r) below because r does not change and is just a constant in the equation)
 * G(0) = x
 * G(1) = x + x^2
 * G(2) = x + 3x^2 + 2x^3
 * ...
 * Precompute the coefficients of x first. after the coeff are computed, G(k) is computable in O(k) per test case.
 * coefficients are computed using equation 1 in O(k^3) which is computable within 10ms in my computer.
 */

import java.math.BigInteger;
import java.io.*;

public class PONY6 {
	static BigInteger[][] C = new BigInteger[55][55];
	static BigInteger[][] coef = new BigInteger[55][55];
	
	static void buildC() {
		
		for (int i=0; i<55; ++i) {
			C[i][i] = C[i][0] = BigInteger.ONE;
			for (int j=1; j<i; ++j) {
				C[i][j] = C[i-1][j].add(C[i-1][j-1]);
			}
		}
		
		for (int i=0; i<55; ++i) {
			for (int j=0; j<55; ++j) {
				coef[i][j] = BigInteger.ZERO;
			}
		}
		
	}
	
	static void build() {
		coef[0][1] = BigInteger.ONE;
		
		for (int K=1; K<=50; ++K) {
			
			// x = 1/(r-1)
			// G(K) = x ( 1 + \sigma i=1..K C(K, i) * G(K-i) )
			
			coef[K][1] = BigInteger.ONE;
			for (int i=1; i<=K; ++i) {
				
				for (int j=1; j<=K-i+1; ++j) {
					coef[K][j+1] = coef[K][j+1].add(C[K][i].multiply(coef[K-i][j])); 
				}
			}
		}
	}
	
	public static void main(String[] args) throws Exception {
		
		long start;
		
		//start = System.currentTimeMillis();
		buildC();
		//System.out.println("buildC time=" + (System.currentTimeMillis()-start));
		
		//start = System.currentTimeMillis();
		build();
		//System.out.println("build time=" + (System.currentTimeMillis()-start));
		
		// hmm, build function finishes in 9-12 ms. It should be fine
		
		//for (int i=0; i<=50; ++i) {
		//
		//	System.out.printf("%d", i);
		//	for (int j=1; j<=i+1; ++j) {
		//		System.out.printf("\t%s", coef[i][j]);
		//	}
		//	System.out.printf("\n");
		//}
		
		// formula
		// given: K, r
		// \sigma i=K+1; i>=1; --i; sum += coeff[K][i] * (r-1)^(i-K-1)
		// gcd = gcd(sum, (r-1)^(K+1))
		// print ("%d/%d\n", sum/gcd, (r-1)^(K+1)/gcd)
		
		//Buffered
		
		int T;
		BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
		T = Integer.parseInt(sc.readLine());
		for (int ppp=0; ppp<T; ++ppp) {
			String[] in = sc.readLine().split(" +");
			
			int K, R;
			K = Integer.parseInt(in[1]);
			R = Integer.parseInt(in[2]);
			
			BigInteger N = BigInteger.ZERO;
			BigInteger Rm1 = new BigInteger("" + (R-1));
			BigInteger rmul = BigInteger.ONE;
			
			for (int i=K+1; i>=1; --i) {
				N = N.add(coef[K][i].multiply(rmul));
				rmul = rmul.multiply(Rm1);
			}
			
			BigInteger D = rmul;
			
			BigInteger gcd = N.gcd(D);
			
			int nsgn = N.signum(), dsgn = D.signum(), sgn = 1;
			if (nsgn != dsgn) {
				sgn = -1;
			}
			
			System.out.printf("%s %s%s / %s%n", in[0], (sgn == -1) ? "-" : "", N.abs().divide(gcd), D.abs().divide(gcd));
			
		}
		
	}
}
