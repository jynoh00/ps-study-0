// 연구소

#include <iostream>
#include <stdio.h>
#include <queue>
#include <cstring>
#include <vector>

#define MAX 8
#define endl "\n"

using namespace std;

int N, M, zero_cnt = 0;
int map[MAX][MAX]; // 00 ~ (N-1, M-1)
bool isVisited[MAX][MAX];
vector<pair<int ,int>> v; // 0의 좌표들
vector<pair<int, int>> v_two; // 바이러스 위치 좌표들

int dx[] = {-1, 0, 1, 0}; // 상 -> 우 -> 하 -> 좌
int dy[] = {0, 1, 0, -1}; // 0    1     2     3
int max_ans = -99999999;

int output_max(int a, int b){ return a > b ? a : b; }
void input();
void solution();
int bfs(int a, int b);
void select_map(int idx, int select_cnt);

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solution();

    return 0;
}

void input(){
    cin >> N >> M;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            cin >> map[i][j];
            if (map[i][j] == 0){
                zero_cnt++;
                v.emplace_back(make_pair(i, j)); // 0 좌표 추가
            }
            if (map[i][j] == 2) v_two.emplace_back(make_pair(i, j));
        }
    }
}

int bfs(int a, int b){ // a,b에서 주변으로 전이 가능한 칸의 개수 (0 <= return)
    // 여기에 memset()하면 이미 전이된 0번이 여러번 카운트될 수 있음.
    queue<pair<int, int>> q;
    q.push(make_pair(a, b));
    isVisited[a][b] = true;
    int cnt = 0;

    while(!q.empty()){
        int x_pos = q.front().first, y_pos = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++){
            int nx = x_pos + dx[i]; 
            int ny = y_pos + dy[i]; // 위치 이동
            
            if (nx >= 0 && ny >= 0 && nx < N && ny < M){ // 범위 안
                if (map[nx][ny] == 0 && isVisited[nx][ny] == false){ // 전이 가능 칸, 방문 x 칸
                    isVisited[nx][ny] = true;
                    cnt++;
                    q.push(make_pair(nx, ny));
                }
            }
        }
    }

    return cnt;
}

void select_map(int idx, int select_cnt){
    if (select_cnt == 3){
        memset(isVisited, false, sizeof(isVisited)); // false 초기화 <- bfs 내부 초기화 하면 안됐음.
        int danger_cnt = 0;

        for (int i = 0; i < v_two.size(); i++){
            danger_cnt += bfs(v_two[i].first, v_two[i].second);
        }

        max_ans = output_max(max_ans, zero_cnt-danger_cnt-3);
        return;
    }

    for (int i = idx; i < zero_cnt; i++){ // 0들 순회
        int tmp_x = v[i].first, tmp_y = v[i].second; // 벽 설치할 좌표로 선택
        map[tmp_x][tmp_y] = 1; // 벽으로 설정
        
        select_map(i+1, select_cnt+1); // 숫자 1 늘려서 재귀 호출

        //선택x
        map[tmp_x][tmp_y] = 0;
    }
}

void solution(){
    select_map(0, 0);

    cout << max_ans << endl;
}


/*
20:25

N*M 맵 바이러스 막기 위해 벽을 쳐야 함

빈칸, 벽, 바이러스

바이러스는 상하좌우로 퍼질 수 있음

세로 새울 벽은 only 3개


(0빈칸, 1벽, 2바이러스)
2 0 0 0 1 1 0
0 0 1 0 1 2 0
0 1 1 0 1 0 0
0 1 0 0 0 0 0
0 0 0 0 0 1 1
0 1 0 0 0 0 0
0 1 0 0 0 0 0


(2,1) (1,2) (4,6)
2 1 0 0 1 1 0
1 0 1 0 1 2 0
0 1 1 0 1 0 0
0 1 0 0 0 1 0
0 0 0 0 0 1 1
0 1 0 0 0 0 0
0 1 0 0 0 0 0

x 1 0 0 1 1 x
1 0 1 0 1 x x
0 1 1 0 1 x x
0 1 0 0 0 1 x
0 0 0 0 0 1 1
0 1 0 0 0 0 0
0 1 0 0 0 0 0

벽 3개 세우고 안전영역 생성

-> 안전영역 크기 27 (0의 개수)

지도가 주어질 때 안전 영역 최대 크기 구하기

BFS 구현 시뮬 그래프 문제


바이러스 차단 경우
    1. 상하좌우 모두 벽으로
    2. 공간 조금 주고 벽으로

0인 곳 중에서 1을 3개 선택해야함.

3 ~ 8임 크기는
3*3 ~ 8*8 인데

즉 0의 수는 64보다 작음

0의개수 C 3 전체 조사
각 경우마다 2기준으로 BFS -> 안전구역 조사

안전구역 최댓값 출력


7 7
2 0 0 0 1 1 0
0 0 1 0 1 2 0
0 1 1 0 1 0 0
0 1 0 0 0 0 0
0 0 0 0 0 1 1
0 1 0 0 0 0 0
0 1 0 0 0 0 0


*/


