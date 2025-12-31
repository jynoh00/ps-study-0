// LIS Algorithm (최장증가수열) - Longest Increasing Subsequence

#include <iostream>

using namespace std;

int arr[8] = {0, 20, 40, 30, 50, 10, 80, 70}; // 1 ~ 7만
int dp[8];

void LIS_ALGORITHM(int N);

int main() {
    LIS_ALGORITHM(7);
}

void LIS_ALGORITHM(int N) {
    int max = 1;
    for (int i = 1; i <= N; i++) {
        dp[i] = 1;
        for (int j = 1; j < i; j++) { // i 왼쪽 원소들
            if (arr[j] < arr[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                max = max < dp[i] ? dp[i] : max;
            }
        }
    }

    cout << max << endl;
}