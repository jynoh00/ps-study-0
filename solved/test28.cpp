// RGB거리 2

#include <iostream>
#include <stdio.h>

#define MAX 1000
#define endl "\n"

using namespace std;

int ans = 1000001;
int N;
int homes[MAX][3];

int min(int a, int b){ return a < b ? a : b; }
void input();
void solution(int selected_homes, int cost_sum, int before_idx, int after_idx, int home_one_idx);

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solution(0, 0, 3, 3, 3);

    cout << ans << endl;

    return 0;
}

void input(){
    cin >> N;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < 3; j++){
            cin >> homes[i][j];
        }
    }
}

void solution(int selected_homes, int cost_sum, int before_idx, int after_idx, int home_one_idx){ // idx: 3(상관없음), 0(빨강), 1(초록), 2(파랑)
    if (selected_homes == N){
        ans = min(ans, cost_sum);
        return;
    }

    int i = selected_homes;
    for (int j = 0; j < 3; j++){ // R, G, B 중 선택
        if (i == N-1) after_idx = home_one_idx;
        if (j == before_idx || j == after_idx) continue;
        if (i == 0) home_one_idx = j;

        solution(selected_homes+1, cost_sum+homes[i][j], j, after_idx, home_one_idx);
    }
}


/*
시간초과 -> DP?

그리디? -> 안됨.



*/