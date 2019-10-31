import java.math.BigInteger;
import java.io.*;

public class spojFCTRL2 {
	public static void main(String[] args) throws IOException {
		BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
		BigInteger on = BigInteger.ONE;
		BigInteger mul = new BigInteger("2");
		String[] arr = new String[105];
		arr[0] = arr[1] = "1";
		for (int i=2; i<=100; i++) {
			on = on.multiply(mul);
			mul = mul.add(BigInteger.ONE);
			arr[i] = on.toString();
		}
		int tst = Integer.parseInt(sc.readLine());
		int in;
		for (int zz=0;zz<tst;zz++) {
			in = Integer.parseInt(sc.readLine());
			System.out.println(arr[in]);
		}
	}
}