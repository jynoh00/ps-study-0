// 톱니바퀴

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
// int idx, d;
// bool A[BIG_NUM][SMALL_NUM];
deque<int> A[BIG_NUM];

/*

idx: 1번 2번 3번 4번 -> 0 1 2 3번 바퀴
d: 1(시계) or -1(반시계)

            0

    7               1

6                       2

    5               3
    
            4

N: 0, S: 1

6이랑 2만 중요

*/

void solution();
void input();
void calcu();

int main(){
    cin.tie(NULL); cout.tie(NULL);
    solution();
    return 0;
}

void solution(){
    input();
    calcu();

    for (int i = 0; i < 4; i++){
        ans += A[i][0] == 0 ? 0 : score_arr[i];
        if (A[i][0] == 1) cout << "점수 추가: " << score_arr[i] << endl;
    }
    cout << ans;
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
        insts[i] = make_pair(idx-1, d);
    }
}

void calcu(){
    for (int i = 0; i < K; i++){ // 총 K번 회전, 한번에 1칸 회전
        int wheel_idx = insts[i].first, direction = insts[i].second; 
        // 시계방향: pop_back한 걸 push_front
        // 반시계방향: pop_front한 걸 push_back
        //d: 1(시계) or -1(반시계)

        if (wheel_idx == 0){ // 좌측
            if (A[0][2] != A[1][6]){ // 우측 바퀴 회전
                if (direction == 1){ // 반시계 회전
                    int tmp_front = A[1][0];
                    A[1].pop_front();
                    A[1].push_back(tmp_front);
                }else{ //시계 회전
                    int tmp_back = A[1][7];
                    A[1].pop_back();
                    A[1].push_front(tmp_back);
                }
            }

            if (direction == 1){ // 시계 회전
                int tmp_back = A[0][7];
                A[0].pop_back();
                A[0].push_front(tmp_back);
            }else{ // 반시계 회전
                int tmp_front = A[0][0];
                A[0].pop_front();
                A[0].push_back(tmp_front);
            }
        }else if (wheel_idx == 3){ // 우측
            if (A[3][6] != A[2][2]){ // 좌측 바퀴 회전
                if (direction == 1){ // 반시계 회전
                    int tmp_front = A[2][0];
                    A[2].pop_front();
                    A[2].push_back(tmp_front);
                }else{ //시계 회전
                    int tmp_back = A[2][7];
                    A[2].pop_back();
                    A[2].push_front(tmp_back);
                }
            }

            if (direction == 1){ // 본인 시계 회전
                int tmp_back = A[3][7];
                A[3].pop_back();
                A[3].push_front(tmp_back);
            }else{ // 본인 반시계 회전
                int tmp_front = A[3][0];
                A[3].pop_front();
                A[3].push_back(tmp_front);
            }
        }else{ // 중간
            // 우측 바퀴 회전
            if (A[wheel_idx][2] != A[wheel_idx+1][6]){ // 우측 바퀴 회전
                if (direction == 1){ // 반시계 회전
                    int tmp_front = A[wheel_idx+1][0];
                    A[wheel_idx+1].pop_front();
                    A[wheel_idx+1].push_back(tmp_front);
                }else{ //시계 회전
                    int tmp_back = A[wheel_idx+1][7];
                    A[wheel_idx+1].pop_back();
                    A[wheel_idx+1].push_front(tmp_back);
                }
            }

            // 좌측 바퀴 회전
            if (A[wheel_idx][6] != A[wheel_idx-1][2]){ // 좌측 바퀴 회전
                if (direction == 1){ // 반시계 회전
                    int tmp_front = A[wheel_idx-1][0];
                    A[wheel_idx-1].pop_front();
                    A[wheel_idx-1].push_back(tmp_front);
                }else{ //시계 회전
                    int tmp_back = A[wheel_idx-1][7];
                    A[wheel_idx-1].pop_back();
                    A[wheel_idx-1].push_front(tmp_back);
                }
            }            

            // 본인 회전
            if (direction == 1){ // 시계 회전
                int tmp_back = A[wheel_idx][7];
                A[wheel_idx].pop_back();
                A[wheel_idx].push_front(tmp_back);
            }else{ // 반시계 회전
                int tmp_front = A[wheel_idx][0];
                A[wheel_idx].pop_front();
                A[wheel_idx].push_back(tmp_front);
            }
        }
    }
}


/*

**** 현재 기준으로 돌리는데 -> 옆에꺼가 돌아가면 그 옆옆꺼도 돌아가는거 고려해야함 ****
어케? flag로 할까?
    노가다로 가자 ->
        0일 경우
            -> 1이 돌아간다.
                -> 2 check
                    -> 3check
        1일 경우
            -> 0이 돌아간다.
            -> 2가 돌아간다.
                -> 3check
        2일 경우
            -> 1이 돌아간다.
                -> 0 check
            -> 3이 돌아간다.
        3일 경우
            -> 2가 돌아간다.
                -> 1 check
                    -> 0check


이거 재귀함수로 해야할 거 같음
    인자로 : wheel_idx랑 해당 idx가 돌아갈 방향
    함수 내부에서 양옆 wheel_idx랑 해당 idx가 돌아갈 방향 함수 재귀 호출

*/

/*

8개의 톱니를 가진 톱니바퀴 4개
톱니는 N or S 중 하나

톱니바퀴 번호 1 ~ 4번 순서대로

톱니바퀴를 총 K번 회전하려함
회전: 
    한 칸(1개의 톱니)을 기준으로
    방향: 시계, 반시계 2개 존재

회전시킬 톱니바퀴와 회전시킬 방향
서로 맞닿은 극에 따라 다른 톱니 움직일 수 있음

회전할 때 옆 톱니와 극이 다르면 옆 톱니바퀴는 반대 방향으로 회전

10101111
시계방향: pop_back한 걸 push_front
반시계방향: pop_front한 걸 push_back
    1
1       0

1       1

1       0
    1

01111101
11001110
00000010
2
3 -1
1 1

최종 점수 합
1번 톱니바퀴의 12시방향이 N극이면 0점, S극이면 1점
2번 톱니바퀴의 12시방향이 N극이면 0점, S극이면 2점
3번 톱니바퀴의 12시방향이 N극이면 0점, S극이면 4점
4번 톱니바퀴의 12시방향이 N극이면 0점, S극이면 8점

구현 시물

*/