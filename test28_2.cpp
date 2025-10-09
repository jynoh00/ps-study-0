// RGB거리2 -> 시간초과 문제 => DP
#include <iostream>
#include <stdio.h>

#define MAX 1000
#define endl "\n"

using namespace std;

int costs[MAX][3]; // 0 ~ 999번 집 가격 (RGB)
int N, ans = MAX*MAX+1;
int dp[MAX][3]; // 0~999번집을 [][0], [][1], [][2]로 칠했을 때의 최소값

int min(int a, int b){ return a < b ? a : b; }
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
    cin >> N;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < 3; j++){
            cin >> costs[i][j];
        }
    }
}

void solution(){
    for (int first = 0; first < 3; first++){
        for (int j = 0; j < 3; j++){
            if (j == first) dp[0][j] = costs[0][j]; // 선택
            else dp[0][j] = 1000000000; // 불가능하게 큰 값
        }

        for (int i = 1; i < N; i++){ // 1 ~ N-1
            dp[i][0] = min(dp[i-1][1], dp[i-1][2]) + costs[i][0]; 
            dp[i][1] = min(dp[i-1][0], dp[i-1][2]) + costs[i][1]; 
            dp[i][2] = min(dp[i-1][0], dp[i-1][1]) + costs[i][2]; 
        }

        for (int last = 0; last < 3; last++){
            if (last == first) continue;
            ans = min(ans, dp[N-1][last]);
        }
    }
}


/*
첫집 색 하나 정해
R:
    -> 이거에 대해 DP => min()
G:
    -> 이거에 대해 DP => min()
B:
    -> 이거에 대해 DP => min()

왜 재귀보다 빠를까? 시간 복잡도가
*/