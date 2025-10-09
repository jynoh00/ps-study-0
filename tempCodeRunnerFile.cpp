#include <iostream>
#include <stdio.h>
#include <cmath>
#include <vector>
#include <cstring>

#define endl "\n"
#define MAX 64

using namespace std;

int N, Q, dfs_cnt, dfs_sum;
int A[MAX][MAX];
vector<int> L_vec;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
bool isDecrease[MAX][MAX];
bool isVisited[MAX][MAX];
int N_pow;

void input();
void solution();
void decrease_check();
void ice_decrease();
int sumOfIce();
int dfs_big_cnt();
void dfs(int i, int j);

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solution();

    return 0;
}

void input(){
    cin >> N >> Q;
    N_pow = pow(2,N);

    for (int i = 0; i < N_pow; i++){
        for (int j = 0; j < N_pow; j++){
            cin >> A[i][j];
        }
    }

    for (int i = 0; i < Q; i++){
        int tmp_L; cin >> tmp_L;
        L_vec.emplace_back(tmp_L);
    }
}
void solution(){
    for (int L_idx = 0; L_idx < L_vec.size(); L_idx++){
        int L_pow = pow(2, L_vec[L_idx]);

        int repeat = N_pow / L_pow; // x, y로 나누는 개수 : 4

        int x_pos = 0;
        for (int r = 1; r <= repeat*repeat; r++){ // 16번
            pair<int, int> start_node = make_pair(x_pos, 0 + (r-1) * L_pow - (x_pos * repeat));
            if (r % repeat == 0) x_pos += L_pow;

            
            vector<vector<int>> v_v;
            for (int i = 0; i < L_pow; i++){ // 2^L만큼 반복 : pow(2, L_vec[L_idx]), 2
                vector<int> tmp_v;
                for (int j = 0; j < L_pow; j++){
                    tmp_v.emplace_back(A[start_node.first+i][start_node.second+j]);
                }
                v_v.emplace_back(tmp_v);
            }

            for (int i = 1; i <= L_pow; i++){
                for (int j = 0; j < L_pow; j++){
                    A[start_node.first+j][start_node.second+L_pow-i] = v_v[i-1][j];
                }
            }
        }

        decrease_check();
        ice_decrease();
    }

    int sum = sumOfIce();
    int num = dfs_big_cnt();
    cout << sum << endl;
    cout << num << endl;

}

void decrease_check(){
    memset(isDecrease, false, sizeof(isDecrease));

    for (int i = 0; i < N_pow; i++){
        for (int j = 0; j < N_pow; j++){
            if (A[i][j] == 0) continue; // 얼음 없는 칸은 볼 필요 x

            int cnt = 0;
            for (int d = 0; d < 4; d++){
                int nx = i + dx[d], ny = j + dy[d];
                if (nx < 0 || ny < 0 || nx >= N_pow || ny >= N_pow) continue; // 맵 외부

                if (A[nx][ny] > 0) cnt++;
            }

            if (cnt < 3) isDecrease[i][j] = true; // 줄여야 하는 칸.         
        }
    }
}

void ice_decrease(){
    for (int i = 0; i < N_pow; i++){
        for (int j = 0; j < N_pow; j++){
            if (isDecrease[i][j]) A[i][j]--;
        }
    }
}

int sumOfIce(){
    int sum = 0;

    for (int i = 0; i < N_pow; i++){
        for (int j = 0; j < N_pow; j++){
            sum += A[i][j];
        }
    }

    return sum;
}

int dfs_big_cnt(){
    memset(isVisited, false, sizeof(isVisited));

    for (int i = 0; i < N_pow; i++){
        for (int j = 0; j < N_pow; j++){
            if (A[i][j] == 0) isVisited[i][j] = true;
        }
    }

    int ans = 0;
    int sum = -1;

    for (int i = 0; i < N_pow; i++){
        for (int j = 0; j < N_pow; j++){
            if (!isVisited[i][j]){ // 방문 x, 0이 아니어야함.
                dfs_cnt = 0;
                dfs_sum = 0;

                isVisited[i][j] = true;
                dfs(i, j);
                if (dfs_sum > sum){
                    ans = dfs_cnt;
                    sum = dfs_sum;
                }
            }
        }
    }

    return ans;
}

void dfs(int i, int j){
    dfs_cnt++;
    dfs_sum += A[i][j];
    
    for (int d = 0; d < 4; d++){
        int nx = i + dx[d], ny = j + dy[d];
        if (nx < 0 || ny < 0 || nx >= N_pow || ny >= N_pow) continue;
        if (isVisited[nx][ny] == true) continue;
        // if (A[nx][ny] == 0) continue;

        isVisited[nx][ny] = true;
        dfs(nx, ny);
    }
}