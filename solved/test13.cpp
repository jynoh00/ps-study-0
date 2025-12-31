// 미세먼지 안녕!

#include <iostream>
#include <stdio.h>
#include <cstring>

#define MAX 50
#define endl "\n"

using namespace std;

int map[MAX][MAX];
int tmp_map[MAX][MAX]; // 0 초기화
int tmp_orign[MAX][MAX];
int R, C, T;
pair<int, int> cleaner[2];
int dx[] = {0, 1, 0, -1}; // 우 하 좌 상
int dy[] = {1, 0, -1, 0}; // 0 1 2 3
int ans = 0;

// 시계 : 0 1 2 3
// 반시계 : 0 3 2 1

void input();
void solution();
void diffusion();
void purification();
void display_arr();

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solution();

    return 0;
}

void input(){
    bool cleanerCheck = false;
    cin >> R >> C >> T;
    for (int i = 0; i < R; i++){
        for (int j = 0; j < C; j++){
            cin >> map[i][j];
            if (map[i][j] == -1 && cleanerCheck == false){
                cleaner[0] = make_pair(i, 0);
                cleaner[1] = make_pair(i+1, 0);

                cleanerCheck = true;
            }
        }
    }
}

void solution(){
    for (int i = 0; i < T; i++){ // 시간 : 시행 횟수
        diffusion();
        purification();
    }

    for (int i = 0; i < R; i++){
        for (int j = 0; j < C; j++){
            if (map[i][j] > 0) ans += map[i][j];
        }
    }

    cout << ans << endl;
}

void diffusion(){
    memset(tmp_map, 0, sizeof(tmp_map)); // 0 초기화 (마지막에 해당 칸 값 만큼 변동)
    memset(tmp_orign, 0, sizeof(tmp_orign));
    // 최종 : map = tmp_map + tmp_orign;
    tmp_map[cleaner[0].first][0] = -1;
    tmp_map[cleaner[1].first][0] = -1;

    for (int i = 0; i < R; i++){
        for (int j = 0; j < C; j++){
            if (map[i][j] > 0){ // 미세먼지 있는 칸.
                int cnt = 0;

                for (int k = 0; k < 4; k++){ // 상하좌우
                    int nx = i + dx[k], ny = j + dy[k];
                    
                    if (nx >= 0 && ny >= 0 && nx < R && ny < C){ // map안
                        if (nx == cleaner[0].first && ny == 0) continue; // 청정기 위치일 경우: 패스
                        if (nx == cleaner[1].first && ny == 0) continue;

                        tmp_map[nx][ny] += map[i][j]/5; // 소수점버림
                        cnt++;
                    }
                }
                tmp_orign[i][j] = map[i][j] - (map[i][j]/5)*cnt;
            }
        }
    }

    for (int i = 0; i < R; i++){
        for (int j = 0; j < C; j++){
            map[i][j] = tmp_orign[i][j] + tmp_map[i][j];
        }
    }
}

void purification(){
    // 2중for문으로 미세먼지 있는 곳 전체 점검 개별 이동
    memset(tmp_map, 0, sizeof(tmp_map)); // 새로운 맵

    tmp_map[cleaner[0].first][0] = -1;
    tmp_map[cleaner[1].first][0] = -1;

    for (int i = 0; i < R; i++){
        for (int j = 0; j < C; j++){
            if (i <= cleaner[0].first){ // 반시계방향 회전
                if (i == 0 && j > 0){ // 상단 : 좌측 이동
                    int nx = i + dx[2], ny = j + dy[2];
                    tmp_map[nx][ny] = map[i][j];

                }else if (i < cleaner[0].first && j == 0){ // 좌변 : 하단 이동
                    int nx = i + dx[1], ny = j + dy[1];
                    if (nx == cleaner[0].first) continue; // 공기청정기 부분
                    
                    tmp_map[nx][ny] = map[i][j];
                    
                }else if (i == cleaner[0].first && j > 0 && j < C-1){ // 하단 : 우측 이동
                    int nx = i + dx[0], ny = j + dy[0];
                    tmp_map[nx][ny] = map[i][j];
                    
                }else if (i > 0 && j == C-1){ // 우변 : 상단 이동
                    int nx = i + dx[3], ny = j + dy[3];
                    tmp_map[nx][ny] = map[i][j];
                }else tmp_map[i][j] = map[i][j]; // 중간
            }else{ // 시계방향 회전
                if (i == cleaner[1].first && j > 0 && j < C-1){ // 상단 : 우측 이동
                    int nx = i + dx[0], ny = j + dy[0];
                    tmp_map[nx][ny] = map[i][j];

                }else if (i < R-1 && j == C-1){ // 우변 : 하단 이동
                    int nx = i + dx[1], ny = j + dy[1];
                    tmp_map[nx][ny] = map[i][j];

                }else if (i == R-1 && j > 0){ // 하단 : 좌측 이동
                    int nx = i + dx[2], ny = j + dy[2];
                    tmp_map[nx][ny] = map[i][j];

                }else if (i > cleaner[1].first && j == 0){ // 좌변 : 상단 이동
                    int nx = i + dx[3], ny = j + dy[3];
                    if (nx == cleaner[1].first) continue;

                    tmp_map[nx][ny] = map[i][j];
                }else tmp_map[i][j] = map[i][j];
            }
        }
    }

    for (int i = 0; i < R; i++){
        for (int j = 0; j < C; j++){
            map[i][j] = tmp_map[i][j];
        }
    }
}