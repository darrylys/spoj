import java.math.BigInteger;
import java.io.*;

public class HARDP {
	
	private static BigInteger[][] C = new BigInteger[55][55];
	
	private static class Frac {
		BigInteger numer;
		BigInteger denom;
		
		Frac(BigInteger a, BigInteger b) {
			numer = a;
			denom = b;
		}
		
		// simplifies this. does not create new object
		Frac simplify() {
			BigInteger gcd = numer.gcd(denom);
			numer = numer.divide(gcd);
			denom = denom.divide(gcd);
			
			return this;
		}
		
		// this + B
		Frac add(Frac B) {
			BigInteger ad = this.denom.multiply(B.denom);
			BigInteger aa = this.numer.multiply(B.denom).add(this.denom.multiply(B.numer));
			return new Frac(aa, ad).simplify();
		}
		
		// 1/this
		Frac inv() {
			return new Frac(denom, numer);
		}
		
		Frac multiply(Frac B) {
			return new Frac(
				this.numer
				.multiply(B.numer), 
				
				this.denom
				.multiply(B.denom)
			).simplify();
		}
		
		public String toString() {
			//simplify();
			return "(" + numer + "/" + denom + ")";
		}
		
	}
	
	static void buildC() {
		for (int i=0; i<55; ++i) {
			C[i][0] = C[i][i] = BigInteger.ONE;
			for (int j=1; j<i; ++j) {
				C[i][j] = C[i-1][j].add(C[i-1][j-1]);
			}
		}
	}
	
	static long gcd(long a, long b) {
		if (b == 0) return a;
		else return gcd(b, a%b);
	}
	
	public static void main(String[] args) throws Exception {
		long begin = System.currentTimeMillis();
		
		buildC();
		
		BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
		String in;
		Frac[] coef = new Frac[55];
		BigInteger[] bCoef = new BigInteger[55];
		int sgnrow;
		BigInteger[] bsgn = new BigInteger[] {BigInteger.ONE, new BigInteger("-1")};
		
		while((in=sc.readLine())!=null){
			int N = Integer.parseInt(in);
			
			coef[0] = new Frac(BigInteger.ONE, new BigInteger("" + (N+1)));
			// coefs are from C[N][1-N]
			
			sgnrow = 0;
			for (int i=1; i<=N; ++i) {
				
				// combin column, vertical way
				// col = (N-i), row = [N+1 <col+1]
				int col = N-i;
				int sgn = sgnrow;
				
				coef[i] = new Frac(BigInteger.ZERO, BigInteger.ONE);
				BigInteger dv = C[col+1][col]; // null here!
				
				for (int j=0; j<i; ++j) {
					int row = N+1-j;
					
					// A * X + Y
					// A*X
					Frac A = new Frac(C[row][col].multiply(bsgn[sgn]), dv);
					coef[i] = coef[i].add(A.multiply(coef[j]));
					sgn ^= 1;
				}
				
				sgnrow ^= 1;
			}
			
			//for (int i=0; i<=N; ++i) {
			//	System.out.printf("%d. %s%n", i, coef[i]);
			//}
			//System.out.println();
			
			// wow!
			BigInteger lcm = BigInteger.ONE;
			//long llcm = 1;
			for (int i=0; i<=N; ++i) {
				BigInteger gcd = lcm.gcd(coef[i].denom);
				lcm = lcm.divide(gcd).multiply(coef[i].denom);
				
				//long igcd = gcd(llcm, coef[i].denom.intValue());
				//llcm = llcm / igcd * coef[i].denom.intValue();
				
			}
			
			//BigInteger lcm = new BigInteger("" + llcm);
			
			for (int i=0; i<=N; ++i) {
				bCoef[i] = coef[i].numer.multiply(lcm).divide(coef[i].denom);
			}
			
			bCoef[N+1] = BigInteger.ZERO;
			
			System.out.printf("%d=%s*(", N, lcm);
			for (int i=N+1; i>=0; i-=2) {
				if (bCoef[i].signum() > -1 && i != N+1) {
					System.out.printf("+%s", bCoef[i]);
				} else {
					System.out.printf("%s", bCoef[i]);
				}
			}
			for (int i=N; i>=0; i-=2) {
				if (bCoef[i].signum() > -1) {
					System.out.printf("+%s", bCoef[i]);
				} else {
					System.out.printf("%s", bCoef[i]);
				}
				
			}
			System.out.printf(")%n");
		}
		
		System.err.printf("%d%n", System.currentTimeMillis()-begin);
		
	}
}
