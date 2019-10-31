#include<iostream>

#include<map>
#include<string>
#include<set>
#include<utility>

#define N 10005
#define miter map<string,int>::iterator
#define siter set<int>::iterator
#define PIB pair<siter,bool>
#define REP(i,a,b) for(int i=a; i<b; i++)

using namespace std;

struct Node {
    //string name;
    int deg_in;
    set<int> child;
    
    Node() {
        deg_in = -1;
    }
};

typedef struct Node Node;

Node node[N];
int stack[N];

int accessMap(map<string, int> &_map, string &in, int &cntr) {
    miter iter = _map.find(in);
    if (iter == _map.end()) {
        _map.insert(make_pair(in,cntr++));
        //node[cntr-1].name = in;
        return cntr-1;
    } else {
        return iter->second;
    }
}

int main() {
    int cntr = 0, index, cid;
    map<string, int> idx;
    miter iter;
    PIB set_pair;
    
    string in;
    
    //input
    while (cin>>in) {
        index = accessMap(idx, in, cntr);
        
        while (cin>>in) {
            if (in == "0") {
                if (node[index].deg_in == -1) node[index].deg_in = 0;
                break;
            }
            cid = accessMap(idx, in, cntr);
            
            set_pair = node[cid].child.insert(index);
            if (set_pair.second) {
                if (node[index].deg_in == -1) {
                    node[index].deg_in = 1;
                } else {
                    node[index].deg_in++;
                }
            }
        }
    }
    
    /*
    for (int i=0; i<cntr; i++) {
        cout<<"name ="<<node[i].name<<" deg_in = "<<node[i].deg_in<<"\n";
    }
    */
    
    int top = 0;
    int front;
    int installed = 0;
    REP(i,0,cntr) {
        if (node[i].deg_in == 0) {
            stack[top++] = i;
        }
    }
    
    while (top > 0) {
        front = stack[--top];
        installed++;
        for (siter iter = node[front].child.begin(); 
            iter != node[front].child.end(); ++iter) {
            node[*iter].deg_in --;
            if (node[*iter].deg_in == 0) {
                stack[top++] = *iter;
            }
        }
    }
    
    cout<<installed<<"\n";
    
    return 0;
}