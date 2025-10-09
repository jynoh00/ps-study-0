#include <iostream>

#define MAX 100000

using namespace std;

int G, P;
int ans = 0;
int parent[MAX];

int find(int u){ return u == parent[u] ? u : parent[u] = find(parent[u]); }

void join(int u, int v){
    u = find(u);
    v = find(v);

    if (u == v) return;
    
    if (u < v) parent[v] = u;
    else parent[u] = v;
}

int main(){
    cin >> G >> P;
    for (int i = 1; i <= G; i++) parent[i] = i;

    for (int i = 0; i < P; i++){
        int a;
        cin >> a;
        if (find(a) == 0) break;
        else{
            ans++;
            join(find(a), find(a)-1);
        }
    }

    cout << ans << endl;
}

// 유니온 - 조