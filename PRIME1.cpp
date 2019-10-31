#include<iostream>
#include<cmath>
using namespace std;

void sieve(int L,int U) {
int i,j,d;
d=U-L+1; /* from range L to U, we have d=U-L+1 numbers. */
/* use flag[i] to mark whether (L+i) is a prime number or not. */
bool *flag=new bool[d];
for (i=0;i<d;i++) flag[i]=true; /* default: mark all to be true */
for (i=(L%2!=0);i<d;i+=2) flag[i]=false;
/* sieve by prime factors staring from 3 till sqrt(U) */
for (i=3;i<=sqrt(U);i+=2) {
if (i>L && !flag[i-L]) continue;
/* choose the first number to be sieved -- >=L,
divisible by i, and not i itself! */
j=L/i*i; if (j<L) j+=i;
if (j==i) j+=i; /* if j is a prime number, have to start form next
one */
j-=L; /* change j to the index representing j */
for (;j<d;j+=i) flag[j]=false;
}
if (L<=1) flag[1-L]=false;
if (L<=2) flag[2-L]=true;
for (i=0;i<d;i++) if (flag[i]) cout << (L+i)<<endl;
}

int main() {
    int t, m, n, f=0;
    bool prime;
    cin>>t;
    for (int zz=0;zz<t;zz++) {
        scanf("%d%d", &m, &n);
        sieve(m, n);
        if (zz+1 != t) printf("\n");
    }
    return 0;
}
