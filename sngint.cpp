#include <stdio.h>
#include <string.h>
int main(){
int T,N,M;
int primes[]={2,3,5,7};
int aexp[4];
int ct[10];
scanf("%d", &T);
while(T--){
scanf("%d",&N);
if(N==0)printf("10\n");
else if(N==1)printf("1\n");
else {
memset(aexp,0,sizeof aexp);
int x=N;
int np=0,P=4;
while(np<P&&x>1){
int exp=0;
while(x%primes[np]==0){
x /= primes[np];
exp++;
}
aexp[np] = exp;
np++;
}
if (x>1){
printf("-1\n");
} else {
memset(ct,0,sizeof ct);
ct[8]+=aexp[0]/3;
ct[9]+=aexp[1]/2;
ct[5]+=aexp[2];
ct[7]+=aexp[3];
int n2=aexp[0]%3;
int n3=aexp[1]%2;
if (n3==1) {
if (n2==1) {
ct[6]++;
} else if (n2==2) {
ct[2]++;
ct[6]++;
} else {
ct[3]++;
}} else {
if (n2==1) {
ct[2]++;
} else if (n2==2) {
ct[4]++;
}}
for (int i=0;i<=9;++i) {
while(ct[i]) {
putchar('0'+i);
ct[i]--;
}}
putchar('\n');}}}}
