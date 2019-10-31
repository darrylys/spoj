import java.math.BigInteger;
import java.io.*;

public class spojIGARB {
    public static int[] convertToBase7Reversed(BigInteger k, BigInteger base) {
        int[] seq = new int[250];
        int cntr = 1; //pos 0 for length
        
        while (!(k.equals(BigInteger.ZERO))) {
            seq[cntr++] = (k.mod(base)).intValue();
            k = k.divide(base);
        }
        seq[0] = cntr;
        return seq;
    }
    
    public static void main(String... args) throws Exception {
        BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(System.out));
        BigInteger k;
        BigInteger base = new BigInteger("7");
        
        int testcase;
        char[] map = {'0','1','2','5','9','8','6'};
        int[] seq;
        testcase = Integer.parseInt(sc.readLine());
        
        for (int xxx= 0; xxx<testcase; xxx++) {
            k = new BigInteger(sc.readLine());
            seq = convertToBase7Reversed(k, base);
            
            for (int i=1; i<seq[0]; i++) {
                out.write(map[seq[i]]);
            }
            
            out.write('\n');
            out.flush();
        }
    }
}