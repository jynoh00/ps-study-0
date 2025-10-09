// 경사로
#include <iostream>
#include <stdio.h>
#include <vector>
#include <cstring>

#define endl "\n"
#define MAX 100

using namespace std;

int N, L, ans = 0;
int map[MAX][MAX]; // 0,0 ~ N-1,N-1

void solution();
void input();
bool isCan(int arr[]);

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solution();

    return 0;
}

bool isCan(int arr[]){ // 한 행(좌 -> 우) or 한 열(위 -> 아래)
    int p_size = 0;
    pair<int, int> p[N];
    bool isVisited[N];
    vector<int> v_idx;
    memset(isVisited, false, sizeof(isVisited));
    cout << endl;

    int tmp_cnt = 1;
    int tmp_num = arr[0];
    v_idx.emplace_back(0);
    int idx_cnt = 0;

    for (int i = 1; i < N; i++){
        if (arr[i] == tmp_num){
            tmp_cnt++;

            if (i == N-1){
                p[p_size] = make_pair(arr[i], tmp_cnt);
            }
        }
        else{ // 일치x
            p[p_size] = make_pair(tmp_num, tmp_cnt);
            
            if (i == N-1){ // 마지막 원소 (이고 일치도 안 함)
                p[p_size] = make_pair(arr[i], 1);
            }

            tmp_num = arr[i];
            tmp_cnt = 1;

            p_size++;
            v_idx.emplace_back(idx_cnt);
        }
        idx_cnt++;
    }

    if (p_size == 0) return true; // 가능, 모두 같은 높이
   
    // for (int i = 0; i <= p_size; i++){
    //     cout << p[i].first << "," << p[i].second << endl;
    // }
    
    for (int i = 0; i <= p_size; i++){ // 앞 뒤 원소 차이
        if (i == p_size) continue; // 마지막 원소 패스

        if (abs(p[i].first - p[i+1].first) >= 2){
            return false; // 2칸 차이는 안됨. // cmath? // algorithm?
        }

        if (p[i].first > p[i+1].first){ // 앞 원소가 더 큰 경우
            if (p[i+1].second >= L){
                for (int j = 0; j < L; j++){
                    if (isVisited[v_idx[i+1]+j*1] == true){
                        return false;
                    }
                    isVisited[v_idx[i+1]+j*1] = true;
                }
            }else{
                return false; // 경사로 설치 불가
            }
        }else{ // 뒤 원소가 더 큰 경우 (같을 경우는 없음)
            if(p[i].second >= L){
                for (int j = 0; j < L; j++){
                    if (isVisited[v_idx[i]+j*1] == true){
                        return false;
                    }
                    isVisited[v_idx[i]+j*1] = true;
                }
            }else{
                return false;
            }
        }
    }

    return true;
}

void solution(){
    for(int i = 0; i < N; i++){ // 가로 행, x
        int x_arr[N];
        for (int j = 0; j < N; j++){
            x_arr[j] = map[i][j];
        }

        if (isCan(x_arr)) ans++;
    }

    for (int j = 0; j < N; j++){ // 세로 열, y
        int y_arr[N];
        for (int i = 0; i < N; i++){
            y_arr[i] = map[i][j];
        }

        if (isCan(y_arr)) ans++;
    }

    cout << ans << endl;
}

void input(){
    cin >> N >> L;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cin >> map[i][j];
        }
    }
}

/*
진짜 구현 다함. 진ㅉ라로


*/


/*
크기 N*N인 지도
각 칸에는 그 곳의 높이

지나갈 수 있는 길이 몇 개 인지

길: 한 열 or 한 행 전체 (한쪽 끝에서 다른쪽 끝까지)

1. 길을 지나가려면 모든 칸의 높이가 같아야 함.
2. 경사로를 놓아 지나갈 수 있게 만들어야함.
    경사로는 높이가 항상 1
    길이는 L
    개수 상관 x

경사로는 낮은 칸에 놓으며
L개의 연속 칸이 동일 높이여야 함 (바닥에 다 맞닿아야 함)
연결하려는 높이차는 1이어야함

지나갈 수 있는 길의 개수 리턴 (왜 최대가 아니지?? )

*/