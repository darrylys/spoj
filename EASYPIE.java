import java.util.*;
import java.io.*;

class Problem {
    int teamsolved;
    int numsubmit;
    int wrongsubs;
    int totaltime;
    Problem() {
        resetVars();
    }
    void resetVars() {
        teamsolved = numsubmit = totaltime = 0;
        wrongsubs = 0;
    }
}

class Player {
    boolean stat;
    boolean[] prob;
    int time;
    Problem[] problem;
    Player() {
        stat = false;
        time = 0;
        prob = new boolean[9];
        problem = new Problem[9];
        for (int i=0; i<9; i++) {
            prob[i] = false;
            problem[i] = new Problem();
        }
    }
}

public class spojEASYPIE {
    public static void main(String[] args) throws IOException {
        BufferedReader sc = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        HashMap<String, Player> table = new HashMap<String, Player>();
        Problem[] problem = new Problem[9];
        for (int i=0; i<9; i++) problem[i] = new Problem();
        int t, n, time; char pc, pst;
        String name;
        Player te;
        n = Integer.parseInt(sc.readLine());
        for (int kk=0; kk<n; kk++) {
            t = Integer.parseInt(sc.readLine());
            for (int bb=0; bb<t; bb++) {
                st = new StringTokenizer(sc.readLine());
                time = Integer.parseInt(st.nextToken());
                name = st.nextToken();
                if (!table.containsKey(name)) {
                    te = new Player();
                    table.put(name, te);
                }
                te = table.get(name);
                te.time = time;
                pc = st.nextToken().charAt(0);
                pst = st.nextToken().charAt(0);
                if (pst == 'A') {
                    if (!te.prob[pc-'A']) {
                        te.prob[pc-'A'] = true;
                        problem[pc-'A'].teamsolved++;
                        te.problem[pc-'A'].totaltime += te.time;
                        te.problem[pc-'A'].numsubmit += te.problem[pc-'A'].wrongsubs+1;
                    }
                } else {
                    if (!te.prob[pc-'A']) {
                        te.problem[pc-'A'].wrongsubs++;
                    }
                }
            }
            
            int[] avesum = new int[9];
            int[] avetime = new int[9];
            String tem;
            for (Iterator it = table.keySet().iterator(); it.hasNext(); ) {
                tem = (String)it.next();
                te = table.get(tem);
                for (int i=0 ; i<9; i++) {
                    if (te.prob[i]) {
                        avesum[i] += te.problem[i].numsubmit;
                        avetime[i] += te.problem[i].totaltime;
                    }
                }
            }
            
            for (int i='A'; i<='I'; i++) {
                if (problem[i-'A'].teamsolved > 0) {
                    System.out.printf("%c %d %.2f %.2f\n", (char)i, problem[i-'A'].teamsolved, 
                        avesum[i-'A']/(double)problem[i-'A'].teamsolved,
                        avetime[i-'A']/(double)problem[i-'A'].teamsolved);
                } else {
                    System.out.printf("%c 0\n", (char)i);
                }
            }
            table.clear();
            for (int i=0; i<9; i++) problem[i].resetVars();
        }
    }
}