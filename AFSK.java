import java.math.BigInteger;
import java.io.*;

public class AFSK {
	
	private static int[][] A = new int[20][20];
	private static BigInteger[][] B_A = new BigInteger[20][20];
	private static BigInteger[] fac = new BigInteger[15];
	
	private static int[] derive(int[] p) {
		
		int[] d = new int[p.length-1];
		for (int i=0; i<d.length; ++i) {
			d[i] = p[i+1]*(i+1);
		}
		
		return d;
	}
	
	private static void build() {
		
		// initial
		A[0][0] = 1;
		
		for (int i=1; i<12; ++i) {
			
			// derive
			// A'(x)(1-x)/(1-x)^(i+2) + A(x)*(i+1)/(1-x)^(i+2) = [A'(x) - xA'(x) + (i+1)*A(x)] / (1-x)^(i+2)
			int[] dA = derive(A[i-1]);
			int p = i;
			for (int j=0; j<12; ++j) {
				
				int xda = 0;
				if (j > 0) xda = dA[j-1];
				
				// multiply by x
				A[i][j+1] = dA[j] - xda + p * A[i-1][j];
			}
		}
		
		fac[0] = BigInteger.ONE;
		for (int i=1; i<fac.length; ++i) {
			fac[i] = fac[i-1].multiply(new BigInteger(""+i));
		}
		
	}
	
	// reduces divison
	private static BigInteger getSum3(int N, int K, BigInteger mod) {
		
		// [N+K+1] to [N+1]
		BigInteger[] lf = new BigInteger[K+1];
		lf[lf.length-1] = new BigInteger("" + (N+1));
		for (int i=lf.length-2, x=2; i>=0; --i, ++x) {
			lf[i] = lf[i+1].multiply(new BigInteger(""+(N+x)));
		}
		
		// [N] to [N-K]
		BigInteger[] rf = new BigInteger[K+1];
		rf[0] = BigInteger.ONE;
		for (int i=1, x=0; i<rf.length; ++i, --x) {
			rf[i] = rf[i-1].multiply(new BigInteger(""+(N+x)));
		}
		
		BigInteger sum = BigInteger.ZERO;
		for (int i=0; i<=N && i<=K; ++i) {
			if (B_A[K][i] == null) {
				B_A[K][i] = new BigInteger("" + A[K][i]);
			}
			
			sum = sum.add(B_A[K][i].multiply(lf[i]).multiply(rf[i]));
		}
		
		//return sum.divide(fac[K+1]);
		return sum;
	}
	
	public static void main(String[] args) throws Exception {
		build();
		
		BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
		String in;
		
		int T = Integer.parseInt(sc.readLine()), N, K;
		BigInteger M;
		
		for (int xx_ = 0; xx_ < T; ++xx_) {
			
			//long begin = System.currentTimeMillis();
			
			in=sc.readLine();
			String[] ai = in.split(" ");
			N = Integer.parseInt(ai[0]);
			K = Integer.parseInt(ai[1]);
			M = new BigInteger(ai[2]);
			
			BigInteger B_K = new BigInteger("" + K);
			
			BigInteger sum = BigInteger.ZERO;
			for (int i=1; i*i <= N; ++i) {
				//sum = sum.add(getSum(N/i, B_K, M));
				//sum = sum.add(getSum2(N/i, K, M));
				sum = sum.add(getSum3(N/i, K, M));
			}
			
			int ns = 1, tn;
			long chkp = N;
			for (int i=1; i*i < N; ++i) {
				tn = N/i - N/(i+1);
				//sum = sum.add(getSum(ns, B_K, M).multiply(new BigInteger("" + tn)));
				//sum = sum.add(getSum2(ns, K, M).multiply(new BigInteger("" + tn)));
				sum = sum.add(getSum3(ns, K, M).multiply(new BigInteger("" + tn)));
				ns++;
				
				chkp = N/(i+1);
				
				if (chkp * chkp <= (long)N) break;
				
			}
			
			// changing the formula a bit allows for division and mod only performed once per test case, just in the last
			// because they're heavy as hell
			System.out.println(sum.divide(fac[K+1]).mod(M));
			//System.err.println("elapsed: " + (System.currentTimeMillis()-begin));
			
		}
		
	}
}
