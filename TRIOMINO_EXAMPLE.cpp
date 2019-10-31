#include <cstdio>
#include <cstring>
#include <set>
 
using namespace std;
 
#define MAX_N 1024
 
#define FULL 1
#define EMPTY 0
 
void input(void);
void solve(void);
 
int get_grundy(int len, int s1, int s2);
 
int n;
int grundy[MAX_N][2][2];
 
int main(void)
{
  memset(grundy, -1, sizeof(grundy));
  int t;
  scanf("%d", &t);
  while(t--) {
    input();
    solve();
  }
    
  return 0;
}
 
void input(void)
{
  scanf("%d", &n);
}
 
void solve(void)
{
  //  printf("%d %d %d %d\n", get_grundy(n, FULL, FULL), get_grundy(n, FULL, EMPTY), get_grundy(n, EMPTY, FULL), get_grundy(n, EMPTY, EMPTY));
  printf("%s\n", get_grundy(n, FULL, FULL) ? "X" : "Y");
}
 
int get_grundy(int len, int s1, int s2)
{
  if(len == 0)                  return 0;
  if(grundy[len][s1][s2] != -1) return grundy[len][s1][s2];
 
  set <int> used;
  if(s1 == EMPTY) used.insert(get_grundy(len - 1, FULL, s2));
  if(s2 == EMPTY) used.insert(get_grundy(len - 1, s1, FULL));
  for(int i = 0; i + 2 <= len; i++) {
    int num = 0;
    num = get_grundy(i, s1, EMPTY) ^ get_grundy(len - i - 2, FULL, s2);
    used.insert(num);
    num = get_grundy(i, s1, FULL) ^ get_grundy(len - i - 2, EMPTY, s2);
    used.insert(num);
  }
  
  int ans = 0;
  for(int i = 0; ; i++) if(used.find(i) == used.end()) { ans = i; break; }
  
  return grundy[len][s1][s2] = ans;
} 