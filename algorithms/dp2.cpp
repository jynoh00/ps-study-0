// 가장 긴 감소하는 수열 -> roQkrdlsep;; dho rhfemqhek djfuqwl
// LIS Algorithm
#include <iostream>
#include <stdio.h>
#include <deque>

#define endl "\n"
#define MAX 1001 // 1~1000

using namespace std;

int N, A[MAX], dp[MAX];

void input();
int solve();

int main() {
    cin.tie(NULL);
    cout.tie(NULL);

    ios_base::sync_with_stdio(false);

    input();
    cout << solve() << endl;

    return 0;
}

void input() {
    cin >> N;
    for (int i = 1; i <= N; i++) cin >> A[i];
}

int solve() {
    int max = 1;
    for (int i = 1; i <= N; i++) {
        dp[i] = 1;
        for (int j = 1; j < i; j++) {
            if (A[j] > A[i] && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                max = max < dp[i] ? dp[i] : max;
            }
        }
    }

    return max;
}