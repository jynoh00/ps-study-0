// 톱니바퀴
// 구현 - 시뮬, 재귀사용
#include <iostream>
#include <stdio.h>
#include <deque>

#define endl "\n"
#define BIG_NUM 4
#define MAX 100

using namespace std;

int K, ans = 0;
pair<int, int> insts[MAX];
int score_arr[4] = {1, 2, 4, 8};
deque<int> A[BIG_NUM];
bool isFinish[4];

void solution();
void input();
void calcu(int wheel_idx, int direction);

int main(){
    cin.tie(NULL); cout.tie(NULL);
    solution();
    return 0;
}

void solution(){
    input();
    for (int i = 0; i < K; i++){
        for (int j = 0; j < 4; j++){
            isFinish[j] = 0; // 초기화
        }
        calcu(insts[i].first, insts[i].second);
    }

    for (int i = 0; i < 4; i++) ans += A[i][0] == 0 ? 0 : score_arr[i];
    cout << ans << endl;
}

void input(){
    for (int i = 0; i < 4; i++){ // 톱니바퀴 4개
        string s;
        cin >> s;

        deque<int> tmp_d;
        for (int j = 0; j < s.size(); j++){
            int tmp;
            tmp = s[j] - '0';
            tmp_d.push_back(tmp);
        }
        A[i] = tmp_d;
    }

    cin >> K;
    for (int i = 0; i < K; i++){
        int idx, d;
        cin >> idx >> d;
        insts[i] = make_pair(idx-1, d); // idx-1로 0, 1, 2, 3으로 wheel_idx
    }
}

void calcu(int wheel_idx, int direction){
    bool left_change = false, right_change = false;

    if ((wheel_idx-1) >= 0 && A[wheel_idx][6] != A[wheel_idx-1][2] && !isFinish[wheel_idx-1]){ // 좌측이 존재하고, 같은 극이 아니고, 처음 돌아가는 경우
        left_change = true;
    }

    if ((wheel_idx+1) < 4 && A[wheel_idx][2] != A[wheel_idx+1][6] && !isFinish[wheel_idx+1]){ // 우측이 존재하고, 같은 극이 아니고, 처음 돌아가는 경우
        right_change = true;
    }

    // 본인 change
    if (direction == 1){ // 시계 회전
        int tmp_back = A[wheel_idx][7];
        A[wheel_idx].pop_back();
        A[wheel_idx].push_front(tmp_back);
    }else{
        int tmp_front = A[wheel_idx][0];
        A[wheel_idx].pop_front();
        A[wheel_idx].push_back(tmp_front);
    }
    isFinish[wheel_idx] = 1;

    if (left_change) calcu(wheel_idx-1, direction*(-1));
    if (right_change) calcu(wheel_idx+1, direction*(-1));

    return;
}

/*

10001011
10000011
01011011
00111101

(ㄱ) 1번
휠 아이디: 0 디렉션: 1
isFinish값: 0 0 0 0 
-> 첫 시작 1,1이 들어왔기에 0번 휠이고 isFinish 정상 -> 정상

(ㄴ)
휠 아이디: 1 디렉션: -1
isFinish값: 1 0 0 0 
-> (ㄱ)에서 실행된 우측 함수, 좌측은 isFinish이고 우측을 돌려야함 isFinish 정상 -> 정상

(ㄷ)
휠 아이디: 2 디렉션: 1
isFinish값: 1 1 0 0 
-> (ㄴ)에서 실행된 우측 함수, 좌측은 isFinish이고 우측은 같은 극이라 돌리면 안됨 isFinish 정상 -> 정상

(ㄹ) 2번
휠 아이디: 1 디렉션: 1
isFinish값: 0 0 0 0 
-> 첫 시작, 2,1이 들어왔기에 1번 휠이고 isFinish 정상, 좌-우 다 돌려야함 -> 정상

(ㅁ)
휠 아이디: 2 디렉션: 1
isFinish값: 0 0 0 0 
-> 2번의 재귀가 아니라 3번 명령어가 실행된 듯, 이상함 0, -1이 실행되어야 함 isFinish도 안되어 있음.

휠 아이디: 3 디렉션: -1
isFinish값: 0 0 1 0 

휠 아이디: 3 디렉션: 1
isFinish값: 0 0 0 0 

휠 아이디: 2 디렉션: -1
isFinish값: 0 0 0 1 

휠 아이디: 1 디렉션: 1
isFinish값: 0 0 1 1 

휠 아이디: 0 디렉션: -1
isFinish값: 0 0 0 0 


*/