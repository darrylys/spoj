import java.math.BigInteger;
import java.io.*;

public class BORING3 {
	
	static final int MAXN = 1000010;
	static final int MAXPRIMES = 80000;
	static final int BATCHSIZE = 300;
	
	static boolean[] flag = new boolean[MAXN];
	static int[] primes = new int[MAXPRIMES];
	static BigInteger[] primeMul = new BigInteger[MAXPRIMES+1];
	
	
	static int buildPrimes() {
		int pno = 0;
		primes[pno++] = 2;
		
		for (int i=3; i < MAXN; i+=2) {
			if (!flag[i]) {
				primes[pno++] = i;
				
				if (i <= 1000) {
					for (int j=i*i; j < MAXN; j+= 2*i) {
						flag[j] = true;
					}
				}
			}
		}
		
		return pno;
	}
	
	static void buildPrimeMul(int noOfPrimes, int batch) {
		//primeMul[0] = BigInteger.ONE;
		
		for (int i=0; i<noOfPrimes; ++i) {
			if (i % batch == 0) {
				primeMul[i] = new BigInteger("" + primes[i]);
			} else {
				primeMul[i] = primeMul[i-1].multiply(new BigInteger("" + primes[i]));
			}
		}
		
		//for (int i=0; i<130; ++i) {
		//	System.err.printf("%d\t%s\n", i, primeMul[i]);
		//}
	}
	
	static int binsearch(int x, int[] arr, int N) {
		int u=0, v=N, c;
		while(true) {
			if (u>=v) {
				return u-1;
			} else {
				c = (u+v)/2;
				if (x < arr[c]) {
					v = c;
				} else if (x > arr[c]) {
					u = c+1;
				} else {
					return c;
				}
			}
		}
	}
	
	public static void main(String[] args) throws Exception {
		
		//long begin = System.currentTimeMillis();
		
		int noOfPrimes = buildPrimes();
		buildPrimeMul(noOfPrimes, BATCHSIZE); // 300 ~ sqrt(80000)
		
		int T;
		BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
		
		//T = Integer.parseInt(sc.readLine());
		
		// Max performance in BORING3 is 2200 (1000 to pass BORING2) (56 s, max 60s). Plan to optimize??
		// This code can solve BORING2 in ~25ms
		T = 2200; // changeable
		for (int _pp = 0; _pp<T; ++_pp) {
			
			String[] inx = sc.readLine().split(" ");
			//BigInteger N = new BigInteger(inx[0]);
			int x = Integer.parseInt(inx[0]);
			
			if (x == 0) {
				System.out.println("0");
				continue;
			}
			
			BigInteger P = new BigInteger(inx[1]);
			
			//if (N.compareTo(P) >= 0) {
			//	System.out.println("0");
			//	continue;
			//}
			
			//int x = P.subtract(N).intValue();
			//int x = D;
			int pmn = x-1;
			
			//System.err.printf("x=%d, pmn=%d\n", x, pmn);
			//
			//System.err.printf("list of primes: \n");
			//for (int i=0; primes[i] <= pmn; ++i) {
			//	System.err.printf("%d\t", i);
			//}
			//System.err.printf("\n");
			//for (int i=0; primes[i] <= pmn; ++i) {
			//	System.err.printf("%d\t", primes[i]);
			//}
			//System.err.printf("\n");
			
			// (p-x)! mod P = (-1)^x ((x-1)!)^-1 mod P
			
			int lastPrime = 1;
			
			BigInteger fac = BigInteger.ONE;
			
			// [1-sqrtN]
			for (int i=0; primes[i] * primes[i] <= pmn; ++i) {
				
				int iN = pmn;
				int p = primes[i];
				int e = 0;
				while (p <= iN) {
					e += iN / p;
					p *= primes[i];
				}
				
				//System.err.printf("%d^%d\n", primes[i], e);
				fac = fac.multiply(new BigInteger("" + primes[i]).modPow(new BigInteger("" + e), P));
				if (fac.compareTo(P) >= 0) {
					fac = fac.mod(P);
				}
				
				lastPrime = primes[i];
				
			}
			
			//System.err.printf("lastPrime=%d, fac=%s\n", lastPrime, fac);
			
			int Nl = binsearch(pmn, primes, noOfPrimes)+1;
			int idx, lim;
			
			//System.err.printf("BEGIN: Nl=%d\n", Nl);
			
			//[N - SQRT(N)]
			for (int i=1; i*i < pmn; ++i) {
				lim = pmn / (i+1); // exp=i+1
				idx = binsearch(lim, primes, Nl);
				
				//System.err.printf("binsearch(%d): idx=%d\n", lim, idx);
				
				//int noz = Nl - idx - 1;
				// multiply all primes from [idx+1, (Nl-1)]
				BigInteger mulOfPrimes = BigInteger.ONE;
				
				int j;
				for (j=idx+1; j<=Nl-1 && j%BATCHSIZE != 0; ++j) {
					mulOfPrimes = mulOfPrimes.multiply(new BigInteger("" + primes[j]));
					if (mulOfPrimes.compareTo(P) >= 0) {
						mulOfPrimes = mulOfPrimes.mod(P);
					}
				}
				
				//System.err.printf("ITEER1: j=%d, mp=%s\n", j, mulOfPrimes);
				
				for ( ; j+BATCHSIZE-1<=Nl-1 ; j += BATCHSIZE) {
					mulOfPrimes = mulOfPrimes.multiply(primeMul[j+BATCHSIZE-1])/*.mod(P)*/;
					if (mulOfPrimes.compareTo(P) >= 0) {
						mulOfPrimes = mulOfPrimes.mod(P);
					}
				}
				
				//System.err.printf("ITEER2: j=%d, mp=%s\n", j, mulOfPrimes);
				
				//modify to
				if (j <= Nl-1) {
					mulOfPrimes = mulOfPrimes.multiply(primeMul[Nl-1]);
					if (mulOfPrimes.compareTo(P) >= 0) {
						mulOfPrimes = mulOfPrimes.mod(P);
					}
				}
				/*
				for ( ; j <= Nl-1; ++j) {
					mulOfPrimes = mulOfPrimes.multiply(new BigInteger("" + primes[j]));
					if (mulOfPrimes.compareTo(P) >= 0) {
						mulOfPrimes = mulOfPrimes.mod(P);
					}
				}
				*/
				//System.err.printf("ITEER3: j=%d, mp=%s\n", j, mulOfPrimes);
				
				mulOfPrimes = mulOfPrimes.modPow(new BigInteger("" + (i)), P);
				
				//System.err.printf("COMPLETE mp^%d mod P=%s\n", i, mulOfPrimes);
				
				fac = fac.multiply(mulOfPrimes);
				if (fac.compareTo(P) >= 0) {
					fac = fac.mod(P);
				}
				
				Nl = idx+1;
				if (Nl == 0 || primes[Nl-1] == lastPrime) break;
			}
			
			//System.err.printf("%d! mod %s = %s%n", pmn, P, fac);
			
			BigInteger mx;
			if (x%2 == 0) {
				mx = BigInteger.ONE;
			} else {
				mx = P.subtract(BigInteger.ONE);
			}
			
			System.out.println(mx.multiply(fac.modInverse(P)).mod(P));
		}
		
		//System.err.println(System.currentTimeMillis() - begin);
		
	}
}