#include <iostream>
#include <stdio.h>
#include <vector>

using namespace std;

#define endl "\n"
#define MAX 100

int N, K, ans = 0;
int map[MAX][MAX];
int change_map[MAX][MAX];
int dx[] = {0, 1}; // 좌, 하
int dy[] = {1, 0};
int max_v = 0, min_v = 10001; // 1 <= 물고기 값 <= 10000
int high_arr[MAX];

void display_arr();
int max(int a, int b){ return a > b ? a : b; }
int min(int a, int b){ return a < b ? a : b; }
void input();
void solution();
void fish_plus();
void stacking_left();
void high_arr_update();
void rotation_stacking(bool flag);
void fish_num_change();
void make_it_one_line();
void change_max_min();
void toLeft(int where_x, int start_y, int end_y);


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
        cin >> map[N-1][j];
        max_v = max(max_v, map[N-1][j]);
        min_v = min(min_v, map[N-1][j]);
    }
}

void solution(){
    for (int j = 0; j < N; j++) high_arr[j] = 1; // init

    int qwe = 1;
    while(abs(max_v-min_v) > K){
        cout << qwe << "번째 시행" << endl;

        // 1.
        fish_plus();
        // display_arr();

        // 2.
        stacking_left();
        high_arr_update();
        // display_arr();

        // 3.
        rotation_stacking(true); // while
        high_arr_update();

        // 4.
        fish_num_change();

        // 5.
        make_it_one_line();
        high_arr_update();

        // 6.
        rotation_stacking(false);
        high_arr_update();

        // 7.
        fish_num_change();

        // 8.
        make_it_one_line();
        for (int i = 0; i < N-1; i++){
            for (int j = 0; j < N; j++){
                map[i][j] = 0;
            }
        }
        high_arr_update();

        change_max_min();
        ans++;
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

void toLeft(int where_x, int start_y, int end_y){ // 4, 7
    // 왼쪽으로 이동만 시킴.
    vector<int> tmp_v;
    int tmp_idx = end_y - start_y+1; // 7 - 4 + 1 = 4 : 이동할 개수

    for (int j = start_y; j < end_y+1; j++) tmp_v.emplace_back(map[where_x][j]); // 4 5 6 7
    for (int j = 0; j < tmp_idx; j++) map[where_x][j] = tmp_v[j]; // 0 1 2 3에 4 5 6 7값을

    for (int j = tmp_idx; j < end_y+1; j++) map[where_x][j] = 0;
}

void fish_plus(){
    // 최솟값들 +1
    for (int j = 0; j < N; j++) if (map[N-1][j] == min_v) map[N-1][j]++;
}

void stacking_left(){
    // 왼쪽값 1개 위에 쌓기
    int tmp_left = map[N-1][0];
    toLeft(N-1, 1, N-1);
    map[N-2][0] = tmp_left;
}

pair<int, int> range_update(){
    int bottom_range = 0, two_plus_range = 0; // 바텀 수조 길이
    
    for (int j = 0; j < N; j++){
        if (high_arr[j] == 0) break;
        if (high_arr[j] >= 2) two_plus_range++;
        bottom_range++;
    }

    return {bottom_range, two_plus_range};
}

void rotation_stacking(bool flag){
    pair<int, int> range_v = {0, 0};
    range_v = range_update(); // bottom_range, two_plus_range

    if (flag){ // 첫 회전-스태킹
        while(true){
            if (range_v.second >= (range_v.first-range_v.second)) break; // 공중부양할거가 공중부양안하고 남은 바닥보다 같거나 클 경우 -> 그만 반복
            vector<vector<int>> v_v;
            
            for (int j = 0; j < range_v.second; j++){ // 공중부양할것들 j값
                vector<int> tmp_v;
                for (int i = N-1; i >= N-high_arr[j]; i--){ // 아래서부터 위로
                    tmp_v.emplace_back(map[i][j]);
                }

                v_v.emplace_back(tmp_v);
            }

            //v_v에서 한칸씩 위로 쌓기
            int tmp_i = 1;
            for (vector<int> tmp_v : v_v){
                for (int j = 0; j < tmp_v.size(); j++){
                    map[N-1-tmp_i][j] = tmp_v[j];
                }
                tmp_i++;
            }

            // 좌밀착 (맨 아래만 하면 됨)
            toLeft(N-1, range_v.second, range_v.first-1);

            // for (int i = N-1; i >= N-range_v.second; i--){
            //     toLeft(i, range_v.second, range_v.first-1); // 2 ~ 7
            // }

            high_arr_update();
            range_v = range_update();
        }
    }else{ // 두번째 회전-스태킹
        for (int k = 2; k <= 4; k+=2){ // N/k
            if (k == 2){
                vector<int> tmp_v;
                for (int j = N/k-1; j >= 0; j--){ // 역순
                    tmp_v.emplace_back(map[N-1][j]);
                }

                toLeft(N-1, N/k, N-1);
                for (int j = 0; j < tmp_v.size(); j++){
                    map[N-2][j] = tmp_v[j];
                }
            }else{ // k == 4 , 5 5 10 9 
                        //.    6 3 10 8
                vector<vector<int>> v_v;
                for (int i = N-2; i <= N-1; i++){
                    vector<int> tmp_v;
                    for (int j = N/k-1; j >= 0; j--){
                        tmp_v.emplace_back(map[i][j]); // 5 5 , 3 6
                    }
                    v_v.emplace_back(tmp_v);
                }

                toLeft(N-1, N/k, (N/2)-1); // 10 9 0 0
                toLeft(N-2, N/k, (N/2)-1); // 10 8 0 0 

                int tmp_i = 1;
                for (vector<int> tmp_v : v_v){
                    for (int j = 0; j < tmp_v.size(); j++){
                        map[N-2-tmp_i][j] = tmp_v[j];
                    }
                    tmp_i++;
                }
            }
        }
    }
}

void fish_num_change(){
    memset(change_map, 0, sizeof(change_map));

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (map[i][j] > 0){
                for (int d = 0; d < 2; d++){ // 우, 하 만 보면 중복 없이 전체 판단 가능
                    int nx = i + dx[d], ny = j + dy[d];
                    if (nx < 0 || ny < 0 || nx >= N || ny >= N) continue;

                    int tmp_d = (abs(map[i][j]-map[nx][ny]))/5;
                    if (tmp_d > 0){
                        if (map[i][j] > map[nx][ny]){
                            change_map[i][j] -= tmp_d;
                            change_map[nx][ny] += tmp_d;
                            continue;
                        }else{
                            change_map[i][j] += tmp_d;
                            change_map[nx][ny] -= tmp_d;
                        }
                    }else continue;
                }
            }else continue;
        }
    }

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            map[i][j] += change_map[i][j];
        }
    }    
}

void make_it_one_line(){
    vector<int> tmp_v;

    for (int j = 0; j < N; j++){
        if (high_arr[j] <= 0) break;

        for (int i = N-1; i >= N-high_arr[j]; i--){
            tmp_v.emplace_back(map[i][j]);
        }
    }
    
    memset(map, 0, sizeof(map));

    for (int j = 0; j < N; j++){
        map[N-1][j] = tmp_v[j];
    }
}

void change_max_min(){
    min_v = 10001, max_v = 0;

    for (int j = 0; j < N; j++){
        min_v = min(min_v, map[N-1][j]);
        max_v = max(max_v, map[N-1][j]);
    }
}

void display_arr(){
    cout << endl;
    for(int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}