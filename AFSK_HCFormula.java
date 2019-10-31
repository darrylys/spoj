import java.math.BigInteger;
import java.io.*;

public class AFSK_HCFormula {
	
	private static int[][] A = new int[20][20];
	private static BigInteger[][] B_A = new BigInteger[20][20];
	
	private static int[][] C = new int[20][20];
	
	private static void buildC() {
		for (int i=0; i<20; ++i) {
			C[i][0] = C[i][i] = 1;
			for (int j=1; j<i; ++j) {
				C[i][j] = C[i-1][j] + C[i-1][j-1];
			}
		}
	}
	
	private static int[] derive(int[] p) {
		
		int[] d = new int[p.length-1];
		for (int i=0; i<d.length; ++i) {
			d[i] = p[i+1]*(i+1);
		}
		
		return d;
	}
	
	private static int[] mulby(int p, int[] a) {
		int[] pa = new int[a.length];
		for (int i=0; i<a.length; ++i) {
			pa[i] = p * a[i];
		}
		return pa;
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
		
	}
	
	private static BigInteger calc(int[] ai, int d, int n, BigInteger mod) {
		
		BigInteger N = new BigInteger("" + n);
		BigInteger Ne = BigInteger.ONE;
		BigInteger sum = BigInteger.ZERO;
		
		for (int e=ai.length-1; e>=0; --e) {
			sum = sum.add(new BigInteger("" + ai[e]).multiply(Ne));
			Ne = Ne.multiply(N);
		}
		
		return sum.divide(new BigInteger("" + d));
	}
	
	private static BigInteger getSum2(int N, int K, BigInteger M) {
		BigInteger sum;
		
		switch (K) {
			case 1:
				sum = calc(new int[]{1, 1, 0}, 2, N, M);
			break;
			
			case 2:
				sum = calc(new int[]{2, 3, 1, 0}, 6, N, M);
			break;
			
			case 3:
				sum = calc(new int[]{1, 2, 1, 0, 0}, 4, N, M);
			break;
			
			case 4:
				sum = calc(new int[]{6, 15, 10, 0, -1, 0}, 30, N, M);
			break;
			
			case 5:
				//(2n6 + 6n5 + 5n4 - n2) / 12
				sum = calc(new int[]{2, 6, 5, 0, -1, 0, 0}, 12, N, M);
			break;
			
			case 6:
				//(6n7 + 21n6 + 21n5 - 7n3 + n)/42
				sum = calc(new int[]{6, 21, 21, 0, -7, 0, 1, 0}, 42, N, M);
			break;
			
			case 7://(3n8 + 12n7 + 14n6 - 7n4 + 2n2)/24
				sum = calc(new int[]{3, 12, 14, 0, -7, 0, 2, 0, 0}, 24, N, M);
			break;
			
			case 8://(10n9 + 45n8 + 60n7 - 42n5 + 20n3 - 3n)/90
				sum = calc(new int[]{10, 45, 60, 0, -42, 0, 20, 0, -3, 0}, 90, N, M);
			break;
			
			case 9: //(2n10 + 10n9 + 15n8 - 14n6 + 10n4 - 3n2)/20
				sum = calc(new int[]{2, 10, 15, 0, -14, 0, 10, 0, -3, 0, 0}, 20, N, M);
			break;
			
			case 10: //6 33 55 0 -66 0  +66 0  -33  0  5    0
				sum = calc(new int[]{6, 33, 55, 0, -66, 0, 66, 0, -33, 0, 5, 0}, 66, N, M);
			break;
			
			default:
				sum = new BigInteger("-1");
			break;
		}
		
		return sum;
	}
	
	private static BigInteger getSum(int N, BigInteger K, BigInteger mod) {
		
		BigInteger sum = BigInteger.ZERO;
		BigInteger comb = BigInteger.ONE;
		int k = K.intValue();
		
		/*for (int i=0; i<=N; ++i) {
				sum += C[N-i+K+1][K+1] * A[K][i];
			}*/
		
		// compute combination
		int zn = N+k+1;
		for (int tk=1; tk<=k+1; ++tk) {
			comb = comb.multiply(new BigInteger(""+zn)).divide(new BigInteger("" + tk));
			zn--;
		}
		
		for (int i=0; i<=Math.min(N,k); ++i) {
			if (B_A[k][i] == null) {
				B_A[k][i] = new BigInteger("" + A[k][i]);
			}
			
			BigInteger mid = comb.multiply(B_A[k][i]);
			sum = sum.add(mid);
			comb = comb.multiply(new BigInteger(""+(N-i))).divide(new BigInteger(""+(N+k+1-i)));
			
		}
		
		return sum;
	}
	
	public static void main(String[] args) throws Exception {
		build();
		
		BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
		String in;
		
		int T = Integer.parseInt(sc.readLine()), N, K;
		BigInteger M;
		
		for (int xx_ = 0; xx_ < T; ++xx_) {
			
			in=sc.readLine();
			String[] ai = in.split(" ");
			N = Integer.parseInt(ai[0]);
			K = Integer.parseInt(ai[1]);
			M = new BigInteger(ai[2]);
			
			BigInteger B_K = new BigInteger("" + K);
			
			BigInteger sum = BigInteger.ZERO;
			for (int i=1; i*i <= N; ++i) {
				//sum = sum.add(getSum(N/i, B_K, M));
				sum = sum.add(getSum2(N/i, K, M));
			}
			
			int ns = 1, tn;
			long chkp = N;
			for (int i=1; i*i < N; ++i) {
				tn = N/i - N/(i+1);
				//sum = sum.add(getSum(ns, B_K, M).multiply(new BigInteger("" + tn)));
				sum = sum.add(getSum2(ns, K, M).multiply(new BigInteger("" + tn)));
				ns++;
				
				chkp = N/(i+1);
				
				if (chkp * chkp <= (long)N) break;
				
			}
			
			System.out.println(sum.mod(M));
			
		}
		
	}
	
	/*
	public static void main_r(String[] args) throws Exception {
		build();
		buildC();
		
		for (int i=0; i<12; ++i) {
			for (int j=0; j<12; ++j) {
				System.out.printf("%d\t", A[i][j]);
			}
			System.out.println();
		}
		
		// planned complexity: O(sqrt(N) * c * K)
		
		BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
		String in;
		while((in=sc.readLine())!=null) {
			
			String[] ai = in.split(" ");
			int N = Integer.parseInt(ai[0]);
			int K = Integer.parseInt(ai[1]);
			
			long sum = 0;
			int I = N;
			
			// breaks when i > min(K,N);
			// change the combinatorics formula.
			// computing the sum can be in O(c * K) where c = bigInteger operation.
			for (int i=0; i<=N; ++i) {
				sum += C[N-i+K+1][K+1] * A[K][i];
			}
			
			System.out.printf("\\sigma x=[1..%d] x^%d = %d%n", N, K, sum);
		}
		
	}
	*/
}
