// 이차원 배열과 연산
#include <iostream>
#include <stdio.h>
#include <vector>
#include <cstring>
#include <algorithm>

#define endl "\n"
#define MAX 101 // 0,0 ~ 100,100 이고 0,0버림 1,1 ~ 100,100

using namespace std;

int r, c, k;
int arr[MAX][MAX];
int x_len = 3, y_len = 3; // x행 y열
int ans = 0;
int calcu_arr[MAX] = {0,};

void input(); int solution();
int max(int a, int b){ return a > b ? a : b; }

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    cout << solution() << endl;

    return 0;
}

void input(){
    cin >> r >> c >> k;
    for (int i = 1; i <= 3; i++){
        for (int j = 1; j <= 3; j++){
            cin >> arr[i][j];
        }
    }
}

vector<pair<int,int>> sort_arr(int idx, bool isX){
    vector<pair<int, int>> ans_v; // (빈도수, 숫자) -> 정렬 first기준 동일 -> second기준
    memset(calcu_arr, 0, sizeof(calcu_arr)); // 빈도 수
    
    if (isX) for (int j = 1; j <= y_len; j++) calcu_arr[arr[idx][j]]++;
    else for (int i = 1; i <= x_len; i++) calcu_arr[arr[i][idx]]++;

    for (int i = 1; i < MAX; i++) if (calcu_arr[i] > 0) ans_v.emplace_back(make_pair(calcu_arr[i], i));

    sort(ans_v.begin(), ans_v.end()); // 빈도수 (작 -> 큰) -> 숫자 (작 -> 큰)
    return ans_v;
}

int solution(){
    while(arr[r][c] != k){
        ans++;
        if (ans > 100) return -1;

        if (x_len >= y_len){
            int tmp_yLen = 0;
            for (int i = 1; i <= x_len; i++){
                vector<pair<int, int>> v = sort_arr(i, true);
                
                int j = 1;
                for (pair<int ,int> p : v){
                    if (j > 100) break;
                    arr[i][j] = p.second; arr[i][++j] = p.first;
                    j++;
                }
                
                if (v.size()*2+1 < MAX) for (int j = v.size()*2+1; j < MAX; j++) arr[i][j] = 0;
                tmp_yLen = max(tmp_yLen, v.size()*2);
            }
            y_len = tmp_yLen;
        }else{
            int tmp_xLen = 0;
            for (int j = 1; j <= y_len; j++){
                vector<pair<int, int>> v = sort_arr(j, false);

                int i = 1;
                for (pair<int, int> p : v){
                    if (i > 100) break;
                    arr[i][j] = p.second; arr[++i][j] = p.first;
                    i++;
                }

                if (v.size()*2+1 < MAX) for (int i = v.size()*2+1; i < MAX; i++) arr[i][j] = 0;
                tmp_xLen = max(tmp_xLen, v.size()*2);
            }
            x_len = tmp_xLen;
        }
    }

    return ans;
}

/*
1 2 2

1 2 1
2 1 3
3 3 3

2 1 1 2

1 1 1
1 1 1
1 1 1


1 3
1 3
1 3

1 1 3 1
1 1 3 1
1 1 3 1

1 1 3 1
3 3 3 3


각 행마다 이외 부분 0으로 초기화해야할듯??

*/

/*
크기 3*3 배열 A
1,1 ~ 3,3까지

1s마다 연산 적용
    R연산: 배열 A의 모든 '행'에 대해 정렬 (행의 개수 >= 열의 개수인 경우)
    C연산: 배열 A의 모든 '열'에 대해 정렬 (행의 개수 < 열의 개수인 경우)

한 줄 정렬
    각각의 수가 몇 번 나오는 지
    등장횟수가 커지는 순서로 (작은거부터 -> 큰) : 등장횟수가 동일하면 더 작은 수부터 큰 수로

이후 정렬된 결과를 배열 A에 저장. 수와 등장횟수 모두 넣어서 ex(2, 3) - 숫자 2가 3회

정렬된 결과를 다시 배열에 넣으면 행 or 열의 크기가 달라질 수 있다.
-> 크기가 커지면 0을 채워 넣음 (다른 행or열)
수 정렬 시 0은 무시
3, 2, 0, 0 -> 2, 1, 3, 1

if 행-열 길이가 100 초과 => 100개까지 남기고 나머진 버린다.

A[][]에 들어있는 수와 r, c, k가 주어짐
A[r][c]의 값이 k가 되기 위한 최소 시간

100s 이후에도 변하지 않으면 -1

*/