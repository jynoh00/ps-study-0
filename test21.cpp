// 뱀
#include <iostream>
#include <stdio.h>
#include <deque>
#include <cstring>

#define endl "\n"
#define MAX 100

using namespace std;

int N, K, L;
int map[MAX][MAX];
bool isSnake[MAX][MAX];
deque<pair<int, int>> dir_q;
deque<pair<int, int>> snake_body; // push -> 머리, pop -> 꼬리
int dx[] = {0, -1, 0, 1}; // 우 -> 상 -> 좌 -> 하 : 0 1 2 3
int dy[] = {1, 0, -1, 0}; // L => +1, R => -1
int x_pos = 0, y_pos = 0, dir = 0;
int sec = 0;

void input(); void solution();
void change_direction();

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solution();

    return 0;
}

void input(){
    cin >> N >> K; // N 맵크기, K 사과개수
    for (int i = 0; i < K; i++){
        int tmp_x, tmp_y;
        cin >> tmp_x >> tmp_y;
        map[tmp_x-1][tmp_y-1] = 1; // 사과 1, 빈공간 0, 뱀 6
    }

    cin >> L; // 방향 전환 횟수
    for (int i = 0; i < L; i++){
        int X; char C; // X초 뒤에 왼쪽(C==L), 오른쪽(C==D)으로 90도 방향 회전
        cin >> X >> C;
        if (C == 'L') dir_q.push_back(make_pair(X, 1));
        else dir_q.push_back(make_pair(X, -1)); // C == 'D'
    }
}

void change_direction(){
    if (dir_q.front().first == sec){ // 시간 동일
        int cd = dir_q.front().second;
        dir_q.pop_front();
        
        dir += cd;
        if (dir == 4) dir = 0;
        if (dir == -1) dir = 3;
    }
}

void snake_update(){
    memset(isSnake, false, sizeof(isSnake));
    for (int i = 0; i < snake_body.size(); i++){
        isSnake[snake_body[i].first][snake_body[i].second] = true; // deque은 인덱싱 가능
    }
}

void solution(){
    isSnake[0][0] = true;
    snake_body.push_back(make_pair(0,0));

    while(true){ // 반복마다 1초
        sec++;
        int nx = x_pos + dx[dir], ny = y_pos + dy[dir];
        if (nx >= 0 && ny >= 0 && nx < N && ny < N){ // map[][] 내부
            if (map[nx][ny] == 1){ // 사과    
                snake_body.push_back(make_pair(nx, ny));
                map[nx][ny] = 0;

                x_pos = nx; y_pos = ny;
            }else if (isSnake[nx][ny]) break; // 뱀
            else{ // 빈공간
                snake_body.push_back(make_pair(nx, ny));
                snake_body.pop_front(); // 선입선출, 꼬리 삭제

                x_pos = nx; y_pos = ny;
            }
        }else break; // 벽

        snake_update();
        change_direction();
    }

    cout << sec << endl;
}

/*
Dummy game

뱀
    1. 사과를 먹으면 -> 길이 증가
    2. 본인몸 or 벽과 부딪히면 return

맵 N*N 크기 (0,0 ~ N-1,N-1)

시작 뱀 길이 1, 좌표 0,0, 첫 방향 동


1초마다
    머리를 다음칸에 위치
    벽이나 자신 몸과 부딪히면 종료
    이동칸에 사과 -> 사과없어지고, 꼬리는 이동하지않음
    사과x -> 꼬리도 이동

사과의 위치와 뱀 이동경로 -> 몇 초에 끝나는 지



*/