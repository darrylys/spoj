#include<cstdio>
#define RO 0
#define SC 1
#define PA 2
#define SA 2
#define SB 1
#define TIE 0
#define N 52
char sv[N];
char en[N][N];
int g(char m){
if (m=='R')return RO;
if (m=='S')return SC;
if (m=='P')return PA;
}
int ww(int m1,int m2){
if (m1== m2)return TIE;
int r=m1-m2;
if (r==2)r-=3;
else if (r==-2)r+=3;
if (r==-1)return SA;
else return SB;
}
int cs(int n,int r){
int sc=0;
for (int i=0; i<r; i++){
for (int j=0; j<n; j++){
int w=ww(g(sv[i]), g(en[j][i]));
if (w==SA)sc+=2;
else if (w==TIE)sc++;
}
}
return sc;
}
int cms(int n,int r){
int as=0;
int rs;
int max;
for (int i=0;i<r;i++){
max = -1;
for (int k=RO;k<=PA;k++){
rs = 0;
for (int j=0;j<n;j++){
int w=ww(k,g(en[j][i]));
if (w==SA)rs+=2;
else if (w==TIE)rs++;
}
if (rs>max)max=rs;
}
as+=max;
}
return as;
}
int main(){
int r, n;
scanf("%d%s%d", &r,sv,&n);
for (int i=0;i<n;i++) scanf("%s",en[i]);
printf("%d\n%d\n",cs(n,r),cms(n,r));
return 0;
}