// 청소년 상어
#include <iostream>
#include <stdio.h>

#define MAX 4
#define endl "\n"

using namespace std;

pair<int, int> fishes[17]; // 물고기 번호 순 1 ~ 16 좌표, 0번 버림
pair<int, int> map[MAX][MAX]; // 0 빈칸, -1 상어, 양수 물고기
int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1}; // 반시계 북 -> 북동
int dy[] = {0, -1, -1, -1, 0, 1, 1, 1};
int x_pos = 0, y_pos = 0;
int ans = 0;

int max(int a, int b){ return a > b ? a : b; }
void input(); void solution(int sx, int sy, int sd, int sum);
void fish_move(int idx);
vector<int> calcu_distance(int sx, int sy, int sd);

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    // 퍼블
    ans += map[0][0].first; 
    fishes[map[0][0].first].first = -1; // 죽은 물고기
    map[0][0].first = -1; // 상어 -1, 방향 유지
    

    solution(x_pos, y_pos, map[0][0].second, ans);

    cout << ans << endl;

    return 0;
}

void input(){
    for (int i = 0; i < MAX; i++){
        for (int j = 0; j < MAX; j++){
            int a, b;
            cin >> a >> b;
            map[i][j] = make_pair(a, b); // 물고기 번호, 방향
            fishes[a] = make_pair(i, j); // 물고기 위치
        }
    }

}
void solution(int sx, int sy, int sd, int sum){
    // 물고기 움직이기
    for (int i = 1; i <= 16; i++){
        fish_move(i);
    }

    vector<int> calcu_distances = calcu_distance(sx, sy, sd); // 이동 가능 칸 수
    if (calcu_distances.size() == 0){ // 이동 불가
        ans = max(ans, sum);
        return;
    }

    for (int i = 0; i < calcu_distances.size(); i++){
        // 현재 위치 빈칸으로
        map[sx][sy].first = 0;
        map[sx][sy].second = 0;
        
        int tmp_x = sx, tmp_y = sy;
        int tmp_d = sd;

        int nx = sx + dx[sd]*calcu_distances[i];
        int ny = sy + dy[sd]*calcu_distances[i];

        int fish_tmp_i = map[nx][ny].first;
        int fish_tmp_d = map[nx][ny].second;

        int nd = fish_tmp_d;

        fishes[fish_tmp_i].first = -1; // 죽은 물고기
        fishes[fish_tmp_i].second = -1;

        sum += fish_tmp_i;
        map[nx][ny].first = -1;
        
        solution(nx, ny, nd, sum);
        
        sum -= fish_tmp_i;
        map[nx][ny].first = fish_tmp_i;
        
        fishes[fish_tmp_i].first = nx;
        fishes[fish_tmp_i].second = ny;        
    }

    // 상어 움직이기, 먹기 -> 조합 몇 칸 이동할 지 (1~3칸) solution(sum)
    /*
    이동할 수 있는 칸 수들 계산 -> 벡터에 담아 -> if 못 움직여 => ans = max(ans, sum);

    for (벡터)
        현재칸 빈칸으로 설정
        물고기 킬 (빈칸이면? -> 빈칸으로 이동 불가)
        상어 다음 위치 설정
        solution(sum+물고기);
        상어 현재 위치로 재설정
        물고기 부활
    */

}

void fish_move(int fish){
    if (fishes[fish].first == -1) return; // 죽은 물고기 : 죽은 물고기 좌표는 -1, -1로 저장

    int tmp_x = fishes[fish].first, tmp_y = fishes[fish].second;
    int tmp_d = map[tmp_x][tmp_y].second;
    for (int i = 0; i < 7; i++){ // +0, +1, +2, +3, +4, +5, +6
        int nd = (tmp_d + i)%8;
        int nx = tmp_x + dx[nd], ny = tmp_y + dy[nd];

        if (nx >= 0 && ny >= 0 && nx < MAX && ny < MAX){ // 00 ~ 33
            if (map[nx][ny].first == -1){ // 상어면
                continue; // 다음 방향
            }else if (map[nx][ny].first == 0){ //빈칸
                map[tmp_x][tmp_y].first = 0;
                map[tmp_x][tmp_y].second = 0; // 빈칸으로
                map[nx][ny].first = fish;
                map[nx][ny].second = nd;
                fishes[fish].first = nx;
                fishes[fish].second = ny;

                return;
            }else{ // 물고기 교체
                map[tmp_x][tmp_y].first = map[nx][ny].first;
                map[tmp_x][tmp_y].second = map[nx][ny].second;
                fishes[map[nx][ny].first].first = tmp_x;
                fishes[map[nx][ny].first].second = tmp_y;

                map[nx][ny].first = fish;
                map[nx][ny].second = nd;
                fishes[fish].first = nx;
                fishes[fish].second = ny;

                return;
            }
        }
    }
    // 이동불가 (변경 x) -> 이럴 수가 있나??
    return;
}

vector<int> calcu_distance(int sx, int sy, int sd){
    vector<int> ans_v;
    int direction = sd; // 상어 방향

    for (int i = 1; i <= 3; i++){
        int nx = sx + dx[direction]*i, ny = sy + dy[direction]*i;

        if (nx >= 0 && ny >= 0 && nx < MAX && ny < MAX){ // 맵 내부
            if (map[nx][ny].first > 0) ans_v.emplace_back(i);
        }
    }

    return ans_v;
}

/*
4*4 크기 공간

(x,y)로 각 공간
한 칸에 물고기 1마리 존재 -> 물고기 : 번호(1<= <=16), 방향(8가지)

(0,0)에 있는 물고기를 먹고 그 위치에 들어감 (방향은 (0,0)에 있던 물고기 방향을 가져옴)

물고기는 번호가 작은 물고기부터 순서대로 이동함.
이동가능한 칸 : 빈칸 or 다른 물고기가 있는 칸
x 칸 : 상어가 있는 칸, 맵 외부

각 물고기는 이동가능한 방향이 나올 때 까지 45도 반시계 방향으로 방향 회전
    이동 불가 -> 이동 x (이동 불가일 수가 있나?)
해당 방향으로 이동

물고기가 다른 물고기가 있는 칸으로 이동할 때는 서로 위치를 바꾸는 방식으로 이동

모든 물고기 이동 종료 -> 상어 이동 시작
방향 칸으로 이동 가능 - 한번에 여러 칸 이동 가능
상어가 물고기 방향으로 이동함. -> 그 물고기 먹고 방향을 가져옴 // 이동 중 지나가는 칸 물고기는 먹지 않음. (도착지점만 먹음)
물고기가 없는 칸으로 이동 불가
이동 가능한 칸이 없으면 집으로 감

물고기 이동 -> 상어 이동 -> 물고기 이동 -> ...

상어가 먹을 수 있는 물고기 합의 최댓값 리턴
(여러 칸 이동이 포인트)



*/