// 주사위 윷놀이
#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

int dices[10];
pair<int, int> players[4]; // idx: 0, 1, 2, 3 말 번호 , i, j 위치 정보.

vector<vector<int>> map_scores = { // i: 0, 1, 2, 3
    {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32, 34, 36, 38, 40}, // 0 ~ 20
    {0, 13, 16, 19, 25, 30, 35, 40}, // 5일때 -> idx 1
    {0, 22, 24, 25, 30, 35, 40}, // 10일때 -> idx 2
    {0, 28, 27, 26, 25, 30, 35, 40} // 15일때 -> idx 3
};
vector<vector<bool>> map_someone = {
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0}, 
    {0, 0, 0, 0, 0, 0, 0, 0} 
};

int ans = -16;

int max(int a, int b){ return a > b ? a : b; }
void input();
void solution();

int main(){
    cin.tie(NULL); cout.tie(NULL);

    input();
    solution();

    return 0;
}

void input(){
    for (int i = 0; i < 10; i++) cin >> dices[i];
}

bool canMove(int player_idx, int num){
    int i_idx = players[player_idx].first;
    int j_idx = players[player_idx].second;

    if ((j_idx + num) >= map_scores[i_idx].size()) return true; // 가능은 해
    if (map_someone[i_idx][j_idx+num]) return false; // 누가 있어

    return true;
}

int score_plus(int player_idx, int num){ // 임시로 점수가 얼마나 추가되는 지 확인용이기에, 실제 위치 바꾸거나 bool 배열 수정 x
    if (player_idx == 5){ // 13 16 19 25 30 (1~5)


        return NULL;
    }

    if (player_idx == 10){
        return NULL;
    }

    if (player_idx == 15){

        return NULL;
    }

    // 외곽
    if (1 <= player_idx && player_idx <= 20){ // 1~20 사이
        if (players[player_idx] + num > 20){
            return 0; // 도착. -> 점수 + 0
        }
        
        return map_scores[players[player_idx]+num];
    }
}

void solution(){

    for (int i = 0; i < 10; i++){
        int dice_num = dices[i];

        vector<int> tmp_score = {-1, -1, -1, -1}; // -1 => 못 움직임, 0 => 도착, 양수 => 움직이고 점수 추가
        for (int j = 0; j < 4; j++){ // 플레이어 idx
            if(canMove(j, dice_num)){ // 이동 가능.
                tmp_score[j] = score_plus(j, dice_num);
            }
        }
        // 전부 못 움직일 수가 있나?
        int tmp_top = -1, tmp_who_idx = -1;
        for (int k = 0; k < 4; k++){
            if (tmp_score[k] == -1) continue;

            if (tmp_top < tmp_score[k]) // 둘 다 똑같으면 어떡해 ㅅㅂㅅ ㅅㅂㅅㅂ
        }
    }
}

/*

시작칸 말 4개

bool isMoving
이동 중이거나, 파란칸 아닌 곳 시작이면 빨간 화살표
도착 칸 이동하면 주사위 수와 상관없이 이동 종료

10개의 턴

턴마다 1~5 숫자 적힌 주사위 돌림
도착칸에 있지 않은 말 1개를 골라 -> 나온 수 만큼 이동

말이 이동을 한 후 도착할 곳에 말이 있으면, 이동할 수 없다. -> 그 말을 고를 수 없다 but. 도착칸에 다른 말이 있는건 가능

이동 끝날 때 마다 칸 숫자가 점수에 추가

주사위 10개 정보를 미리 알 때, 얻을 수 있는 최대 점수 값

1 2 3 4 1 2 3 4 1 2


그리디?

움직일 수 있는 애들 중, 가장 최고점을 받을 수 있는 말을 움직이게


주사위 10개 정보니까

//종료조건
{
    ans = max(ans, sum)
}

for (int i = idx; i < 10; i++){
    for (int j = 0; j < 4; j++){
        // 재귀호출()
    }
}
재귀호출로 전체 경우의 수 확인

*/