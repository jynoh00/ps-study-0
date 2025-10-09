// 주사위 굴리기
#include <iostream>
#include <stdio.h>

#define MAX 20
#define IMAX 1000
#define endl "\n"

using namespace std;

int N, M, x_pos, y_pos, K;
int map[MAX][MAX];
int insts[IMAX];
int _top = 0, _down = 0, _right = 0, _left = 0, _bottom = 0, _up = 0;
int dx[] = {0, 0, 0, -1, 1}; // 1 ~ 4
int dy[] = {0, 1, -1, 0, 0}; // 1 ~ 4

void input();
void solution();
void dice_update(int d);

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solution();

    return 0;
}

void dice_update(int d){
    int tmp_bottom = _bottom;
    if (d == 1){ // 우측
        _bottom = _right;
        _right = _top;
        _top = _left;
        _left = tmp_bottom;
    }else if (d == 2){ // 좌측
        _bottom = _left;
        _left = _top;
        _top = _right;
        _right = tmp_bottom;

    }else if (d == 3){ // 상단
        _bottom = _up;
        _up = _top;
        _top = _down;
        _down = tmp_bottom;
    }else{ // d == 4 // 하단
        _bottom = _down;
        _down = _top;
        _top = _up;
        _up = tmp_bottom;
    }
}

void solution(){
    for (int i = 0; i < K; i++){
        int direction = insts[i];
        int nx = x_pos + dx[direction], ny = y_pos + dy[direction];

        if (nx < 0 || nx >= N || ny < 0 || ny >= M) continue;
        
        dice_update(direction);

        x_pos = nx; y_pos = ny;

        if (map[x_pos][y_pos] == 0) map[x_pos][y_pos] = _bottom;
        else{ // 0이 아니면
            _bottom = map[x_pos][y_pos];
            map[x_pos][y_pos] = 0;
        }
        cout << _top << endl;
    }
}

void input(){
    cin >> N >> M >> x_pos >> y_pos >> K;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            cin >> map[i][j];
        }
    }

    for (int i = 0; i < K; i++) cin >> insts[i];
}

/*
크기 N M 맵

    2
4   1   3
    5
    6

(r,c)

윗면 1, 방향 우측 (x,y)에서 시작

처음 주사위 모든면에 0

주사위는 윗 면이 1이고, 동쪽을 바라보는 방향이 3인 상태로 놓여져 있으며, 놓여져 있는 곳의 좌표는 (x, y) 이다. 가장 처음에 주사위에는 모든 면에 0이 적혀져 있다.
??? 윗면이 1이고 동쪽이 3이라며 ㅅㅂ

각 칸 정수

이동
    이동칸이 0이면 주사위 바닥면에 쓰여있는 수가 칸에 복사
    0이 아니면 칸에 쓰여있는 수가 주사위 바닥에 복사, 칸에 수는 0이됨.
if 맵 바깥 -> 명령 무시, 출력 x

00

    N-1,M-1

N, M, K
MAX = 20

우측: 1
좌측: 2
상단: 3
하단: 4


*/