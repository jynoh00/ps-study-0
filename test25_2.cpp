#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>

#define endl "\n"
#define MAX 51

using namespace std;

int N, M, K;
vector<struct Fireball> fireball_vec;
pair<int, int> map[MAX][MAX]; // 개수, 질량 합

int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};

vector<int> map_dirs[MAX][MAX];
int map_speeds[MAX][MAX];
int ans = 0;

struct Fireball{
    int r;
    int c;
    int m;
    int s;
    int d;
};

void input(); void solution();

int main(){
    cin.tie(NULL); cout.tie(NULL);

    input();
    for (int i = 0; i < K; i++){
        solution();
    }

    for (Fireball fb : fireball_vec) ans += fb.m;

    cout << ans << endl;

    return 0;
}

void input(){
    cin >> N >> M >> K;

    for (int i = 0; i < M; i++){
        Fireball fb;
        cin >> fb.r >> fb.c >> fb.m >> fb.s >> fb.d;
        fireball_vec.emplace_back(fb);
    }
}

void solution(){
    for (int r = 1; r <= N; r++){ // 방향 벡터 초기화
        for (int c = 1; c <= N; c++){
            map_dirs[r][c].clear();
            map[r][c] = {0, 0};
        }
    }
    memset(map_speeds, 0, sizeof(map_speeds));

    // 이동
    for (Fireball fb : fireball_vec){
        // 다음 위치로 이동
        int nr = (fb.r + dx[fb.d] * (fb.s%N) + N - 1)%N + 1;
        int nc = (fb.c + dy[fb.d] * (fb.s%N) + N - 1)%N + 1;
        map[nr][nc].first++;
        map[nr][nc].second += fb.m;
        map_dirs[nr][nc].emplace_back(fb.d);
        map_speeds[nr][nc] += fb.s;
    }


    fireball_vec.clear();
    // 합치기
    for (int r = 1; r <= N; r++){
        for (int c = 1; c <= N; c++){
            if (map[r][c].first > 1){ // 2개 이상 위치하면
                int nm = map[r][c].second / 5;
                if (nm == 0) continue; // 사라짐.

                int ns = map_speeds[r][c] / map[r][c].first;

                bool udrl = true;
                int check_num = -1;
                for (int d : map_dirs[r][c]){
                    if (check_num == -1){
                        check_num = d%2;
                        continue;
                    }

                    if (check_num != d%2){
                        udrl = false;
                        break;
                    }
                }

                int dirs[4];
                if (udrl){
                    int tmp_dirs[4] = {0, 2, 4, 6};
                    memcpy(dirs, tmp_dirs, sizeof(dirs));
                }else{
                    int tmp_dirs[4] = {1, 3, 5, 7};
                    memcpy(dirs, tmp_dirs, sizeof(dirs));
                }

                for (int d = 0; d < 4; d++){ // 4개 추가
                    Fireball fb;
                    fb.r = r; fb.c = c;
                    fb.m = nm;
                    fb.s = ns;
                    fb.d = dirs[d];

                    fireball_vec.emplace_back(fb);
                }
            }else if (map[r][c].first == 1){ // 1개 존재
                Fireball fb;
                fb.r = r; fb.c = c;
                fb.m = map[r][c].second;
                fb.d = map_dirs[r][c][0]; // 1개만 들어와 있을거니까
                fb.s = map_speeds[r][c]; // 동일

                fireball_vec.emplace_back(fb);
            }else continue; // 파이어볼 x
        }
    }
}