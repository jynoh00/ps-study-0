// 계단오르기 re
#include <iostream>
#include <stdio.h>

#define endl "\n"
#define MAX 300

using namespace std;

int N, ans = 0;
int scores[MAX]; // idx 0 ~ 299
int dp[MAX];
bool isVisited[MAX];

int max(int a, int b){ return a > b ? a : b; }
void input(); void solution();

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input(); solution();
    cout << dp[N-1] << endl;

    return 0;
}

void input(){
    cin >> N;
    for (int i = 0; i < N; i++){
        cin >> scores[i];
    }
}

void solution(){ // 마지막 계단은 무조건 선택
    dp[0] = scores[0];
    dp[1] = scores[0] + scores[1];
    dp[2] = max(scores[0], scores[1]) + scores[2];

    for (int i = 3; i < N; i++){
        dp[i] = max(dp[i-2], dp[i-3] + scores[i-1]) + scores[i];
    }
}

/*
6
    5
    4

5
    4
    3

4
    3
    2

3
    2
    1

4
*/