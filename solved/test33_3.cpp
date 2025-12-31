#include <iostream>
#include <stdio.h>
#include <vector>

#define endl "\n"

using namespace std;

int dices[10], ans = 0;
int scores[33] = {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20,
    22, 24, 26, 28, 30, 32, 34, 36, 38, 40,
    13, 16, 19, 22, 24, 28, 27, 26, 25, 30, 35, 0}; // 0: 시작점, 32: 도착점
int nxt[33]; // 다음 위치
int pos[4]; // 말 위치: idx

int max(int a, int b){ return a > b ? a: b; }
void input();
void solution(int idx, int sum);

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solution(0, 0);

    return 0;
}

void input(){
    for (int i = 0; i <= 19; i++) nxt[i] = i+1;
    nxt[20] = 32;

    nxt[5] = 21;
    nxt[10] = 24;
    nxt[15] = 26;

    nxt[21] = 22; nxt[22] = 23; nxt[23] = 29;
    nxt[24] = 25; nxt[25] = 29;
    nxt[26] = 27; nxt[27] = 28; nxt[28] = 29;
    nxt[29] = 30; nxt[30] = 31; nxt[31] = 20;
    nxt[32] = 32; // 도착

    for (int i = 0; i < 10; i++) cin >> dices[i];
}

int move(int start, int dice){ // 1 , 5라하면 6이 되어야함.
    int cur = start; // 1
    bool isLast = false;
    for (int i = 0; i < dice; i++){ // i = 0 1 2 3 4
        if ()
        cur = nxt[cur]; // cur = nxt[1] -> cur = 2 | cur = nxt[2] -> cur = 3 | cur = nxt[3] -> cur = 4 | cur = nxt[4] -> cur = 5 | cur = nxt[5] -> cur = 21
        if (cur == 32) break;
    }
    return cur; // 26이 리턴됨
}

void solution(int idx, int sum){
    if (idx == 10){
        ans = max(ans, sum);
        return;
    }

    int dice = dices[idx];

    for (int k = 0; k < 4; k++){
        int cur = pos[k]; // 현재 말 위치
        if (cur == 32) continue;
        
        int next_pos = move(cur, dice);
    }
}