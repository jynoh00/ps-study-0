// 주사위 굴리기 2
// 구현, 시뮬, 그래프, BFS
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <queue>

#define MAP_MAX 21
#define endl "\n"

using namespace std;

int N, M, K, score = 0;
int map[MAP_MAX][MAP_MAX]; // 1,1 ~ N,M 까지만 고려
int x_pos = 1, y_pos = 1;
int _top = 1; // 윗면
int _left = 4;
int _right = 3;
int _up = 2;
int _down = 5;
bool isVisited[MAP_MAX][MAP_MAX];

int direction = 0;
int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

void solution();
void input();
void calcu();
void move_dice();
void stat_update();
void bfs(int a, int b);


int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    solution();

    return 0;
}

void solution(){
    input();
    for (int i = 0; i < K; i++){
        calcu();
    }

    cout << score << endl;
}

void input(){
    cin >> N >> M >> K;
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= M; j++){
            cin >> map[i][j];
        }
    }
}

void bfs(int a, int b){ // 완전탐색 - 너비우선탐색 : 일치하는 노드 카운트
    memset(isVisited, false, sizeof(isVisited));

    int num = map[a][b];
    int cnt = 0;

    queue<pair<int, int>> q;
    q.push(make_pair(a, b));
    isVisited[a][b] = true;

    while(!q.empty()){ // 큐에 원소가 존재하면 반복
        int x = q.front().first;
        int y = q.front().second;
        q.pop();
        cnt++;

        for (int i = 0; i < 4; i++){ // x, y에서 상하좌우
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (nx > 0 && ny > 0 && nx <= N && ny <= M){ // 범위 안
                if (map[nx][ny] == num && isVisited[nx][ny] == false){ // 같은 숫자, 방문한 적 x
                    q.push(make_pair(nx, ny));
                    isVisited[nx][ny] = true;
                }
            }
        }
    }
    score += cnt * num;
}

void stat_update(){
    if (direction == 0){ // 우측
        int top_tmp = _top;

        _top = 7 - _right;
        _left = 7 - top_tmp; // 바텀이 레프트로
        _right = top_tmp; // 탑이 라이트로

    }else if (direction == 2){ // 좌측
        int top_tmp = _top;

        _top = 7 - _left;
        _right = 7 - top_tmp;
        _left = top_tmp;

    }else if (direction == 3){ // 상단
        int top_tmp = _top;

        _top = 7 - _up;
        _down = 7 - top_tmp;
        _up = top_tmp;

    }else{ // 하단 1
        int top_tmp = _top;

        _top = 7 - _down;
        _up = 7 - top_tmp;
        _down = top_tmp;
    }
}

void move_dice(){ // direction 벽 생각 적용된 상태, 이동 + 점수 계산
    x_pos += dx[direction]; y_pos += dy[direction];
    stat_update();

    int A = 7 - _top; // 아랫면
    int B = map[x_pos][y_pos];

    if (A > B) direction = (direction+1) == 4 ? 0 : direction+1; // 시계
    else if (A < B) direction = (direction-1) == -1 ? 3 : direction-1; // 반시계

    bfs(x_pos, y_pos);
}

void calcu(){
    // 이동할 칸
    int tmp_x = x_pos + dx[direction], tmp_y = y_pos + dy[direction];
    
    if (tmp_x > N || tmp_x < 1 || tmp_y > M || tmp_y < 1){ // 맵 범위 밖
        direction = (direction+2)%4; // 반대 전환 (반대도 막힌 경우는 없음. 2<= N,M )
    }

    move_dice();
}

/*

크기 N*M인 지도 존재
좌표 r,c

1,1

      N,M

주사위 1~6
전개도

  2
4 1 3
  5
  6

왼쪽 이동
  2
1 3 6
  5
  4

오른쪽 이동
  2
6 4 1
  5
  3





윗면 1, 우측을 바라보는 방향이 3인 상태 시작 (아랫면은 6), 좌표는 1,1

지도 각 칸에 정수 있음

첫 주사위 이동 방향은 우측

이동 한 번
    1. 이동 방향으로 1칸 이동, 칸이 없다면 반대 방향으로 1칸 이동
    2. 도착한 칸 x,y에 있는 점수를 더함
    3. 주사위 아랫면 정수 A와 x,y칸에 있는 정수 B 비교
        A > B: 이동 방향을 90도 시계 방향 회전 (우측)
        A < B: 90도 반시계 방향 회전 (좌측) 
        A = B: 이동 방향 그대로

x,y에 있는 정수 B라 할 때 상하좌우 이동 가능한 칸의 개수(맵 안쪽)(근데 B랑 같아야함) C
    얻는 점수 = B*C

4 5 1
4 1 2 3 3
6 1 1 3 3
5 6 1 3 2
5 5 6 5 5

재귀 필요 x -> 단순 구현 느낌

4 5 1
4 1 2 3 3
6 1 1 3 3
5 6 1 3 2
5 5 6 5 5


*/