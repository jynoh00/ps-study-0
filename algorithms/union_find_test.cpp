#include <iostream>

#define MAX 100

using namespace std;

int N;
pair<int, int> p_arr[MAX];
int parents[MAX];

int find(int u){ return u == parents[u] ? u : parents[u] = find(parents[u]); }

void join(int u, int v){
    u = find(u);
    v = find(v);

    if (u == v) return;

    parents[u] = v;
}

int main(){
    for (int i = 0; i < 8; i++){
        int a, b;
        cin >> a >> b;
        p_arr[i] = make_pair(a, b);
    }

    for (int i = 1; i <= 9; i++) parents[i] = i;
    for (int i = 1; i <= 9; i++) cout << parents[i] << " ";
    cout << endl;

    for (pair<int, int> p : p_arr){
        cout << p.first << "," << p.second << endl;
        if (find(p.first) == 0) continue; // 안쓰는 값
        if (find(p.second) == 0) continue;

        join(find(p.first), find(p.second));
    }

    for (int i = 1; i <= 9; i++) cout << parents[i] << " ";
    cout << endl;

    

    return 0;
}
