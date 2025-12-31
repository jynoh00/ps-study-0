// 마법사 상어와 비바라기
// 구현-시뮬 문제, 전역이 아닌 지역 변수에서 선언 시 초기화 주의: bool arr[MAX][MAX] = {false}; // 전체 false로
#include <iostream>
#include <vector>
#include <stdio.h>

#define endll "\n"
#define MAP_MAX 51
#define INST_MAX 101

using namespace std;

int N, M, ans = 0;
int A[MAP_MAX][MAP_MAX];
int dx[] = {0, 0, -1, -1, -1, 0, 1, 1, 1};
int dy[] = {0, -1, -1, 0, 1, 1, 1, 0, -1};
pair<int, int> insts[INST_MAX];
// ←, ↖, ↑, ↗, →, ↘, ↓, ↙ 
// 1, 2, 3, 4, 5, 6, 7, 8
vector<pair<int, int>> v;



void solution();
void input();
void calcu();
int water_copy_bug(int x, int y);

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    solution();

    return 0;
}

void solution(){
    input();
    calcu();

    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= N; j++){
            ans += A[i][j];
        }
    }
    cout << ans << endl;
}

void input(){
    cin >> N >> M;
    for (int i = 1; i <= N; i++){
        for (int j = 1; j <= N; j++){
            cin >> A[i][j];
        }
    }

    for (int i = 1; i <= M; i++){
        int di, si;
        cin >> di >> si;
        insts[i] = make_pair(di, si);
    }
}

void calcu(){
    // init
    v.emplace_back(make_pair(N-1, 1));
    v.emplace_back(make_pair(N-1, 2));
    v.emplace_back(make_pair(N, 1));
    v.emplace_back(make_pair(N, 2));

    for (int i = 1; i <= M; i++){ // i : 명령어 idx
        bool test_map[MAP_MAX][MAP_MAX] = {false};        

        int di = insts[i].first, si = insts[i].second;
        for (int j = 0; j < v.size(); j++){ // 모든 구름 순회
            // 구름 위치 이동
            for (int k = 0; k < si; k++){
                v[j].first += dx[di];    
                v[j].second += dy[di];

                if (v[j].first == 0) v[j].first = N;
                if (v[j].first == (N+1)) v[j].first = 1;
                if (v[j].second == 0) v[j].second = N;
                if (v[j].second == (N+1)) v[j].second = 1;
            }

            A[v[j].first][v[j].second]++; // 비내리기

            test_map[v[j].first][v[j].second] = true; // 마지막 구름 위치 저장
        }

        // 물 증가 칸, 대각선 물복사 버그
        for (int j = 0; j < v.size(); j++){
            A[v[j].first][v[j].second] += water_copy_bug(v[j].first, v[j].second);
        }

        v.clear(); // 구름 제거

        for (int x = 1; x <= N; x++){ // 구름 생성
            for (int y = 1; y <= N; y++){
                if (test_map[x][y]){
                    continue;
                }
                if (A[x][y] >= 2){
                    A[x][y] -= 2;
                    v.emplace_back(make_pair(x, y));
                }
            }
        }
    }
}

int water_copy_bug(int r, int c){
    int count = 0;
    for (int i = 2; i <= 8; i+=2){
        if (((r + dx[i]) == 0) || (r + dx[i] == (N+1)) || ((c + dy[i]) == 0) || ((c + dy[i]) == (N+1))){ // 맵 벗어나는 경우
            continue;
        }
        if (A[r+dx[i]][c+dy[i]] > 0) count++; // 물이 있으면
    }

    return count;
}

/*

// 마법사 상어: 파이어볼, 토네이도, 파이어스톰, 물복사버그
비바라기

맵 크기 N*N

격자 각 칸 바구니

A[r][c] <- 해당 칸에 있는 바구니에 담긴 물의 양



좌하단 4칸에 비구름 생성
N-1,1 N-1, 2
N,1 N2     

구름 이동 명령 M번
i번째 이동명령은 방향 di, 거리si로

방향 di는 총 8개
←, ↖, ↑, ↗, →, ↘, ↓, ↙ 
1, 2, 3, 4, 5, 6, 7, 8

1. 모든 구름이 di로 si칸 이동
2. 각 구름에서 비가 내려 칸 바구니 물양 +1
3. 구름이 사라짐
4. 2에서 물이 증가한 칸 (r,c)에 물복사버그 : 대각선방향 거리가 1인 칸에 물이 있는( > 0) 바구니의 수만큼 (r,c)에 있는 바구니의 물 양 증가 (x개 -> +x) (물 흡수가 아닌 "복사")
5. 바구니 물 양 (>= 2)인 모든 칸에 구름이 생김, 물의 양 (-2) : 이때 구름이 생기는 칸은 3에서 구름이 사라진 칸이 아니어야 함.

-> 구름이 생기는게 하나의 동작 과정


M번의 이동 끝난 후 모든 바구니에 들어있는 물의 양의 합


구현 - 시뮬레이션
*/