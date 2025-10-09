#include <string>
#include <vector>
#include <cstring>

using namespace std;

int max(int a, int b){ return a > b ? a : b; }

int solution(vector<vector<int>> triangle) {
    int answer = 0;
    int height = triangle.size();
    int dp[height][height];
    memset(dp, 0, sizeof(dp));
    
    for (int j = 0; j < height; j++) dp[height-1][j] = triangle[height-1][j];
    
    for (int i = height-2; i >= 0; i--){ // 아래부터
        for (int j = 0; j <= i; j++){
            dp[i][j] = max(dp[i+1][j], dp[i+1][j+1]) + triangle[i][j];
        }
    }    
    answer = dp[0][0];
    
    return answer;
}

/*
50 10 100 20 40
30 50 70 10 60

각 열별로

50  40  200 130 250
30  100 110 210 190

dp[1][1] = scores[1][1];
dp[1][2] = scores[1][2];

dp[1][N] = max(dp[2][N-1], dp[2][N-2]) + scores[1][N];
dp[2][N] = max(dp[1][N-1], dp[1][N-2]) + scores[2][N];

50 -> 50 -> 100 -> 10 -> 40
         -> 20
         -> 10
         -> 40
         -> 60

   -> 100
         -> 
         ->
   -> 70
   -> 20
   -> 10
   -> 40
   -> 60


root 잡고 쭉 계산?
*/