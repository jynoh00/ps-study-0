// 스티커
#include <iostream>
#include <stdio.h>
#include <cstring>

#define endl "\n"
#define MAX 100001 // 0(버림) 1~100000

using namespace std;

int T, N;
int scores[3][MAX]; // scores[0][0] = 0;
int ans = 0;
int dp[3][MAX];

void input();
void solution();

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    return 0;
}

void input(){
    cin >> T;
    for (int t = 0; t < T; t++){
        cin >> N;
        for (int i = 1; i <= 2; i++){
            for (int j = 1; j <= N; j++){
                cin >> scores[i][j];
            }
        }
        solution();
    }
}

void solution(){
    dp[1][1] = scores[1][1];
    dp[2][1] = scores[2][1];
    //dp[0][0], dp[0][1] = 0

    for (int j = 2; j <= N; j++){
        dp[1][j] = max(dp[2][j-1], dp[2][j-2]) + scores[1][j];
        dp[2][j] = max(dp[1][j-1], dp[1][j-2]) + scores[2][j];
    }

    cout << max(dp[1][N], dp[2][N]) << endl;
}

/*
상근이 동생 상냥이

문방구에서 스티커 2n개 구매
2행(x) n열(y)

땐 스티커의 인접 스티커는 사용불가
각 스티커에 점수가 있음. (scores)
점수의 합이 최대가 되게 스티커를 떼려함

50 10 100 20 40
30 50 70 10 60

각 열별로

50  40  200 130 250
30  100 110 210 190

dp[1][1] = scores[1][1];
dp[1][2] = scores[1][2];

dp[1][N] = max(dp[2][N-1], dp[2][N-2]) + scores[1][N];
dp[2][N] = max(dp[1][N-1], dp[1][N-2]) + scores[2][N];




*/