import java.math.BigInteger;
import java.io.*;

public class spojFCTRL4 {
	public static final BigInteger FIVE = new BigInteger("5");
	public static void main(String... args) throws Exception {
		BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
		String in;
		int[] num;
		while ((in = sc.readLine())!=null) {
			if (in.equals("0") || in.equals("1")) {
				System.out.println("1");
				continue;
			}
			num = convertToBase5(in);
			int q = 0, x = 0 , t = 0;
			for (int i=num[0]; i>=2; i--) {
				q = q + num[i];
				x = x + q;
				if (num[i]%2 == 0) t = t+num[i];
			}
			if (num[1]%2 == 0) t+=num[1];
			int z = (x+t/2)%4;
			switch (z) {
				case 0: System.out.println("6"); break;
				case 1: System.out.println("2"); break;
				case 2: System.out.println("4"); break;
				case 3: System.out.println("8"); break;
			}
		}
	}
	
	public static int[] convertToBase5(String num) {
		BigInteger n = new BigInteger(num);
		int[] stack = new int[200];
		int top = 1;
		
		while (!n.equals(BigInteger.ZERO)) {
			stack[top++] = n.mod(FIVE).intValue();
			n = n.divide(FIVE);
		}
		
		stack[0] = top-1;
		return stack;
	}
}