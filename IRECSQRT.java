import java.math.BigInteger;
import java.io.*;

public class spojIRECSQRT {
    
    public static BigInteger getsum42(BigInteger[] _4, BigInteger exp, BigInteger mod, int counter) {
        if (exp.equals(BigInteger.ZERO)) {
            _4[counter] = new BigInteger("4");
            return BigInteger.ONE;
        }
        
        if (exp.equals(BigInteger.ONE)) {
            _4[counter] = new BigInteger("16");
            return new BigInteger("5");
        }
        
        if (exp.testBit(0)) {
            BigInteger exp2 = exp.shiftRight(1);
            BigInteger half = getsum42(_4, exp2, mod, counter+1);
            _4[counter] = _4[counter+1].multiply(_4[counter+1]).remainder(mod);
            return half.multiply(_4[counter+1].add(BigInteger.ONE)).remainder(mod);
        } else {
            BigInteger exp2 = exp.shiftRight(1).subtract(BigInteger.ONE);
            BigInteger half = getsum42(_4, exp2, mod, counter+1);
            _4[counter] = _4[counter+1].shiftLeft(2).multiply(_4[counter+1]).remainder(mod);
            return half.add(_4[counter+1].multiply(half.add(_4[counter+1]))).remainder(mod);
        }
    }
    
    public static void main(String[] args) throws Exception {
        BigInteger[] _4 = new BigInteger[70];
        BigInteger _2 = new BigInteger("2");
        
        BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
        
        int T = Integer.parseInt(sc.readLine());
        for (int pp=0; pp<T; ++pp) {
            String[] d = sc.readLine().split(" ");
            if (d[0].equals("0")) {
                System.out.println("1");
            } else if (d[0].equals("1")) {
                System.out.println("2");
            } else {
                BigInteger N = new BigInteger(d[0]);
                BigInteger M = new BigInteger(d[1]);
                
                //keep4(_4, N.subtract(_2), M, 0);
                /*for (int i=0; _4[i]!=null; ++i) {
                    System.out.println("\t >> " + _4[i]);
                }*/
                
                
                BigInteger sum4 = getsum42(_4, N.subtract(_2), M, 0);
                
                System.out.println(BigInteger.ONE.add(_2.modPow(N.subtract(BigInteger.ONE), M)).add(sum4.shiftLeft(1)).remainder(M));
                
                for (int i=0; _4[i]!=null; ++i) {
                    _4[i] = null;
                }
            }
        }
        
    }
}