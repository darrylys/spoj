import java.io.*;
import java.math.*;
import java.util.*;
public class LASTDIG{
public static void main(String[] args)throws IOException{
BufferedReader sc=new BufferedReader(new InputStreamReader(System.in));
StringTokenizer x;
int in = Integer.parseInt(sc.readLine());
for (int i=0;i<in;i++){
x=new StringTokenizer(sc.readLine());
System.out.println((new BigInteger(x.nextToken())).modPow((new BigInteger(x.nextToken())),BigInteger.TEN));
}
}
}