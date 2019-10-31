import java.math.BigInteger;
import java.io.*;

public class spojBISHOPS {
    public static void main(String... args) throws Exception {
        BigInteger TWO = new BigInteger ("2");
        String in;
        BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(System.out));
        
        while ((in=sc.readLine())!=null) {
            if (in.equals("1")) out.write("1\n");
            else {
                out.write((((new BigInteger(in)).multiply(TWO)).subtract(TWO)).toString());
                out.write("\n");
            }
        }
        out.flush();
    }
}
