#include<iostream>
#include<map>
using namespace std;
#define FOR(i,a,b) for(int i=a;i<b;i++)
#define REP(i,n) FOR(i,0,n)
typedef pair<int,int> PII;
PII dp[1024][1024];
int dp2[1024][1024];
int arr[1024];
map<int,int>mp;
int n;
void process1(void)
{
  FOR(i,1,n+1)
    {
      FOR(j,1,n)
   {
     PII p=dp[i][j-1];
     int cntless=p.first;
     int cntmore=p.second;
     if(i+j<=n)if(mp[i+j]<mp[i])cntmore++;
     if(i-j>0)if(mp[i-j]<mp[i])cntless++;
     dp[i][j]=PII(cntless,cntmore);
   }
    }
}

void printdp() {
    FOR(i,1,n+1) {
        FOR(j,0,n+1) {
            PII p = dp[i][j];
            printf("(%3d,%3d) ", p.first, p.second); //first = smaller, snd = larger
        }
        printf("\n");
    }
}

void process2(void)
{
  FOR(i,1,n+1)dp2[i][i]=mp[i];
  FOR(j,1,n)
    FOR(i,1,n-j+1)
    dp2[i][i+j]=min(dp2[i+1][i+j]+(mp[i]-dp[i][j].second)*(j+1),dp2[i][i+j-1]+(mp[i+j]-dp[i+j][j].first)*(j+1));
}

int main()
{
  int ncases;
  scanf("%d",&ncases);
  while(ncases--)
    {
      scanf("%d",&n);
      FOR(i,1,n+1)
   {
     scanf("%d",&arr[i]);
     mp[arr[i]]=i;
   }
      FOR(i,1,n+1)dp[i][0]=PII(0,0);
      process1();
      printdp();
      process2();
      cout<<dp2[1][n]<<"\n";
    }
  return 0;
}

