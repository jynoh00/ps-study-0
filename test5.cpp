// 스타트와 링크
// 백트래킹, 브루트포스 -> 재귀함수로

#include <iostream>
#include <stdio.h>

#define endl "\n"
#define MAX 20

using namespace std;

int N;
int arr[MAX][MAX];
int ans = 99999999;
bool isTeamA[MAX];

void input(){
    cin >> N;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cin >> arr[i][j];
        }
    }
}

int min(int a, int b){ return a < b ? a : b;}

int stat_check(){
    int teamA = 0, teamB = 0;

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (i == j) continue;
            if (isTeamA[i] && isTeamA[j]) teamA += arr[i][j];
            else if (isTeamA[i] == isTeamA[j]) teamB += arr[i][j];
        }
    }
    return teamA > teamB ? (teamA - teamB) : (teamB - teamA);
}

void calcu(int idx, int sum){
    if (sum == N/2){
        ans = min(ans, stat_check());
        return;
    }

    for (int i = idx; i < N; i++){
        isTeamA[i] = true;
        calcu(i+1, sum+1);
        isTeamA[i] = false;
    }
}

void solution(){
    input();
    calcu(0, 0);

    cout << ans << endl;
}

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    solution();

    return 0;
}

/*

N명 모임 -> N은 짝수
N/2로 스타트팀, 링크팀 나눔

1~N까지 사람에게 번호

능력치
Sij: i번 사람과 j번 사람이 같은 팀일 때 팀에 더해지는 능력치
팀의 능력치는 팀에 속한 모든 Sij의 합

Sij != Sji ?? => i랑 j가 같은 팀이면 Steam += Sij + Sji

두 팀 능력치 차이 최소

4 <= N <= 20 짝수

4*4 ~ 20*20


1 2 3 4

12 - 34
13 - 24
14 - 23

4C2 / 2 = 3

0 1 2 3 4 5

6C3 / 2 

N/2명 고르고 스탯 차이 비교


6C3 => 654/321 20가지

*/