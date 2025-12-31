// 로봇 청소기

#include <iostream>
#include <stdio.h>

#define endl "\n"
#define MAX 50

using namespace std;

int N, M, r, c, d; // d (0: 상, 1: 우, 2: 하, 3: 좌)
int ans = 0;
int map[MAX][MAX]; // 1: 벽, 0: 청소x, 2: 청소o
bool flag = true;
int dx[] = {-1, 0, 1, 0}; 
int dy[] = {0, 1, 0, -1}; // 0: 상, 1: 우, 2: 하, 3: 좌 이동
int bx[] = {1, 0, -1, 0};
int by[] = {0, -1, 0, 1}; // 뒤로 이동

int check_num = 7;

void input(){
    cin >> N >> M;
    cin >> r >> c >> d;

    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            cin >> map[i][j];
        }
    }
}

bool machine_run(){
    check_num++;
    if (map[r][c] == 0){
        map[r][c] = 2;
        ans++;

        // cout << "청소완료(" << r << "," << c << ")" << endl;

        return true;
    }

    for (int i = 0; i < 4; i++){ // 4번 방향 전환
        // d: {-1 -2 -3 -4}  {0 -1 -2 -3} {1 0 -1 -2} {2 1 0 -1}
        // d:   3  2  1  0    0  3  2  1   1 0  3  2   2 1 0  3 , 음수면 +4 음수 아니면 그대로
        if (d == 0) d = 3;
        else d--;

        // cout << "바뀐 d: " << d << endl;

        if (r+dx[d] >= 0 && r+dx[d] < N && c+dy[d] >= 0 && c+dy[d] < M){
            if (map[r+dx[d]][c+dy[d]] == 0){ // 청소해야할 곳
                r = r + dx[d];
                c = c + dy[d];

                return true;
            }
        }else continue;
    }

    // 근처 없음 청소할 곳
    if (((r+bx[d]) >= 0) && ((r+bx[d]) < N) && ((c+by[d]) >= 0) && ((c+by[d]) < M)){ // 맵 내부
        if (map[r+bx[d]][c+by[d]] == 1) return false; // 후진할 곳이 벽일 경우

        r = r + bx[d];
        c = c + by[d];

        return true;
    }

    // 후진했는데 맵 외부
    return false;
}

void calcu(){
    while(flag){
        flag = machine_run();
    }
}

void solution(){
    input();
    calcu();

    cout << ans << endl;
}

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    fill(map[0], map[MAX], 1); // 벽으로

    solution();

    return 0;
}

/*
로봇청소기, 방의 상태가 주어짐 -> 청소하는 영역의 개수 출력

방 (N*M)
    각 칸은 벽 or 빈칸
    칸 좌표 (r, c)
    좌상단 (0, 0)
    우하단 (N-1, M-1)
    빈칸은 청소되지 않은 상태

청소기
    바라보는 방향 존재
    이동방향은 상하좌우

청소기 동작
    1. 현재 칸 청소 x 상태 -> 청소한다
    2. 현재 칸 주변 4칸 중 청소되지 않은 빈칸 x -> 
         바라보는 방향 유지 상태로 후진할 수 있을 경우 후진 이후 1번으로
         후진 불가 (벽) -> 정지 (종료)
    3. 현재 칸 주변 4칸 청소되지 않은 빈칸 존재 ->
         반시계 방향 90도 회전 (왼쪽으로 회전)
         바라보는 앞칸이 청소되지 않은 경우 -> 전진
         1번으로


청소기가 청소하는 칸의 개수

그래프 - 노드, 구현 문제?   => ㅇㅇ 맞음 구현, 시뮬레이션 문제였음.

3 <= N, M <= 50
좌표 (r,c), 바라보는 방향 d (0: 상, 1: 우, 2: 하, 3: 좌)

3 3 // N M
1 1 0 // 청소기 좌표, 방향
1 1 1
1 0 1
1 1 1
-> 1: 벽, 0: 청소되지않은 상태


3 3
1 1 0
1 0 0
1 0 1
1 0 1

*/