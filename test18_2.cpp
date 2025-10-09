#include <iostream>
#include <stdio.h>
#include <queue>
#include <vector>
#include <cstring>
#include <climits>

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
                map[i][j] = 0; // 반드시 0으로 바꿔야 통로가 막히지 않음
                continue;
            }
            if (map[i][j] != 0) fish_cnt++;
        }
    }
}

void eat_fish(){
    eat_cnt++;
    if (eat_cnt == shark_size){
        eat_cnt = 0;
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

        int nxt_node_x = -1, nxt_node_y = -1;
        int nxt_node_d = INT_MAX;

        for (pair<int, int> p : can_Move){
            int r = p.first, c = p.second;
            if (map[r][c] == 0) continue;           // 빈칸
            if (map[r][c] == shark_size) continue;  // 같은 크기(지나갈 수는 있으나 먹을 수 없음)

            int tmp_dis = costs[r][c];
            if (tmp_dis < 0) continue; // 도달 불가 (안전장치)

            // 선택 기준: 거리 우선, 거리가 같으면 행(위)이 작은 것, 또 같으면 열(왼쪽)이 작은 것
            if (nxt_node_x == -1
                || tmp_dis < nxt_node_d
                || (tmp_dis == nxt_node_d && (r < nxt_node_x || (r == nxt_node_x && c < nxt_node_y)))){
                nxt_node_x = r;
                nxt_node_y = c;
                nxt_node_d = tmp_dis;
            }
        }

        // 안전 체크: 후보가 없으면 반복 종료
        if (nxt_node_x == -1) break;

        ans += nxt_node_d;
        x_pos = nxt_node_x;
        y_pos = nxt_node_y;

        eat_fish();
    }
}

vector<pair<int, int>> bfs(){
    // costs를 -1로 초기화해서 "도달 불가"와 "거리 0"을 구분
    memset(costs, -1, sizeof(costs));
    memset(isVisited, false, sizeof(isVisited));
    queue<pair<int, int>> q;
    q.push(make_pair(x_pos, y_pos));
    isVisited[x_pos][y_pos] = true;
    costs[x_pos][y_pos] = 0;
    vector<pair<int, int>> v;

    while(!q.empty()){
        int tmp_x = q.front().first, tmp_y = q.front().second;
        q.pop();

        for (int i = 0; i < 4; i++){
            int nx = tmp_x + dx[i], ny = tmp_y + dy[i];

            if (nx >= 0 && ny >= 0 && nx < N && ny < N){ // 범위 안
                if (!isVisited[nx][ny] && map[nx][ny] <= shark_size){ // 통과 가능하고 아직 방문 안 함
                    isVisited[nx][ny] = true;
                    q.push(make_pair(nx, ny));
                    costs[nx][ny] = costs[tmp_x][tmp_y] + 1; // 거리 대입

                    v.emplace_back(make_pair(nx, ny));
                }
            }
        }
    }
    
    return v;
}
