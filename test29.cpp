// 공항

#include <iostream>
#include <stdio.h>

#define MAX 100000
#define endl "\n"

using namespace std;

int G, P, ans = 0;
int plane_gates[MAX]; // 0 ~ 값-1 중 하나의 게이트에 도킹
bool isVisited[MAX];
int parent[MAX];

int find(int u);
void merge(int u, int v);
void input();
void solution();

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solution();

    cout << ans << endl;

    return 0;
}

void input(){
    cin >> G >> P;
    for (int i = 0; i < P; i++){
        cin >> plane_gates[i];
    }
}

void solution(){
    for (int i = 0; i < P; i++){
        bool isCan = false;
        for (int j = plane_gates[i]-1; j >= 0; j--){
            if (isVisited[j]) continue;
            else{
                isVisited[j] = true;
                ans++;
                isCan = true;

                break;
            }
        }

        if (isCan == false) break;
    }
}

int find(int u){ return u == parent[u] ? u : find(parent[u]); }

void join(int u, int v){
    u = find(u);
    v = find(v);

    if (u == v) return;
    parent[u] = v;
}