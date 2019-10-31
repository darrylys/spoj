#include<stdio.h>
#include<string.h>

#define MOD 1000000007
#define ull unsigned long long

int vd[105];
int fac[10005];
int ifac[10005];

char vis[100005][105];
int dp[100005][105];

int stack1[1000005];
int stack2[1000005];
int stack3[1000005];

int expmod(int base, int exp, int mod) {
    if (exp==0) return 1;
    if (exp==1) return base;
    int half = expmod(base, exp>>1, mod);
    ull h2 = ((ull)half*half)%mod;
    if (exp&1) {
        h2 = (h2*base)%mod;
    }
    return (int)h2;
}

int fillfac() {
    fac[0] = fac[1] = ifac[0] = ifac[1] = 1;
    for (int i=2; i<=10000; ++i) {
        fac[i] = (int)(((ull)i*fac[i-1])%MOD);
        ifac[i] = expmod(fac[i], MOD-2, MOD);
    }
}

int RECURSIVErf(int n, int u, int sd, int udn) {
    /*int top = 1;
    stack1[0] = n;
    stack2[0] = u;
    stack3[0] = sd;
    */
    if (vis[n][u]) return dp[n][u];
    vis[n][u] = 1;
    //printf("n=%d, u=%d, sd=%d, udn=%d\n", n, u, sd, udn);
    if (n == sd) {
        ull ulmp = fac[n];
        
        for (int i=u; i<udn; ++i) {
            ulmp *= ifac[vd[i]];
            ulmp %= MOD;
        }
        
        return dp[n][u] = (int)ulmp;
    } else if (sd < n) {
        return dp[n][u] = 0;
    } else {
        
        dp[n][u] = 0;
        ull q=0;
        for (int i=0; n>=i && u<udn && i<=vd[u]; ++i) {
            q = (((ull)fac[n] * ifac[n-i])%MOD * (ull)ifac[i])%MOD;
            dp[n][u] = (dp[n][u] + (q * RECURSIVErf(n-i, u+1, sd-vd[u], udn))%MOD)%MOD;
        }
        return dp[n][u];
    }
}

int rf(int n, int u, int sd, int udn) {
    int top = 1;
    stack1[0] = n;
    stack2[0] = u;
    stack3[0] = sd;
    
    int tn, tu, tsd;
    
    while (top) {
        tn = stack1[top-1];
        tu = stack2[top-1];
        tsd = stack3[top-1];
        
        if (vis[tn][tu]) {
            top--;
            continue;
        }
        
        if (tn == tsd) {
            ull ulmp = fac[tn];
            
            for (int i=tu; i<udn; ++i) {
                ulmp *= ifac[vd[i]];
                ulmp %= MOD;
            }
            
            dp[tn][tu] = (int)ulmp;
            vis[tn][tu] = 1;
            top--;
            
        } else if (tsd < tn) {
            vis[tn][tu] = 1;
            dp[tn][tu] = 0;
            top--;
            
        } else {
            
            bool pass = true;
            for (int i=0; tn>=i && tu<udn && i<=vd[tu]; ++i) {
                //q = (((ull)fac[n] * ifac[n-i])%MOD * (ull)ifac[i])%MOD;
                
                if (!vis[tn-i][tu+1]) {
                    pass = false;
                    stack1[top] = tn-i;
                    stack2[top] = tu+1;
                    stack3[top] = tsd-vd[tu];
                    top++;
                }
                
                //tsum = (tsum + (q * rf(n-i, u+1, sd-vd[u], udn))%MOD)%MOD;
            }
            
            if (pass) {
                dp[tn][tu] = 0;
                ull q=0;
                vis[tn][tu] = 1;
                for (int i=0; tn>=i && tu<udn && i<=vd[tu]; ++i) {
                    q = (((ull)fac[tn] * ifac[tn-i])%MOD * (ull)ifac[i])%MOD;
                    dp[tn][tu] = (dp[tn][tu] + (q * dp[tn-i][tu+1])%MOD)%MOD;
                }
                top--;
            }
            
        }
    }
    return dp[n][u];
}


int main() {
    int dN;
    int ns;
    int re;
    int c=1;
    
    fillfac();
    
    while (scanf("%d", &dN)!=-1) {
        ns = 0;
        for (int i=0; i<dN; ++i) {
            scanf("%d", &vd[i]);
            ns += vd[i];
        }
        
        memset(vis, 0, sizeof(vis));
        re = 0;
        
        for (int i=1, tv; i<=ns; ++i) {
            //printf("DOING n=%d\n", i);
            tv = rf(i, 0, ns, dN);
            //printf("rf(%d,%d,%d,%d)=%d\n", i, 0, ns, dN, tv);
            
            re += tv;
            re %= MOD;
        }
        printf("Case %d: %d\n", c++, re);
    }
    
    return 0;
}
