#include <iostream>

#define MAX 510
#define endl "\n"

using namespace std;

int N, ans = 0;
int map[MAX][MAX];

int dx[] = {0, 0, 1, -1}; // 우 좌 하 상
int dy[] = {1, -1, 0, 0}; // 동 서 남 북

// 1 1 7 7 10 10 2 2 5
int xdx[4][10] = {{-1, 1, -1, 1, -1, 1, -2, 2, 0, 0}, {-1, 1, -1, 1, -1, 1, -2, 2, 0, 0}, {0, 0, 1, 1, 2, 2, 1, 1, 3, 2}, {0, 0, -1, -1, -2, -2, -1, -1, -3, -2}}; // 동 서 남 북
int ydy[4][10] = {{0, 0, 1, 1, 2, 2, 1, 1, 3, 2}, {0, 0, -1, -1, -2, -2, -1, -1, -3, -2}, {-1, 1, -1, 1, -1, 1, -2, 2, 0, 0}, {-1, 1, -1, 1, -1, 1, -2, 2, 0, 0}};
int percent[9] = {1, 1, 7, 7, 10, 10, 2, 2, 5}; // 나머지는 알파

void input();
void solution();
void spread_sand(int x, int y, int d);
int change_direction(int d);

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solution();

    cout << ans << endl;

    return 0;
}

void input(){
    cin >> N;
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= N; j++){
            cin >> map[i][j];
        }
    }
}

void solution(){
    int x_pos = (N+1)/2;
    int y_pos = (N+1)/2;
    int direction = 1;
    int move_cnt = 1;

    while(true){
        for (int i = 0; i < 2; i++){
            for (int j = 0; j < move_cnt; j++){
                spread_sand(x_pos, y_pos, direction);
                x_pos += dx[direction];
                y_pos += dy[direction];
            }
            direction = change_direction(direction);
        }

        move_cnt++;
        if (move_cnt == N){ // 마지막 1번
            for (int j = 0; j < move_cnt; j++){
                spread_sand(x_pos, y_pos, direction);
                x_pos += dx[direction];
                y_pos += dy[direction];
            }
            break; // while 종료
        }
    }
}

void spread_sand(int x, int y, int d){
    int nx = x + dx[d];
    int ny = y + dy[d];
    if (map[nx][ny] == 0) return; // 모래없는 칸일 경우 스킵

    int sand = map[nx][ny];
    int tmp = sand;

    for (int i = 0; i < 9; i++){
        int xx = x + xdx[d][i];
        int yy = y + ydy[d][i];
        int per = percent[i];
        int plus = (tmp*per) / 100;

        if (xx < 1 || yy < 1 || xx > N || yy > N) ans += plus;
        else map[xx][yy] += plus;

        sand -= plus;
    }
    int alpha_x = x + xdx[d][9]; // alpha_x
    int alpha_y = y + ydy[d][9]; // alpha_y

    if (alpha_x < 1 || alpha_y < 1 || alpha_x > N || alpha_y > N) ans += sand;
    else map[alpha_x][alpha_y] += sand;

    map[nx][ny] = 0;
}

int change_direction(int d){
    if (d == 0) return 3; // 동 -> 북
    if (d == 1) return 2; // 서 -> 남
    if (d == 2) return 0; // 남 -> 동
    if (d == 3) return 1; // 북 -> 서
    else return 16;
}

/*

if N = 7

7*7

(4,4)에서 토네이도 시작. (중앙 모래값 = 0)

토네이도를 배움

N*N 맵에서 연습

A[r][c]는 모래의 양

토네이도 시전 -> 가운데 칸부터 토네이도 이동 시작

한번에 한 칸 이동

N 홀수

토네이동 4가지 좌 하 우 상

맵 밖으로 나간 모래의 양
*/