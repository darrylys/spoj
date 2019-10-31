import java.math.BigInteger;
import java.io.*;

public class BORING {
	public static void main(String[] args) throws IOException {
		
		//long l = System.currentTimeMillis();
		
		BigInteger[] b = new BigInteger[10005];
		
		b[0] = BigInteger.ONE;
		
		for (int i=1; i<=10000; ++i) {
			b[i] = b[i-1].multiply(new BigInteger(""+i));
		}
		
		//System.out.println(System.currentTimeMillis() - l);
		
		//System.out.println(b[10000]);
		
		BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
		
		String in;
		String[] prm;
		
		int T = Integer.parseInt(sc.readLine());
		for (int xxx=0; xxx<T; ++xxx) {
			prm = sc.readLine().split(" ");
			long N = Long.parseLong(prm[0]);
			long P = Long.parseLong(prm[1]);
			
			BigInteger BP = new BigInteger(prm[1]);
			
			int np = (int)(P-N);
			if (np <= 0) {
				System.out.println("0");
				continue;
			}
			
			BigInteger lp = BigInteger.ONE;
			if ((np % 2) != 0) {
				lp = new BigInteger("" + (P-1));
			}
			BigInteger rp = b[np-1].mod(BP);
			System.out.println(lp.multiply(rp).modInverse(BP));
			
		}
		
		
	}
}
