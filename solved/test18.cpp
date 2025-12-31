// 아기 상어

#include <iostream>
#include <stdio.h>
#include <queue>
#include <cstring>

#define endl "\n"
#define MAX 20

using namespace std;

int N, ans = 0;
int map[MAX][MAX];
int costs[MAX][MAX];
bool isVisited[MAX][MAX];
int x_pos, y_pos, shark_size = 2;
int fish_cnt = 0;
int eat_cnt = 0;

int dx[] = {-1, 0, 1, 0}; // 상 -> 우 -> 하 -> 좌
int dy[] = {0, 1, 0, -1};

void input();
void solution();
vector<pair<int, int>> bfs();
void eat_fish();

int main(){
    cin.tie(NULL); cout.tie(NULL);

    input();
    solution();

    cout << ans << endl;

    return 0;
}

void input(){
    cin >> N;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cin >> map[i][j];
            if (map[i][j] == 9){
                x_pos = i;
                y_pos = j;
                map[i][j] = 0;

                continue;
            }
            if (map[i][j] != 0) fish_cnt++;
        }
    }
}

void eat_fish(){
    eat_cnt++;
    if (eat_cnt == shark_size){
        eat_cnt = 0; // 이거 맞겠지?
        shark_size++;
    }
    map[x_pos][y_pos] = 0; // 먹은 곳은 0으로
    fish_cnt--;
}

void solution(){
    while(true){
        if (fish_cnt == 0) break;

        vector<pair<int, int>> can_Move = bfs();
        
        // 먹을 수 있는 물고기가 없을 경우 종료
        bool isFinish = true;
        for (pair<int, int> p : can_Move){
            if (map[p.first][p.second] != 0 && map[p.first][p.second] < shark_size){
                isFinish = false;
                break;
            }
        }
        if (isFinish) break;

        int nxt_node_x, nxt_node_y, nxt_node_d = 99;

        for (pair<int, int> p : can_Move){
            if (map[p.first][p.second] == 0) continue;
            if (map[p.first][p.second] == shark_size) continue;

            int tmp_dis = costs[p.first][p.second];
            // int tmp_dis = abs(x_pos - p.first) + abs(y_pos - p.second);

            if (nxt_node_d > tmp_dis){
                nxt_node_x = p.first; nxt_node_y = p.second;
                nxt_node_d = tmp_dis;
            }
            if (nxt_node_d == tmp_dis){
                // 동일할 경우 x,y가 작은 순으로
                if (p.first < nxt_node_x){ // x값이 더 작은 경우 (더 위)
                    nxt_node_x = p.first;
                    nxt_node_y = p.second;
                }else if (p.first == nxt_node_x){ // x값 동일
                    nxt_node_y = p.second < nxt_node_y ? p.second : nxt_node_y;
                }else{ // x값이 더 큰 경우 (더 아래)
                    continue; // 기존 넥스트 노드 유지
                }
            }
        }

        ans += costs[nxt_node_x][nxt_node_y];
        x_pos = nxt_node_x;
        y_pos = nxt_node_y;

        eat_fish();
    }
}

vector<pair<int, int>> bfs(){
    memset(costs, 0, sizeof(costs)); // 0 초기화
    memset(isVisited, false, sizeof(isVisited)); // false 초기화
    queue<pair<int, int>> q;
    q.push(make_pair(x_pos, y_pos));
    isVisited[x_pos][y_pos] = true;
    vector<pair<int, int>> v;

    while(!q.empty()){
        int tmp_x = q.front().first, tmp_y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++){
            int nx = tmp_x + dx[i], ny = tmp_y + dy[i];

            if (nx >= 0 && ny >= 0 && nx < N && ny < N){ // 범위 안
                if (map[nx][ny] <= shark_size && isVisited[nx][ny] == false){ // 샤크보다 작고, 온 적 없는 노드
                    isVisited[nx][ny] = true;
                    v.emplace_back(make_pair(nx, ny));
                    q.push(make_pair(nx, ny));
                    costs[nx][ny] += costs[tmp_x][tmp_y] + 1; // 거리 측정
                }
            }
        }
    }
    
    return v;
}


/*
N*N 크기 맵
물고리 M마리
아기상어 1마리

한칸에 물고기 최대 1마리 -> 없을 수도 있다.

아기상어와 물고기는 크기를 가짐 (자연수)

아기상어
처음 크기 2
1초에 상하좌우 1칸 이동
자기보다 큰 물고기 있는 칸 이동 x
나머지칸은 지나갈 수 있
본인보다 작은 물고기만 먹을 수 있음. (그럼 자기랑 같은 크기는? -> 못먹지만 지나갈 순 있)

이동 결정 알고리즘
    1. 먹을 수 있는 물고기가 없으면 엄마 상어에게 도움 요청 (return;)
    2. 먹을 수 있는 물고기가 1마리 -> 먹으러간다.
    3. 1마리보다 많으면 -> 가장 가까운 물고기 먹으러 감
        거리: 아기상어 칸에서 물고기칸으로 이동할 때 지나야하는 칸의 개수 최솟값
        만약 동일 거리 -> 가장 위에 있는 물고기, 가장 위 물고기가 여러마리면 가장 왼쪽부터
        (가장 위 가장 왼쪽 -> forfor?)

먹는데 걸리는 시간 x
이동과 동시에 먹음

먹으면 -> 빈칸이됨

크기 증가: 본인 크기와 같은 물고기 수를 먹을 때 증가 (먹는 물고기의 크기 상관 x)

몇 초동안 엄마상어에게 도움요청 x, 잡아먹을 수 있는 지

구현

1, 2, 3, 4, 5, 6 -> 물고기 크기
0 빈칸
9 -> 아기 상어

거리 측정할때 돌아가게 측정해야함.

*/