#include<cstdio>
#include<algorithm>

using namespace std;

int arr[2010];
int unik[2010];
int pntr[2010];

int main() {
    int n, u, v, key, ans, sol, prev, cntr;
    while (scanf("%d",&n) && n) {
        for (int i=0; i<n; i++) {
            scanf("%d",&arr[i]);
        }
        sort(arr, arr+n);
        prev = arr[0];
        unik[0] = arr[0];
        pntr[0] = 0;
        cntr = 1;
        for (int i=1; i<n; i++) {
            if (prev != arr[i]) {
                unik[cntr] = arr[i];
                pntr[cntr] = i;
                cntr++;
                prev = arr[i];
            }
        }
        sol = 0;
        for (int i=0; i<n-2; i++) {
            for (int j=i+1; j<n-1; j++) {
                key = arr[i] + arr[j];
                u = 0;
                v = cntr;
                while (true) {
                    if (u >= v) {
                        if (u < cntr)
                            ans = pntr[u];
                        else
                            ans = 5000;
                        break;
                    } else {
                        int c = (u+v)/2;
                        if (key > unik[c]) {
                            u = c+1;
                        } else if (key < unik[c]) {
                            v = c;
                        } else {
                            if (c+1 < cntr)
                                ans = pntr[c+1];
                            else 
                                ans = 5000;
                            break;
                        }
                    }
                }
                
                if (ans < n) {
                    sol += n-ans;
                }
            }
        }
        
        printf("%d\n", sol);
    }
    return 0;
}