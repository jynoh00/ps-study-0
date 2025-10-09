// 연산자 끼워넣기
// 브루트포스, 백트래킹 - 재귀함수 사용 -> 전체 사항 고려
#include <iostream>
#include <stdio.h>

#define endl "\n"

using namespace std;

int N;
int operands[11] = {0,};
int operators[4] = {0,};
int answer_min = 1000000000, answer_max = -1000000000;

void input(){
    cin >> N;
    for (int i = 0; i < N; i++) cin >> operands[i];
    for (int i = 0; i < 4; i++) cin >> operators[i];
}

void calcu(int res, int idx){
    if (idx == N){
        if (res > answer_max) answer_max = res;
        if (res < answer_min) answer_min = res;
        return;
    }

    for (int i = 0; i < 4; i++){
        if (operators[i] > 0){
            operators[i]--;
            if (i == 0) calcu(res + operands[idx], idx+1);
            else if (i == 1) calcu(res - operands[idx], idx+1);
            else if (i == 2) calcu(res * operands[idx], idx+1);
            else calcu(res / operands[idx], idx+1);
            operators[i]++;
        }
    }
}

void solution(){
    input();
    calcu(operands[0], 1);

    cout << answer_max << endl << answer_min << endl;
}

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);
    
    solution();

    return 0;
}