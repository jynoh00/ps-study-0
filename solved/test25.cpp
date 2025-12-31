// 마법사 상어와 파이어볼
#include <iostream>
#include <stdio.h>
#include <vector>
#include <cstring>

#define endl "\n"
#define MAX 51


using namespace std;

int N, M, K;
int map[MAX][MAX][4]; // i, m, s, d
int tmp_map[MAX][MAX][4];
vector<pair<int, int>> pos_v;
vector<int> map_dirs[MAX][MAX];
int ans = 0;

int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1}; // 북 -> 시계방향 -> 북서
int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};

void input(); void solution();

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    for (int i = 0; i < K; i++) solution();

    for (int r = 1; r <= N; r++){
        for (int c = 1; c <= N; c++){
            ans += map[r][c][1];
        }
    }

    cout << ans << endl;

    return 0;
}

void input(){
    cin >> N >> M >> K;

    for (int i = 1; i <= M; i++){ // 파이어볼 개수
        int r, c;
        cin >> r >> c;
        map[r][c][0] = 1;
        for (int j = 1; j <= 3; j++){ // m, s, d
            cin >> map[r][c][j];
        }

        pos_v.emplace_back(make_pair(r, c)); // 현재 파이어볼 위치 (이동시킬)
    }
}

void solution(){
    memset(tmp_map, 0, sizeof(tmp_map)); // 0 초기화 
    for (int r = 1; r <= N; r++){
        for (int c = 1; c <= N; c++){
            map_dirs[r][c].clear();
        }
    }

    for (pair<int, int> p : pos_v){ // pos_v 파이어볼 위치 벡터
        int x = p.first;
        int y = p.second;
        int m = map[x][y][1];
        int s = map[x][y][2];
        int d = map[x][y][3];

        int nx = (x + dx[d] * (s%N) + N - 1)%N + 1;
        int ny = (y + dy[d] * (s%N) + N - 1)%N + 1;

        tmp_map[nx][ny][0]++;
        tmp_map[nx][ny][1] += m;
        tmp_map[nx][ny][2] += s;
        // tmp_map[nx][ny][3] += d;
        map_dirs[nx][ny].emplace_back(d); // 짝 홀 판단용
    }

    pos_v.clear(); // 초기화
    for (int r = 1; r <= N; r++){
        for (int c = 1; c <= N; c++){
            if (tmp_map[r][c][0] > 1){
                pos_v.emplace_back(make_pair(r, c));
            }
        }
    }
    // while(check_twoPlus()){ // 2개 이상 겹친 칸이 존재하면
    for (pair<int, int> p : pos_v){ // 2개 이상 겹친 칸들
        int x = p.first, y = p.second;
        int m = tmp_map[x][y][1] / 5;
        if (m == 0) continue; // 질량 0은 사라진다.

        int s = tmp_map[x][y][2] / tmp_map[x][y][0];

        bool udlr = true;
        int check_num = -1;
        for (int d : map_dirs[x][y]){
            if (check_num == -1){
                check_num = d%2;
                continue;
            }

            if (check_num != d%2){
                udlr = false;
                break;
            }
        }
        map_dirs[x][y].clear(); // 이후 해당 부분 클리어 디렉션

        int dirs[4];
        
        if (udlr){
            int tmp[4] = {0, 2, 4, 6};
            memcpy(dirs, tmp, sizeof(dirs));
        }else{
            int tmp[4] = {1, 3, 5, 7};
            memcpy(dirs, tmp, sizeof(dirs));
        }

        for (int d : dirs){
            // int nx = x + s*dx[d], ny = y + s*dy[d];
            int nx = (x + dx[d] * (s%N) + N - 1)%N + 1;
            int ny = (y + dy[d] * (s%N) + N - 1)%N + 1;
            
            tmp_map[nx][ny][0]++;
            tmp_map[nx][ny][1] += m;
            tmp_map[nx][ny][2] += s;
            map_dirs[nx][ny].emplace_back(d);
        }

        for (int i = 0; i < 4; i++){ // 현재 위치 0
            tmp_map[x][y][i] = 0;
        }
    }
    pos_v.clear();
    // }

    // 파이어볼 있는 곳 pos_v에 담기
    // map에 tmp_map 대입
    for (int r = 1; r <= N; r++){
        for (int c = 1; c <= N; c++){
            for (int i = 0; i < 4; i++){
                map[r][c][i] = tmp_map[r][c][i];
            }

            if (map[r][c][0] > 0) pos_v.emplace_back(make_pair(r, c)); // 파이어볼 있는 곳 좌표
        }
    }
}

// rotlqkf -> 4개로 나누고 이동이아니라 4개로 나뉜 상태로 한 칸 안에 있는거였음
// 그리고 이동 명령 떨어지면 각자 방향으로 이동
// 또 2개 이상인 것들을 모두 합쳐서 4개로 나뉜 상태로 존재하게



// bool check_twoPlus(){
//     for (int r = 1; r <= N; r++){
//         for (int c = 1; c <= N; c++){
//             if (tmp_map[r][c][0] > 1){
//                 pos_v.emplace_back(make_pair(r, c));
//             }
//         }
//     }

//     return pos_v.size() > 0;
// }

/*

어른 상어 -> 마법사 상어

파이어볼

N*N인 맵

파이어볼 M개 발사

처음 각 파이어볼은 위치에서 이동 대기 중

i번 파이어볼 위치 (ri, ci), 질량 mi, 방향 di, 속력 si

1,1 ~ N,N

이동 명령.
    1. 각 파이어볼이 본인 방향 di로 si만큼 이동. (이동 중 같은 칸에 파이어볼 여러개 존재 가능)
    2. 이동이 끝난 후 2개 이상의 파이어볼이 있는 칸에서 다음
        ㄱ. 같은 칸 파이어볼을 합침
        ㄴ. 파이어볼이 4개의 파이어볼로 나누어짐
        ㄷ. 나누어진 파이어볼의 질량 속력 방향
            a. 질량 = 합쳐진 파이어볼 질량/5
            b. 속력 = 합쳐진 파이어볼 속력/합쳐진 개수
            c. 합쳐지는 파이어볼의 방향이 모두 홀수이거나 모두 짝수면 방향은 0, 2, 4, 6 아니면 1, 3, 5, 7
        ㄹ. 질량이 0인 파이어볼은 사라짐.

이동 명령 K번 이후 남아있는 파이어볼의 질량

1. 소수점 버림?
2. 합쳐진다는건 단순 sum?



*/