//Implementation: Optimized Brute-Force

#include<stdio.h>
#include<queue>
#include<algorithm>

#define FOR(i,a,b) for(int i=a; i<=b; ++i)
#define ll long long

using namespace std;

ll LIMIT = 1000000000000LL;
ll arr_b[454200];
ll tru[454200];

int max(int a, int b) {
    if (a>b) return a;
    else return b;
}

int build() {
    queue<ll> qs;
    queue<char> lvs;
    ll q;
    char lv;
    int cntr = 1;
    arr_b[0] = 1;
    
    qs.push(4);
    qs.push(7);
    lvs.push(1);
    lvs.push(1);
    
    while (!qs.empty()) {
        lv = lvs.front(); lvs.pop();
        q = qs.front(); qs.pop();
        arr_b[cntr++] = q;
        
        if (lv < 12) {
            qs.push(q*10+4);
            qs.push(q*10+7);
            lvs.push(lv+1);
            lvs.push(lv+1);
        }
    }
    
    return cntr;
}

int dup(int n, int last) {
    ll prev[25];
    int cntr = last;
    FOR(t,0,0) { //20
        prev[14] = arr_b[t];
        
        FOR(p,t,1) { //19
            if (prev[14]*arr_b[p] < LIMIT) {
            prev[15] = prev[14]*arr_b[p];
            
            FOR(q,p,1) { //18
                if (prev[15]*arr_b[q] < LIMIT) {
                prev[16] = prev[15]*arr_b[q];
                
                FOR(r,q,1) { //17
                    if (prev[16]*arr_b[r] < LIMIT) {
                    prev[17] = prev[16]*arr_b[r];
                    
                    FOR(s,r,1) { //16
                        if (prev[17]*arr_b[s] < LIMIT) {
                        prev[18] = prev[17]*arr_b[s];
                        
                        FOR(a,s,1) { //15
                            if (prev[18]*arr_b[a] < LIMIT) {
                            prev[0] = prev[18]*arr_b[a];
                        
                            FOR(b,a,2) { //14
                                if (prev[0]*arr_b[b] < LIMIT) {
                                prev[1] = prev[0]*arr_b[b];
                                
                                FOR(c,b,2) { //13
                                    if (prev[1]*arr_b[c] < LIMIT) {
                                    prev[2] = prev[1]*arr_b[c];
                                    
                                    FOR(d,c,2) { //12
                                        if (prev[2]*arr_b[d] < LIMIT) {
                                        prev[3] = prev[2]*arr_b[d];
                                        
                                        FOR(e,d,2) { //11
                                            if (prev[3]*arr_b[e] < LIMIT) {
                                            prev[4] = prev[3]*arr_b[e];
                                            
                                            FOR(f,e,2) { //10
                                                if (prev[4]*arr_b[f] < LIMIT) {
                                                prev[5] = prev[4]*arr_b[f];
                                                
                                                FOR(g,f,2) { //9
                                                    if (prev[5]*arr_b[g] < LIMIT) {
                                                    prev[6] = prev[5]*arr_b[g];
                                                    
                                                    FOR(h,g,2) { //8
                                                        if (prev[6]*arr_b[h] < LIMIT) {
                                                        prev[7] = prev[6]*arr_b[h];
                                                        
                                                        FOR(i,h,4) { //7
                                                            if (prev[7]*arr_b[i] < LIMIT) {
                                                            prev[8] = prev[7]*arr_b[i];
                                                            
                                                            FOR(j,i,6) { //6
                                                                if (prev[8]*arr_b[j] < LIMIT) {
                                                                prev[9] = prev[8]*arr_b[j];
                                                                
                                                                FOR(k,j,6) { //5
                                                                    if (prev[9]*arr_b[k] < LIMIT) {
                                                                    prev[10] = prev[9]*arr_b[k];
                                                                    
                                                                    FOR(l,k,14) { //4
                                                                        if (prev[10]*arr_b[l] < LIMIT) {
                                                                        prev[11] = prev[10]*arr_b[l];
                                                                        
                                                                        FOR(m,l,30) { //3
                                                                            if (prev[11]*arr_b[m] < LIMIT) {
                                                                            prev[12] = prev[11]*arr_b[m];
                                                                            
                                                                            FOR(x,(max(1,m)),126) { //2
                                                                                if (prev[12]*arr_b[x] < LIMIT) {
                                                                                prev[13] = prev[12]*arr_b[x];
                                                                                
                                                                                FOR(y,x,n) { //1
                                                                                    
                                                                                    if (prev[13]*arr_b[y] < LIMIT) {
                                                                                        arr_b[cntr++] = prev[13]*arr_b[y];
                                                                                    } else {break;}
                                                                                }
                                                                                } else {break;}
                                                                            }
                                                                            } else {break;}
                                                                        }
                                                                        } else {break;}
                                                                    }
                                                                    } else {break;}
                                                                }
                                                                } else {break;}
                                                            }
                                                            } else {break;}
                                                        }
                                                        } else {break;}
                                                    }
                                                    } else {break;}
                                                }
                                                } else {break;}
                                            }
                                            } else {break;}
                                        }
                                        } else {break;}
                                    }
                                    } else {break;}
                                }
                                } else {break;}
                            }
                            } else {break; }
                        }
                        } else {break; }
                    }
                    } else {break; }
                }
                } else {break; }
            }
            } else {break; }
        }
    }
    return cntr;
}

int bsearch(ll val, int n, bool &isfound) {
    int u=0, v=n, c;
    
    while (u<v) {
        c = (u+v)/2;
        if (tru[c] == val) {
            isfound = true;
            return c;
        } else if (tru[c] > val) {
            v = c;
        } else {
            u = c+1;
        }
    }
    isfound = false;
    return u-1;
}

int main() {
    int cntr = build();
    int l = dup(cntr-1, cntr);
    
//    printf("l=%d\n\n", l);
    sort(arr_b, arr_b+l);
    ll prev = arr_b[1], a, b;
    arr_b[l] = LIMIT+1;//dummy
    int ctr = 0;
    for (int i=2; i<=l; i++) {
        if (prev != arr_b[i]) {
            tru[ctr++] = prev;
            prev = arr_b[i];
        }
    }
    
//    for (int i=0; i<ctr; i++) {
//        printf(">>> %lld\n", tru[i]);
//    }
    
    //printf("ctr=%d\n", ctr);
    
    int test;
    scanf("%d", &test);
    bool fa, fb;
    while (test--) {
        scanf("%lld %lld", &a, &b);
        int ia = bsearch(a, ctr, fa), ib = bsearch(b, ctr, fb), res;
        if (fa) {
            if (fb) {
                res = ib-ia+1;
            } else {
                res = ib-ia+1;
            }
        } else {
            if (fb) {
                res = ib-ia;
            } else {
                res = ib-ia;
            }
        }
        printf("%d\n", res);
        
    }
    return 0;
}   