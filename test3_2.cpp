// 퇴사

// 반대편에서부터 계산
// DP
#include <iostream>
#include <stdio.h>

#define endl "\n"
#define MAX 16

using namespace std;

int N, ans;
pair<int, int> arr[MAX];
int res[MAX] = {0,};

int max(int a, int b){ return a >= b ? a : b; }

void input(){
    cin >> N;
    for (int i = 1; i <= N; i++){
        int Ti, Pi;
        cin >> Ti >> Pi;
        arr[i] = make_pair(Ti, Pi);
    }
}

void calcu(){
    int deadline;
    for (int i = N; i > 0; i--){
        deadline = i + arr[i].first;
        if (deadline > (N+1)){
            res[i] = res[i+1]; // can't
        }else{
            res[i] = max(res[i+1], res[deadline] + arr[i].second);
        }
    }
}

void solution(){
    input();
    calcu();

    ans = res[1];
}

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    solution();

    cout << ans << endl;
    
    return 0;
}