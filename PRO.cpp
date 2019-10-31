#include<cstdio>
#include<map>
#include<utility>

#define ll unsigned long long int
#define miter map<int,int>::iterator

using namespace std;

int main() {
    map<int, int> box;
    int n;
    ll total = 0;
    scanf("%d", &n);
    miter iter, smallest, largest;
    while (n--) {
        int k, x;
        scanf("%d", &k);
        while (k--) {
            scanf("%d",&x);
            iter = box.find(x);
            if (iter == box.end()) {
                box.insert(make_pair(x, 1));
            } else {
                iter->second++;
            }
        }
        smallest = box.begin();
        largest = box.end();
        largest--;
        total += -smallest->first + largest->first;
        if (smallest->second > 1) 
            smallest->second--; 
        else 
            box.erase(smallest);
        
        if (largest->second > 1) 
            largest->second--; 
        else 
            box.erase(largest);
    }
    printf("%llu\n", total);
    return 0;
}
