import java.math.BigInteger;
import java.io.*;

public class spojJULKA {
	public static void main(String[] args) throws IOException {
		BigInteger t, d, two = new BigInteger("2");
		BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
		String in;
		while ((in=sc.readLine())!=null) {
			t = new BigInteger(in);
			d = new BigInteger(sc.readLine());
			System.out.println((t.add(d)).divide(two));
			System.out.println((t.subtract(d)).divide(two));
		}
	}
}