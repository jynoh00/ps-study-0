// 파일 합치기
#include <iostream>
#include <stdio.h>
#include <vector>
#include <cstring>

#define endl "\n"
#define MAX 501

using namespace std;

int T;
vector<vector<int>> testDatas;
int cost_dp[MAX][MAX]; // idx가 장, dp[i][j]는 i~j장의 코스트, dp[i][i]는 i장의 코스트
int sum[MAX];

void input();
int solution(int test_idx);
int min(int a, int b){ return a < b ? a : b; }

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    vector<int> ans_v;
    for (int i = 0; i < testDatas.size(); i++){
        int ans = solution(i);
        ans_v.emplace_back(ans);
    }

    for (int i : ans_v) cout << i << endl;

    return 0;
}

void input(){
    cin >> T;
    for (int i = 0; i < T; i++){
        int data_cnt; cin >> data_cnt;
        vector<int> tmp_v;
        for (int j = 0; j < data_cnt; j++){
            int tmp_data; cin >> tmp_data;
            tmp_v.emplace_back(tmp_data);
        }
        testDatas.emplace_back(tmp_v);
    }
}

int solution(int test_idx){
    memset(cost_dp, 0, sizeof(cost_dp));
    memset(sum, 0, sizeof(sum));
    int N = testDatas[test_idx].size();

    for (int i = 1; i <= N; i++){ // init
        sum[i] = testDatas[test_idx][i-1] + sum[i-1];
        cost_dp[i][i] = 0;
    }

    for (int len = 2; len <= N; len++){
        for (int i = 1; i+len-1 <= N; i++){
            int j = i + len - 1;
            cost_dp[i][j] = 1e9;

            for (int m = i; m < j; m++){
                cost_dp[i][j] = min(cost_dp[i][j], cost_dp[i][m] + cost_dp[m+1][j] + sum[j] - sum[i-1]);
            }
        }
    }

    return cost_dp[1][testDatas[test_idx].size()]; // 1 ~ K장까지
}

/*

소설가

chapter로 나누어서 소설을 씀

각 장은 각각 다른 파일
다 쓰고 한 파일로 합침

합치는 과정
    - 두 개의 파일을 합쳐서 하나의 임시파일로 이 임시파일이나 원래의 파일을 계속 두 개씩 합쳐 소설의 여러 장들이 연속이 되도록 합침
    - 최종적으로 1개으 ㅣ파일
    - 두 파일을 합치는 비용 두 파일 크기의 합
    - 최종 완성 파일


*/