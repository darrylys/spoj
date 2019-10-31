#include<cstdio>
#include<cstring>
#include<queue>

#define X 10001
#define DLIM 200

using namespace std;

bool flag[X];
int digit;
int order;

void solve(int x) {
    queue<int> vs;      //lucky number
    queue<int> ds;      //digit num
    queue<int> ids;     //6^?
    int v, d, id;
    
    //initials
    digit = -1;
    order = -1;
    vs.push(6); 
    vs.push(8);
    
    ds.push(1); 
    ds.push(1);
    
    ids.push(1); 
    ids.push(0);
    //memset(flag, false, x*sizeof(bool));
    
    while (!vs.empty()) {
        v = vs.front(); d = ds.front(); id = ids.front();
        vs.pop(); ds.pop(); ids.pop();
        
        if (d > DLIM) continue;
        flag[v%x] = true;
        
        if (id == 0) { //pure 8
            if (v % x == 0) {
                digit = d;
                order = id;
                break;
            } else {
                //if (!flag[((v*10)+6)%x]) {
                    vs.push(((v*10)+6)%x);
                    ds.push(d+1);
                    ids.push(1);
                    flag[((v*10)+6)%x] = true;
                //}
                //if (!flag[((v*10)+8)%x]) {
                    vs.push(((v*10)+8)%x);
                    ds.push(d+1);
                    ids.push(0);
                    flag[((v*10)+8)%x] = true;
                //}
            }
        } else { //has 6
            if (v%x == 0) {
                digit = d;
                order = id;
                break;
            } else {
                //if (!flag[((v*10)+6)%x]) {
                    vs.push(((v*10)+6)%x);
                    ds.push(d+1);
                    ids.push(id+1);
                    flag[((v*10)+6)%x] = true;
                //}
            }
        }
    }
}

int main() {
    int test, x;
    scanf("%d", &test);
    while (test--) {
        scanf("%d", &x);
        
        if (x % 5) {
        
            solve(x);
            if (digit != -1 || order != -1) {
                for (int i=0; i<digit-order; i++) {
                    putchar('8');
                }
                for (int i=0; i<order; i++) {
                    putchar('6');
                }
            } else {
                putchar('-');
                putchar('1');
            }
        } else {
            putchar('-');
            putchar('1');
        }
        putchar('\n');
    }
    return 0;
}