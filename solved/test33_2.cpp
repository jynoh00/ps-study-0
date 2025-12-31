#include <iostream>
#include <stdio.h>
#include <vector>

#define endl "\n"

using namespace std;

int dices[10], ans = 0;
pair<int, int> players[4]; // i, j
bool isSomeone[50][50]; // 인덱스 여유 공간
vector<vector<int>> map_scores = { // i: 0, 1, 2, 3
    {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40}, // 0 ~ 20 : 1~20만 유효
    {10, 13, 16, 19, 25, 30, 35, 40}, // 5일때 : 1 ~ 7만 유효
    {20, 22, 24, 25, 30, 35, 40}, // 10일때 : 1 ~ 6만 유효
    {30, 28, 27, 26, 25, 30, 35, 40} // 15일때 : 1 ~ 7만 유효
};

int max(int a, int b){ return a > b ? a : b; }
void input();
void solution(int i, int sum); // idx는 주사위 결과 번호, sum은 지금까지 점수 합

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solution(0, 0);

    cout << ans << endl;

    return 0;
}

void input(){
    for (int i = 0; i < 10; i++){
        cin >> dices[i];
    }
}

bool canMove(int player_idx, int num){
    int i = players[player_idx].first, j = players[player_idx].second;
    if (i == 0){
        if ((j+num) == 5) return isSomeone[1][0] ? false : true;
        if ((j+num) == 10) return isSomeone[2][0] ? false : true;
        if ((j+num) == 15) return isSomeone[3][0] ? false : true;
    }
    if ((j+num) >= map_scores[i].size()) return true; // 가능은 함.

    return isSomeone[i][j+num] ? false : true;
}

void solution(int i, int sum){
    if (i == 10){
        ans = max(ans, sum);
        return;
    }

    for (int j = 0; j < 4; j++){ // 말 4개 0~3
        int x = players[j].first, y = players[j].second;
        if (canMove(j, dices[i])){
            isSomeone[x][y] = false;
            if (x == 0){
                if ((y+dices[i]) == 5){
                    isSomeone[1][0] = true;
                    players[j].first = 1; players[j].second = 0;
                    solution(i+1, sum+map_scores[1][0]);
                    players[j].first = x; players[j].second = y;
                    isSomeone[1][0] = false;
                }
                if ((y+dices[i]) == 10){
                    isSomeone[2][0] = true;
                    players[j].first = 2; players[j].second = 0;
                    solution(i+1, sum+map_scores[2][0]);
                    players[j].first = x; players[j].second = y;
                    isSomeone[2][0] = false;
                }
                if ((y+dices[i]) == 15){
                    isSomeone[3][0] = true;
                    players[j].first = 3; players[j].second = 0;
                    solution(i+1, sum+map_scores[3][0]);
                    players[j].first = x; players[j].second = y;
                    isSomeone[3][0] = false;
                }
            }
            else if ((y+dices[i]) >= map_scores[x].size()) solution(i+1, sum+0); // 도착
            else{
                isSomeone[x][y+dices[i]] = true;
                players[j].first = x; players[j].second = y+dices[i];
                solution(i+1, sum+map_scores[x][y+dices[i]]);
                players[j].first = x; players[j].second = y;
                isSomeone[x][y+dices[i]] = false;
            }

            isSomeone[x][y] = true;
        }
    }
}