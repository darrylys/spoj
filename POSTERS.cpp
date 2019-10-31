#include<cstdio>
#include<set>
#include<cstdlib>
#include<cstring>

#define sii set<int>::iterator
#define START false
#define END true

using namespace std;

typedef struct {
    int pt;
    bool tipe;
    int owner;
} Point;

Point point[80010];
bool flag[40010];

int cmp(const void* o1, const void* o2) {
    Point* a = (Point*) o1;
    Point* b = (Point*) o2;
    
    int r = a->pt - b->pt;
    if (!r) {
        if (a->tipe == b->tipe) {
            return b->owner - a->owner;
        } else {
            if (a->tipe && !(b->tipe)) {
                return -1;
            } else {
                return 1;
            }
        }
    }
    return r;
}

int main() {
    int test, a, b, n, topmost;
    set<int> stat;
    
    scanf("%d", &test);
    while (test--) {
        scanf("%d", &n);
        memset(flag, false, n*sizeof(bool));
        for (int i=0; i<n; i++) {
            scanf("%d %d", &a, &b);
            point[2*i].pt = a;
            point[2*i].tipe = START;
            point[2*i].owner = i+1;
            point[2*i+1].pt = b+1;
            point[2*i+1].tipe = END;
            point[2*i+1].owner = i+1;
        }
        
        qsort(point, n*2, sizeof(point[0]), cmp);
        /*
        for (int i=0; i<(n<<1); i++) {
            printf("i=%d pt=%d tipe=%d owner=%d\n", i, point[i].pt, (int)(point[i].tipe), point[i].owner);
        }*/
        
        
        int ot = n<<1;
        int prev = point[0].pt;
        int topmost = -1;
        int num = 0;
        for (int i=0; i<ot; i++) {
            
            if (point[i].tipe == START) {
                
                if (point[i].pt == prev) {
                    if (point[i].owner > topmost) {
                        topmost = point[i].owner;
                        flag[point[i].owner] = true;
                        num++;
                    }
                } else {
                    if (point[i-1].tipe == END) {
                        if (stat.empty()) topmost = -1;
                        else {
                            sii iter = stat.end();
                            iter--;
                            topmost = *iter;
                            
                            if (!flag[topmost]) {
                                flag[topmost] = true;
                                num++;
                            }      
                        }                  
                    }
                    if (point[i].owner > topmost) {
                        topmost = point[i].owner;
                        flag[point[i].owner] = true;
                        num++;
                    }
                    prev = point[i].pt;                   
                }
                stat.insert(point[i].owner);
            } else {
                if (point[i].pt == prev) {
                    if (point[i].owner == topmost) {
                        if (!flag[point[i].owner]) {
                            flag[point[i].owner] = true;
                            num++;
                        }
                    } else {
                        if (!flag[point[i].owner]) {
                            flag[point[i].owner] = true;
                        }
                    }
                    stat.erase(point[i].owner);
                } else {
                    sii iter = stat.end();
                    iter--;
                    topmost = *iter;
                    
                    if (!flag[topmost]) {
                        flag[topmost] = true;
                        num++;
                    }
                    prev = point[i].pt;
                    stat.erase(point[i].owner);
                }
            }
            //printf("i=%d top=%d num=%d current_processed=%d tipe=%d\n", i, topmost, num, point[i].owner, point[i].tipe);
        }
        stat.clear();
        printf("%d\n", num);
    }
    return 0;
}
