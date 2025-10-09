// 공항 - 유니온파인드 알고리즘

#include <iostream>
#include <stdio.h>

#define MAX 100001

using namespace std;

int G, P, ans = 0;
int parents[MAX];
int plane_gates[MAX];

void input();
void solution();

int find(int u){ return u == parents[u] ? u : parents[u] = find(parents[u]); }
void join(int u, int v){
    u = find(u);
    v = find(v);

    if (u == v) return;

    // 더 작은 쪽을 가리키게
    if (u < v) parents[v] = u;
    else parents[u] = v; 
}

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solution();

    return 0;
}

void input(){
    cin >> G >> P;

    for (int i = 0; i < P; i++){
        cin >> plane_gates[i];
    }
}

void solution(){
    for (int i = 1; i <= G; i++) parents[i] = i;

    for (int i = 0; i < P; i++){
        // cout << "i= " << plane_gates[i] << ": ";
        // for (int j = 1; j<= G; j++) cout << parents[j] << " ";
        // cout << "-> ";

        if (find(plane_gates[i]) == 0) break;
        else{
            ans++;
            join(find(plane_gates[i]), find(plane_gates[i])-1);
        }

        // for (int j = 1; j<= G; j++) cout << parents[j] << " ";
        // cout << endl;
    }

    cout << ans << endl;
}