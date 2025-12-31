#include <iostream>
#include <stdio.h>

#define endl "\n"

using namespace std;

int dices[10], ans = 0;
int h_pos[4]; // 말 포지션 (idx)
int scores[33] = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20,
    22, 24, 26, 28, 30, 32, 34, 36, 38, 40,
    13, 16, 19, // 21, 22, 23
    22, 24, // 24, 25
    28, 27, 26, // 26, 27, 28
    25, 30, 35, // 29, 30, 31
    0}; // 32
int next_arr[33];
bool isSomeone[33];

void input(){ for (int i = 0; i < 10; i++) cin >> dices[i]; }
void solution(int idx, int sum);
void init();
int max(int a, int b){ return a > b ? a : b; }
pair<int, bool> canMove(int h_idx, int dice);

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    init();
    solution(0, 0);

    cout << ans << endl;

    return 0;
}

void init(){
    for (int i = 0; i < 33; i++) next_arr[i] = i+1; // default
    next_arr[5] = 21;
    next_arr[10] = 24;
    next_arr[15] = 26;
    next_arr[20] = 32; // 마지막 칸 다음은 도착칸
    
    next_arr[23] = 29;
    next_arr[25] = 29;
    // next_arr[28] = 29; // default랑 동일

    next_arr[31] = 20;
    next_arr[32] = 32; // 32 다음은 본인 그대로 -> for반복시 점수 추가 +0이 반복되게
}

void solution(int idx, int sum){
    if (idx == 10){
        ans = max(ans, sum);
        return;
    }

    for (int i = 0; i < 4; i++){ // 4개 말 중 선택
        int orign_pos = h_pos[i];
        pair<int, bool> p = canMove(i, dices[idx]); // first-> 다음 위치 idx, second-> 이동 가능 불가능
        if (p.second || p.first == 32){ // 이동 가능
            isSomeone[orign_pos] = false; // 원래 위치 false
            h_pos[i] = p.first;
            isSomeone[p.first] = true;

            solution(idx+1, sum+scores[p.first]);
            
            isSomeone[p.first] = false;
            h_pos[i] = orign_pos;
            isSomeone[orign_pos] = true;
        }
    }
}

pair<int, bool> canMove(int h_idx, int dice){
    int tmp_pos = h_pos[h_idx]; // idx값

    if (tmp_pos == 5 || tmp_pos == 10 || tmp_pos == 15){ // 분기점 시작이면
        for (int i = 0; i < dice; i++){
            tmp_pos = next_arr[tmp_pos];
        }
    }else{
        // 5, 10, 15 idx가 아닐 때
        for (int i = 0; i < dice; i++){ // dice만큼 반복
            if (tmp_pos == 5 || tmp_pos == 10 || tmp_pos == 15){ // 최초 tmp_pos가 아닌 tmp_pos가 5, 10, 15일 때: 분기 없이 1칸 추가
                tmp_pos++;
                continue;
            }
            tmp_pos = next_arr[tmp_pos];
        }
    }    
    
    return make_pair(tmp_pos, !isSomeone[tmp_pos]); // isSomeone이 true면 false
}