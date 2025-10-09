// 퇴사
#include <iostream>
#include <vector>
#include <stdio.h>

#define endl "\n"
#define MAX 15

using namespace std;

int N;
int ans = 0, sum = 0, today = 0;
pair<int, int> arr[MAX];
vector<vector<int>> vec;
bool _select[MAX];

int max(int a, int b){ return a >= b ? a : b; }

void input(){
    cin >> N;
    for (int i = 0; i < N; i++){
        int Ti, Pi; cin >> Ti >> Pi;
        arr[i] = make_pair(Ti, Pi);
    }
}

int calcu_money(){
    vector<int> test_v;
    int ans_tmp = 0;
    for (int i = 0; i < MAX; i++){
        if (_select[i]){
            ans_tmp += arr[i].second;
            test_v.emplace_back(i);
        }
    }
    cout << "ans_tmp: " << ans_tmp << endl;
    vec.emplace_back(test_v);
    return ans_tmp;
}

void calcu(int idx){
    today += idx;
    if (sum == N && ((today + arr[idx].first) <= N)){
        sum -= arr[idx].first;
        today -= arr[idx].first;
        ans = max(ans, calcu_money());
        return;
    }

    if (sum > N && ((today + arr[idx].first) <= N)){
        _select[idx] = false;
        sum -= arr[idx].first;
        today -= arr[idx].first;
        ans = max(ans, calcu_money());
        return;
    }

    for (int i = idx; i < N; i++){
        if (_select[i]) continue;

        _select[i] = true;
        sum += arr[i].first;
        calcu(i+arr[i].first);
        _select[i] = false;
    }
}

void solution(){
    input();
    calcu(0);

    cout << ans << endl;
}

int main(){
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    solution();

    return 0;
}

/*

오늘부터 N+1일째 되는 날 퇴사를 원함

남은 N일 동안 최대한 많은 상담하려 함

하루에 하나씩 서로다른 사람의 상담을 잡음

각 상담은 걸리는 시간 Ti
        받을 수 있는 금액 Pi
    -> pair

ex N = 7
(3, 10) (5, 20) (1, 10) (1, 20) (2, 15) (4, 20) (2, 200)

걸리는 시간은 일 수

최대 금액 1일 4일 5일 상담

Ti 총합을 N이 되게
Pi가 많게

##최대 수익 구하기


조합 문제
1 ~ 15번

각 시간 합이 <= N인, 15개 중 x개 선택 경우의 수
-> 이 중 최대 수익 max값 구하기


Ti


tlqkf

*/