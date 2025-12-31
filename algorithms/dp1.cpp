#include <iostream>
#include <stdio.h>

#define endl "\n"
#define MAX 1500002 // 1 ~ 1500000

using namespace std;

int N;
pair<int, int> tp_pair[MAX];
long long dp[MAX];

long long max(long long a, long long b) {return a > b ? a : b; }
void input();
void solve();

int main() {
    cin.tie(NULL);
    cout.tie(NULL);

    ios_base::sync_with_stdio(false);

    input();
    solve();

    return 0;
}

void input() {
    cin >> N;
    for (int i = 1; i <= N; i++) {
        int Ti, Pi;
        cin >> Ti >> Pi;
        
        tp_pair[i] = make_pair(Ti, Pi);
    }
}

void solve() {
    int nowImYoung = N+1;
    if (tp_pair[N].first == 1) {
        dp[N] = tp_pair[N].second;
        nowImYoung = N;
    }else dp[N] = 0;

    for (int i = N-1; i > 0; i--) {
        if (tp_pair[i].first + i - 1 < nowImYoung) { // 이어서 가능한 경우 (최선)
            dp[i] = dp[i+1] + tp_pair[i].second;
            nowImYoung = i;

            continue;
        }

        int a_data = 0;

        if (tp_pair[i].first + i - 1 <= N) { // tp_pair[i].second + dp[tp_pair[i].first + i - 1]
            a_data = tp_pair[i].second + dp[tp_pair[i].first + i];
        }

        if (a_data > dp[i+1]) nowImYoung = i;

        dp[i] = max(a_data, dp[i+1]);
    }

    cout << dp[1] << endl;
}

    // dp[6] + dp[7]이 가능하면 무조건 이걸로
    // 불가능하면 max(dp[6], dp[7])로 (dp[6]이 불가능할 수도 있음. -> 불가능하면 0으로 하면 자동으로 max 처리)

    // dp[6], dp[7], dp[6] + dp[7]

    /*
    마지막 날부터 dp 역 계산
    
    N = 7
    dp[7] = money[7] + 0 // money[]는 0일 수 있음 (불가능한 경우)
    dp[6] = (dp[7] + money[6], money[6]) // money[6]또한 0일 수 있음
    

    
    */

/*
퇴사2

N+1일째 되는날 퇴사하기위해

N일동안 일을 많이 하려함

최대한 많은 상담 -> 아니잖아 ㅅㅂ

Ti 걸리는 기간
Pi 받는 금액

최대 수익을 얻고 싶음


1000 * 1500000000

*/