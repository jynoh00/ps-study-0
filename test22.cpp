// 감시
#include <iostream>
#include <stdio.h>
#include <vector>
#include <cstring>

#define endl "\n"
#define MAX 8

using namespace std;

int map[MAX][MAX];
bool isView[MAX][MAX];
int N, M;
vector<pair<int, pair<int, int>>> all_cctvs;
int cctv_cnt = 0;

int dx[] = {0, 0, 1, -1}; // 동 서 남 북
int dy[] = {1, -1, 0, 0};

vector<vector<int>> cctv_dir[6] = {{{0}}, 
                                {{0}, {1}, {2}, {3}}, // 1번
                                {{0, 1}, {2, 3}}, // 2번
                                {{0, 2},{0, 3},{1, 2},{1, 3}}, // 3번
                                {{0, 1, 2}, {0, 1, 3}, {0, 2, 3}, {1, 2, 3}}, // 4번
                                {{0, 1, 2, 3}}}; // 5번
// 0버림, 1~5

int watch_cnt = 0, zero_cnt = 0;
int cctv_direction[8];

int max(int a, int b){ return a > b ? a : b; }
void input();
void solution(int idx);
int calcu_watch_cnt();

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solution(0);

    cout << zero_cnt - watch_cnt << endl;

    return 0;
}

void input(){
    cin >> N >> M;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            cin >> map[i][j];
            if (map[i][j] != 0 && map[i][j] != 6){
                all_cctvs.emplace_back(make_pair(map[i][j], make_pair(i, j)));
                cctv_cnt++;
            }
            if (map[i][j] == 0) zero_cnt++;
        }
    }
}

int calcu_watch_cnt(){
    memset(isView, false, sizeof(isView));
    int tmp_cnt = 0;

    for (int i = 0; i < cctv_cnt; i++){
        int x_pos = all_cctvs[i].second.first;
        int y_pos = all_cctvs[i].second.second;

        for (int j = 0; j < cctv_dir[all_cctvs[i].first][cctv_direction[i]].size(); j++){ // 바라보는 방향
            int tmp_dir = cctv_dir[all_cctvs[i].first][cctv_direction[i]][j];
            int nx = x_pos, ny = y_pos;

            while(true){ // 무한 반복
                nx += dx[tmp_dir], ny += dy[tmp_dir];
                if (nx >= 0 && ny >= 0 && nx < N && ny < M){ // 맵 내부
                    if (map[nx][ny] == 6) break;
                    if (map[nx][ny] == 0){
                        if (isView[nx][ny] == true) continue;
                        tmp_cnt++;
                        isView[nx][ny] = true;
                    }
                    
                }else break;
            }
        }
    }
    return tmp_cnt;
}

void solution(int idx){
    if (idx == cctv_cnt){ // 전체 cctv 모두 선택
        watch_cnt = max(watch_cnt, calcu_watch_cnt());
        return;
    }

    for (int i = idx; i < cctv_cnt; i++){ // 전체 CCTV 순회
        int cctv_number = all_cctvs[i].first;
        for (int j = 0; j < cctv_dir[cctv_number].size(); j++){ // 해당 번호 CCTV 배치 경우의 수 조회
            cctv_direction[i] = j;

            solution(i+1);
        }
    }
}

/*
맵 N*M

K개의 CCTV

CCTV 5가지 종류 (해당 방향으로 벽나올때까지 전체), 대각선 확인 불가
    1- 한쪽만 1개 => 4가지
    2- 반대방향 2개 => 2가지
    3- 90도 2개 => 4가지
    4- 한쪽 빼고 나머지 3개 =>4가지
    5- 전체 4개 => 1가지

1. CCTV 벽 통과 x
2. 감시x 영역 사각지대
3. CCTV 회전도 가능 ;;
    -> 회전은 항상 90도 방향 (시계-반시계 둘 다?)

0: 빈칸
6: 벽
1~5: CCTV 번호

CCTV는 CCTV 통과 가능

각 CCTV의 방향을 정하고 사각지대의 최소값 리턴

CCTV 최대 개수 8개

최대 경우 : 4^(8)
*/