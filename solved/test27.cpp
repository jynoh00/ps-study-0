// 어항정리
#include <iostream>
#include <stdio.h>
#include <vector>

#define endl "\n"
#define MAX 100 // 어항 개수

using namespace std;

int N, K, ans = 0; // N개면 나올 수 있는 맵은 N*N 배열 -> 위로만 늘어나잖아?? -> [N-1][0]~[N-1][N-1]에 초기 입력 받고 작업
int map[MAX][MAX];
int tmp_map[MAX][MAX];
int min_value = 100001, max_value = 0;
int high_arr[MAX];

// 인접
int dx[] = {0, 1};
int dy[] = {1, 0};

int max(int a, int b){ return a > b ? a : b; }
int min(int a, int b){ return a < b ? a : b; }
void input();
void solution();

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solution();

    cout << ans << endl;

    return 0;
}

void input(){
    cin >> N >> K;
    for (int j = 0; j < N; j++){
        cin >> map[N-1][j]; // 마지막 행
        min_value = min(min_value, map[N-1][j]);
        max_value = max(max_value, map[N-1][j]);
    }
}

void to_Left(int where_x, int start_y, int end_y){
    if (start_y == 0) return;

    vector<int> line_v;
    int tmp_num = end_y - start_y;

    for (int j = start_y; j <= end_y; j++){
        line_v.emplace_back(map[where_x][j]);
    }

    for (int j = 0; j <= tmp_num; j++){ // if start_y = 4, end_y = 7 => 4칸 , 7-4 = 3 0 <= 3
        map[where_x][j] = line_v[j];
    }

    for (int j = tmp_num+1; j <= end_y; j++) map[where_x][j] = 0; // 빈 공간
}

vector<int> rotation_func(int where, int start_node, int end_node, int angle){
    vector<int> ans_v;
    if (angle == 90){ // x가 스타트-엔드 노드, where은 y좌표
        for (int i = end_node; i >= start_node; i--){
            ans_v.emplace_back(map[i][where]);
        }

        return ans_v;
    }

    for (int i = end_node; i >= start_node; i--){ // 반대 정렬
        ans_v.emplace_back(map[where][i]);
    }
    
    return ans_v;
}

void fish_num_change(){
    memset(tmp_map, 0, sizeof(tmp_map));

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (map[i][j] > 0){
                for (int d = 0; d < 2; d++){ // 우, 하 만 보면 중복 없이 전체 판단 가능
                    int nx = i + dx[d], ny = j + dy[d];
                    if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;

                    int tmp_d = (abs(map[i][j]-map[nx][ny]))/5;
                    if (tmp_d > 0){
                        if (map[i][j] > map[nx][ny]){
                            tmp_map[i][j] -= tmp_d;
                            tmp_map[nx][ny] += tmp_d;
                            continue;
                        }

                        tmp_map[i][j] += tmp_d;
                        tmp_map[nx][ny] -= tmp_d;
                    }else continue;
                }
            }else continue;
        }
    }

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            map[i][j] += tmp_map[i][j];
        }
    }
}

void all_zero(){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            map[i][j] = 0;
        }
    }
}

void high_arr_update(){
    for (int j = 0; j < N; j++){
        high_arr[j] = 0;
        for (int i = N-1; i >= 0; i--){
            if (map[i][j] == 0) break;
            high_arr[j]++;
        }
    }
}

