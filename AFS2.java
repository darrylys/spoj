import java.math.BigInteger;
import java.io.*;

public class spojAFS2 {
    public static void main(String[] args) throws Exception {
        BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
        
        String in;
        BigInteger sum;
        int tc = Integer.parseInt(sc.readLine());
        for (int xsx=0; xsx<tc; ++xsx) {
            long n = Long.parseLong(sc.readLine());
            
            if (n == 1) {
                System.out.println("0");
                continue;
            }
            
            sum = new BigInteger(""+(n-1));
            int lasti=0;
            
            for (long i=2; i*i<=n; ++i) {
                //sum += (n/i-1)*i;
                sum = sum.add(new BigInteger("" + ((n/i-1)*i)));
                lasti = (int)i;
            }
        
            for (long i=2; i*i<n; ++i) {
                sum = sum.add((new BigInteger(""+(n/i-lasti))).multiply(new BigInteger(""+(n/i+lasti+1))).shiftRight(1));
                
                //sum += (ll)(n/i-lasti)*(n/i+lasti+1)/2;
            }
            System.out.println(sum);
        }
    }
}