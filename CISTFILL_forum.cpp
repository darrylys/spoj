    #include <algorithm>
    #include <iostream>
    #include <cstdio>
    using namespace std;

    void echo(long long a) {
       cout << a / 100;
       cout << ".";
       if(a % 100 < 10)
          cout << 0;
       cout << a % 100;
       cout << endl;
    };

    struct cistern {
       int base, height;
       long long sq;
       
       inline friend bool operator<(const cistern &a, const cistern &b) {
          return a.base < b.base;
       };
    };

    int N;
    long long V;
    cistern cisterns[50000];

    long long amount(long long level) {
       long long total = 0;
       for(int i = 0; i < N; ++i) {
          if(level <= cisterns[i].base)
             break;
          if(level >= cisterns[i].base + cisterns[i].height)
             total += cisterns[i].sq * cisterns[i].height;
          else
             total += cisterns[i].sq * (level - cisterns[i].base);
       };
       return total;
    };

    int main() {
       int T;
       scanf("%d", &T);
       int c, d;
       for(int t = 0; t < T; ++t) {
          long long total = 0;
          int top = 0;
          scanf("%d", &N);
          for(int i = 0; i < N; ++i) {
             scanf("%d%d%d%d", &cisterns[i].base, &cisterns[i].height, &c, &d);
             cisterns[i].sq = c * d;
             cisterns[i].base *= 100LL;
             cisterns[i].height *= 100LL;
             total += cisterns[i].sq * cisterns[i].height;
             if (top < cisterns[i].base + cisterns[i].height)
                top = cisterns[i].base + cisterns[i].height;
             //top >?= cisterns[i].base + cisterns[i].height;
          };
          sort(cisterns, cisterns + N);
          cin >> V;
          V *= 100LL;
          if(V > total)
             printf("OVERFLOW\n");
          else if(V == total)
             echo(top);
          else {
             long long low = cisterns[0].base, high = top, mid;
             while(high - low > 1) {
                mid = (low + high) / 2;
                if(amount(mid) >= V)
                   high = mid;
                else
                   low = mid;
             };
             if(amount(low) >= V)
                echo(low);
             else
                echo(high);
          };
       };
       return 0;
    };
