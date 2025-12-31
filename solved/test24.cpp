// 상어 초등학교
#include <iostream>
#include <stdio.h>
#include <cstring>

#define endl "\n"
#define MAX 21 // 1,1 ~ 20,20까지

using namespace std;

int N;
int map[MAX][MAX];
pair<int, int> like_map[MAX][MAX]; // (선호도, 주변 빈칸 수)
int students[MAX*MAX][4]; // i -> 학생 번호, [i][] = 좋아하는 학생 번호
int stu_id[MAX*MAX];
int ans = 0;
int like_point[5] = {0, 1, 10, 100, 1000};

int dx[] = {0, 0, 1, -1}; // 우 좌 상 하
int dy[] = {1, -1, 0, 0};

void input(); void solution();
void isGoodSearch();

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
    for (int i = 1; i <= N*N; i++){
        cin >> stu_id[i]; // 학생 번호

        for (int j = 0; j < 4; j++){
            cin >> students[stu_id[i]][j]; // 학생 번호가 좋아하는 학생 번호s
        }
    }
}

void solution(){
    for (int i = 1; i <= N*N; i++){
        memset(like_map, 0, sizeof(like_map)); // 적합도

        int tmp_stu = stu_id[i]; // 지금 학생 번호
        int x_pos = 0, y_pos = 0;
        
        for (int r = 1; r <= N; r++){ // 자리 선호도
            for (int c = 1; c <= N; c++){
                if (map[r][c] != 0){
                    like_map[r][c].first = -1; // 못 앉는 곳
                    continue;
                }

                for (int d = 0; d < 4; d++){ // 상하좌우
                    int nx = r + dx[d], ny = c + dy[d];

                    if (nx > 0 && ny > 0 && nx <= N && ny <= N){ // 1,1 ~ N,N
                        if (map[nx][ny] == 0) like_map[r][c].second++;

                        int isGoodCnt = 0;
                        for (int like_idx = 0; like_idx < 4; like_idx++){
                            if (map[nx][ny] == students[tmp_stu][like_idx]){
                                isGoodCnt++;
                            }
                        }

                        like_map[r][c].first += isGoodCnt;
                    }
                }
            }
        }

        for (int r = 1; r <= N; r++){
            for (int c = 1; c <= N; c++){
                if (like_map[r][c].first == -1) continue;

                if (x_pos == 0 && y_pos == 0){
                    x_pos = r;
                    y_pos = c;

                    continue;
                }
                
                if (like_map[x_pos][y_pos].first < like_map[r][c].first){ // 선호도가 더 큼
                    x_pos = r;
                    y_pos = c;

                    continue;
                }else if (like_map[x_pos][y_pos].first == like_map[r][c].first){ // 선호도 동일
                    if (like_map[x_pos][y_pos].second < like_map[r][c].second){ // 주변 빈칸 더 많음
                        x_pos = r;
                        y_pos = c;
                    }else if (like_map[x_pos][y_pos].second == like_map[r][c].second){ // 주변 빈칸 동일
                        if (x_pos > r){
                            x_pos = r;
                            y_pos = c;
                        }else if (x_pos == r){
                            if (y_pos > c){
                                x_pos = r;
                                y_pos = c;
                            }else{
                                continue;
                            }
                        }else continue;
                    }else{ // 주변 빈칸 더 적음
                        continue;
                    }
                }else{ // 선호도가 더 작음
                    continue;
                }
            }
        }             

        map[x_pos][y_pos] = tmp_stu;
    }

    isGoodSearch();
}

void isGoodSearch(){
    for (int r = 1; r <= N; r++){
        for (int c = 1; c <= N; c++){
            int tmp_stu = map[r][c];
            int cnt = 0;

            for (int d = 0; d < 4; d++){ // 상하좌우
                int nx = r + dx[d], ny = c + dy[d];

                if (nx > 0 && ny > 0 && nx <= N && ny <= N){ // 1,1 ~ N,N
                    for (int like_idx = 0; like_idx < 4; like_idx++){
                        if (map[nx][ny] == students[tmp_stu][like_idx]){
                            cnt++;
                        }
                    }
                }
            }

            ans += like_point[cnt];
        }
    }
}

/*
상어초딩학교 교실 하나

교실 크기 N*N

학생 수 N^2 -> 교실 크기와 동일

자리 정하는 날
학생 번호 1~N^2까지 

(r,c)

1,1 ~ N,N

좋아하는 학생 4명

abs(r1 - r2) + abs(c1 - c2) = 1 -> 상하좌우 1칸인 두 칸이 인접

1. 비어있는 칸 중 좋아하는 학생이 인접한 칸에 가장 많은 칸으로 자리 배정
2. 1 만족이 여러 개면 인접 칸 중 비어있는 칸이 가장 많은 칸으로 배정
3. 2도 여러개면 행의 번호(r)가 가장 작은 칸으로, 그러한 칸도 여러개면 (c)가 가장 작은 칸으로

인접 좋아하는 학생 수에 따라
0 : +0
1 : +1
2 : +10
3 : +100
4 : +1000

만족도 총합 출력

*/