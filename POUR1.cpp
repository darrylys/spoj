//impl Simulation + Search Pruning

#include<cstdio>
#include<queue>
#include<map>

using namespace std;

int _max(int a, int b) {return (a>=b)?a:b;}

int encode(int a, int b, int ma, int mb) {
    return a * (_max(ma, mb)+1) + b;
}

int main () {
    int t, a, b, c, na, nb, lv, ta, tb, e;
    queue<int> as, bs, lvl;
    map<int, bool> bank;
    map<int, bool>::iterator iter;
    scanf("%d",&t);
    while(t--) {
        scanf("%d%d%d", &a, &b, &c);
        if (c > a && c > b) {
            printf("-1\n");
            continue;
        }
        as.push(0); bs.push(0); lvl.push(0);
        bank[0] = true;
        while (!as.empty()) {
            na = as.front(); nb = bs.front(); lv = lvl.front();
            as.pop(); bs.pop(); lvl.pop();
            //printf("lv = %d, na = %d, nb = %d\n", lv, na, nb);
            if (na == c || nb == c) {
                printf("%d\n", lv);
                goto exist;
            }

            //case 3: both full
            if (nb == b && na == a) continue;

            //case 2: both empty
            if (na == 0 && nb == 0) {
                if (lv == 0) {
                    //fill a
                    as.push(a); bs.push(0); lvl.push(lv+1);
                    bank[encode(a,0,a,b)] = true;

                    //fill b
                    as.push(0); bs.push(b); lvl.push(lv+1);
                    bank[encode(0,b,a,b)] = true;
                }
                continue;
            }

            //case 1: one is full
            if (na == a) {
                if (nb < b) {
                    if (a > b) {
                        tb = b;
                        ta = a - b + nb;
                    } else {
                        e = _max(nb + na - b, 0);
                        ta = e;
                        tb = na + nb - e;
                    }
                    iter = bank.find(encode(ta,tb,a,b));
                    if (iter == bank.end()) {
                        as.push(ta); bs.push(tb); lvl.push(lv+1);
                        bank[encode(ta,tb,a,b)] = true;
                    }

                    if (nb > 0) {
                        iter = bank.find(encode(0,nb,a,b));
                        if (iter == bank.end()) {
                            as.push(0); bs.push(nb); lvl.push(lv+1);
                            bank[encode(0,nb,a,b)] = true;
                        }
                    }
                }
                continue;
            } else if (nb == b) {
                if (na < a) {
                    if (b > a) {
                        ta = a;
                        tb = b - a + na;
                    } else {
                        e = _max(nb + na - a, 0);
                        tb = e;
                        ta = nb + na - e;
                    }
                    iter = bank.find(encode(ta,tb,a,b));
                    if (iter == bank.end()) {
                        as.push(ta); bs.push(tb); lvl.push(lv+1);
                        bank[encode(ta,tb,a,b)] = true;
                    }

                    if (na > 0) {
                        iter = bank.find(encode(na,0,a,b));
                        if (iter == bank.end()) {
                            as.push(na); bs.push(0); lvl.push(lv+1);
                            bank[encode(na,0,a,b)] = true;
                        }
                    }
                }
                continue;
            }

            //case 4: one not full
            if (na < a && nb == 0) {
                if (na > b) {
                    ta = na - b;
                    tb = b;
                } else {
                    tb = na;
                    ta = 0;
                }
                iter = bank.find(encode(ta,tb,a,b));
                if (iter == bank.end()) {
                    as.push(ta); bs.push(tb); lvl.push(lv+1);
                    bank[encode(ta,tb,a,b)] = true;
                }

                //empty filled
                iter = bank.find(encode(na,b,a,b));
                if (iter == bank.end()) {
                    as.push(na); bs.push(b); lvl.push(lv+1);
                    bank[encode(na,b,a,b)] = true;
                }
                continue;
            } else if (na == 0 && nb < b) {
                if (nb > a) {
                    tb = nb - a;
                    ta = a;
                } else {
                    ta = nb;
                    tb = 0;
                }
                iter = bank.find(encode(ta,tb,a,b));
                if (iter == bank.end()) {
                    as.push(ta); bs.push(tb); lvl.push(lv+1);
                    bank[encode(ta,tb,a,b)] = true;
                }

                //empty filled
                iter = bank.find(encode(a,nb,a,b));
                if (iter == bank.end()) {
                    as.push(a); bs.push(nb); lvl.push(lv+1);
                    bank[encode(a,nb,a,b)] = true;
                }
                continue;
            }
        }
        printf("-1\n");

        exist:
        bank.clear();
        while (!as.empty()) {
            as.pop();
            bs.pop();
            lvl.pop();
        }
    }
}
