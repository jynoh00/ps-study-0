// 컨베이어 벨트 위의 로봇
#include <iostream>
#include <stdio.h>
#include <deque>

#define endl "\n"
#define MAX 100

using namespace std;

int N, K, ans = 0;
int hp[MAX*2]; // 2N 개
deque<pair<int, bool>> belt_state; // N개
bool isFininsh = false;

void input();
void solution();


int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solution();

    return 0;
}

// 0번: 올리는 위치, N-1번: 내리는 위치
void solution(){
    while(!isFininsh){
        ans++;

        // 벨트 이동 
        belt_state.pop_back();
        int nIdx = belt_state.front().first - 1;
        if (nIdx == -1) nIdx = 2*N - 1;

        belt_state.push_front(make_pair(nIdx, 0));
        
        if (belt_state[N-1].second) belt_state[N-1].second = false; // 로봇 내림

        // 로봇 이동
        for (int i = N-2; i >= 0; i--){ // 벨트 순회 (마지막은 로봇 사라지니까 제외), 역순으로
            if (belt_state[i].second){ // 로봇 존재 
                if (!belt_state[i+1].second && hp[belt_state[i+1].first] > 0){ 
                    belt_state[i].second = false;
                    belt_state[i+1].second = true;
                    hp[belt_state[i+1].first]--;
                }
            }

            if (belt_state[N-1].second) belt_state[N-1].second = false; // 로봇 내림
        }

        // 로봇 올림
        if (hp[belt_state[0].first] > 0){
            belt_state[0].second = true;
            hp[belt_state[0].first]--;
        }

        // 내구 확인 (isFinish)
        int cnt = 0;
        for (int i = 0; i < 2*N; i++){
            if (hp[i] == 0) cnt++;
            if (cnt >= K){
                isFininsh = true;
                break;
            }
        }
    }

    cout << ans << endl;
}

void input(){
    cin >> N >> K;
    for (int i = 0; i < 2*N; i++){
        cin >> hp[i];
        if (i < N){ 
            belt_state.push_back(make_pair(i, 0));
            // i : 칸 번호, 0 : 로봇 x, 1 : 로봇 o
        }
    }
}



/*
길이 N 컨베이어 벨트 -> 큐?
2N인 벨트가 위 아래로 돎

1 2 3 4 5 . . . N
2N   . . .      N+1

i번칸의 내구도 A[i]

1: 올리는 위치
N: 내리는 위치

로봇이 내리는 위치에 도달하면 내림

로봇은 벨트 위에서 이동할 수 있음 스스로

로봇을 올리거나
로봇이 해당 칸으로 이동   =>    그 칸 내구도 -1

로봇들을 건너편으로 옮길려함


순서대로
1. 벨트가 각 칸에 있는 로봇과 함께 한 칸 전진 (+1)
2. 가장 먼저 올라간 로봇부터 회전방향으로 이동할 수 있다면 +1칸 이동, 없으면 가만
    이동 할 수 있을 조건 -> 이동하려는 칸에 로봇이 없고 그 칸 내구도가 1이상이어야함
3. 올리는 위치에 있는 칸의 내구도가 0이 아니라면 올리는 위치에 로봇을 올림
4. 내구도 0인 칸 개수가 K개 이상이면 종료 stop, else -> goto 1

종료 시 1~4 중 몇 단계가 진행 중이었나?

2 <= N <= 100
1 <= K <= 2N : 내구도 0인 개수 -> 종료 조건
A[i] 내구도 <= 1000



*/