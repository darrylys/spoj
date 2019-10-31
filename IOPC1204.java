import java.math.BigInteger;
import java.io.*;

public class Main {
    public static void main(String[] args) throws Exception {
        BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
        BufferedWriter out = new BufferedWriter(new OutputStreamWriter(System.out));
        int t = Integer.parseInt(sc.readLine());
        for (int _=0; _<t; ++_) {
            long n = Long.parseLong(sc.readLine());
            if (n == 0) out.write("1\n");
            else if (n == 1) out.write("3\n");
            else if (n == 2) out.write("5\n");
            else {
                n += 2;
                if (n > 2 && n % 2 == 0) n++;
                if (n > 3 && n % 3 == 0) n += 2;
                while (!(new BigInteger(""+n).isProbablePrime(3))) n += (n % 3 == 1) ? 4 : 2;
                //printf("%lld\n", x);
                out.write(""+n+"\n");
            
                /*for (long i = n+2+(n+3)%2 ; ; i+=2 ) {
                    String m = ""+i;
                    boolean z = new BigInteger(m).isProbablePrime(3);
                    if (z) {
                        out.write(m);
                        out.write("\n");
                        break;
                    }
                }*/
            }
        }
        out.flush();
    }
}