import java.math.BigInteger;
import java.io.*;
import java.util.*;

public class spojINCPOWK {
    public static void main(String[] args) throws Exception {
        BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(System.out));
        StringTokenizer st;
        
        int test = Integer.parseInt(sc.readLine()), k;
        int cntr;
        BigInteger n, result;
        
        for (int xx=0; xx<test; xx++) {
            st = new StringTokenizer(sc.readLine());
            
            k = Integer.parseInt(st.nextToken());
            n = new BigInteger(st.nextToken());
            
            result = new BigInteger(n.toString(2), k);
            out.write(result.toString());
            out.write('\n');
            out.flush();
        }
    }
}