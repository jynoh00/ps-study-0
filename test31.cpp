// 외적으로, CCW 알고리즘

#include <iostream>
#include <stdio.h>

#define endl "\n"

using namespace std;

pair<int, int> p[3];

void input();
int solution();

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    
    if (solution() > 0) cout << 1 << endl;
    else if (solution() < 0) cout << -1 << endl;
    else cout << 0 << endl;

    return 0;
}

void input(){
    for (int i = 0; i < 3; i++){
        int x, y; cin >> x >> y;
        p[i] = make_pair(x,y);
    }
}

int solution(){ return (p[1].first-p[0].first) * (p[2].second-p[0].second) - (p[2].first-p[0].first) * (p[1].second-p[0].second); }