void display_arr(){
    cout << endl;
    for (int i = 0; i < N; i++){
        for (int j = 0; j <N; j++){
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
}

void fish_plus(){
    for (int j = 0; j < N; j++) if (map[N-1][j] == min_value) map[N-1][j]++;
}

void stacking_left(){
    int tmp_left = map[N-1][0];
    to_Left(N-1, 1, N-1); // N-1,1 -> N-1,N-1 좌밀착 (나머지 부분 0으로)
    map[N-2][0] = tmp_left;
}

void rotation_stacking(bool isFirst){
    bool isCan = true;
    vector<vector<int>> v_v;
    while(isCan){
        if (isFirst){
            int j_idx = -1;
            int _high = -1;

            for (int j = 0; j < N; j++){
                if (high_arr[j] == 0) break; // for문만 종료
                if (high_arr[j] >= 2){
                    j_idx = j;
                    _high = high_arr[j];
                }
            }

            if (j_idx == -1 || _high == -1){
                isCan = false;
                break;
            }

            for (int j = 0; j <= j_idx; j++){
                vector<int> tmp_v;
                for (int i = N-1; i >= N-_high; i--){
                    tmp_v.emplace_back(map[i][j]);
                }
                v_v.emplace_back(tmp_v);
            }

            if (v_v.size() == 0){
                isCan = false;
                break;
            }

            for (int i = N-2; i >= N-1-v_v.size(); i--){
                
            }

            continue;
        }

        // isSecond


    }

}

void makeIt_one_line(){

}

void 
{

}

void solution(){
    for (int i = 0; i < N; i++) high_arr[i] = 1; // 높이

    while(abs(max_value-min_value) > K){
        // 1.물고기 추가(높이변화x)

        display_arr();

        // 2.어항 쌓기(높이변화o)


        // 3.공중부양(높이변화o)
        vector<int> tmp_v = rotation_func(0, N-2, N-1, 90); // y=0, N-2~N-1범위 x, 90도 회전 => N-2 ~ N-1 순 map값 벡터 리턴
        to_Left(N-1, 1, N-2);
        for (int j = 0; j < tmp_v.size(); j++) map[N-2][j] = tmp_v[j];
        high_arr_update();
        display_arr();

        // 4.물고기 수 조절
        fish_num_change();
        display_arr();

        // 5.일렬정리(높이변화o)
        tmp_v.clear();
        for (int j = 0; j < N; j++){
            if (high_arr[j] <= 0) break;

            for (int i = N-1; i >= N-high_arr[j]; i--){
                tmp_v.emplace_back(map[i][j]);                
            }
        }
        all_zero();
        for (int j = 0; j < N; j++){
            map[N-1][j] = tmp_v[j];
        }
        high_arr_update();
        display_arr();

        // 6.공중부양(높이변화o)
        bool repeat_b = true;
        vector<vector<int>> v_v;
        while(repeat_b){
            for (int k = 0; k < N; k++){
                if (high_arr[k] == 0){
                    repeat_b = false;
                    break;
                }

                tmp_v = rotation_func(N-1, 0, (N/2)-1, 180);
                to_Left(N-1, N/2, N-1);
                for (int j = 0; j < N/2; j++){
                    map[N-2][j] = tmp_v[j];
                }
            high_arr_update();
            }
        }
        display_arr();

        // 7.공중부양(높이변화o)
        v_v.clear(); // 2개 벡터담을 예정
        for (int i = N-2; i < N; i++){
            tmp_v = rotation_func(i, 0, (N/4)-1, 180);
            to_Left(i, N/4, (N/2)-1);
            v_v.emplace_back(tmp_v); // N-2뒤집은거랑, N-1뒤집은거 순으로 들어감.
        }

        int tmp_i = 0;
        for (vector<int> v : v_v){ // N-2 뒤집은거, N-1 뒤집은거 순
            for (int j = 0; j < N/4; j++){
                map[N-3-tmp_i][j] = v[j];
            }
            tmp_i++;
        }
        high_arr_update();
        display_arr();

        // 8. 물고기 수 조절
        fish_num_change();
        display_arr();

        // 9. 일렬정리
        tmp_v.clear();
        for (int j = 0; j < N; j++){
            if (high_arr[j] <= 0) break;

            for (int i = N-1; i >= N-high_arr[j]; i--){
                tmp_v.emplace_back(map[i][j]);                
            }
        }
        all_zero();
        for (int j = 0; j < N; j++){
            map[N-1][j] = tmp_v[j];
            high_arr[j] = 1;
        }
        display_arr();

        ans++; // 1회 시행

        min_value = 100001, max_value = 0;
        for (int j = 0; j < N; j++){
            min_value = min(min_value, map[N-1][j]);
            max_value = max(max_value, map[N-1][j]);
        }
    }
}

void solution(){
    for (int j = 0; j < N; j++) high_arr[j] = 1; // init

    while(abs(max_value-min_value) > K){
        // 1.
        fish_plus();

        // 2.
        stacking_left();
        high_arr_update();

        // 3.
        rotation_stacking(true); // while
        high_arr_update();

        // 4.
        fish_num_change();

        // 5.
        makeIt_one_line();
        high_arr_update();

        // 6.
        rotation_stacking(false);
        high_arr_update();

        // 7.
        makeIt_one_line(); 
        high_arr_update(); // 111111~

        change_max_min();
        ans++;
    }
}

/*
어항을 정리하려함

한 변의 길이 1 - 정육면체 어항 N개를 가지고 있음

처음에 일렬로

칸에 적힌 값 = 어항 물고기 수

정리 과정

1. 물고기 수 가장 적은 어항에 1마리 넣음 (그런 어항 여러개면 -> 모두 1마리씩)
2. 어항 쌓기 (가장 왼쪽 어항을 그 오른쪽 어항 위에)
3. 2개 이상 쌓인 어항을 모두 "공중부양" 이후 시계방향 90도 회전, 이후 바닥에 놓음 (바닥에 놓을 수 없으면 이 과정 스킵)
4. 물고기 수 조절 (인접 어항 물고기 수 차이를 구함, 이 차이를 /5한 몫 d)
    d>0 : 물고기가 많은 곳에서 d 마리를 적은 곳으로 , 모든 인접 칸에서 동시 발생 -> 나눔으로 인해 새로 생긴 차이 고려x 의미
5. 다시 일렬 정리 왼쪽 어항 (아래에서 위)부터 오른쪽으로)
6. 다시 공중 부양, 가운데 중심 왼쪽 N/2개(절반)를 공중부양 이후 180도 시계방향 회전하고 위로 쌓음
7. 바닥은 N/2인 상태, 왼쪽 N/4개를 다시 6번하고 오른쪽 N/4 위에 쌓음
8. 물고기 수 조절 (4번)
9. 일렬 정리 (5번)

-> 이렇게가 1번

어항의 수 N
초기 어항별 물고기 수 주어짐

물고기수 최댓값과 최솟값 차이 <= K가 되려면
어항을 몇 번 정리해야하나 (정리과정을 몇 번 반복해야 하나)
*/


/*

*/