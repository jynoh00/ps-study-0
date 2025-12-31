#include <iostream>
#include <stdio.h>
#include <vector>

#define MAX 10001
#define endl "\n"

using namespace std;

int N, ans;
int dp[MAX][2];
int TownNum[MAX];
bool visited[MAX]; // 상위 노드로 이동 방지. dfs check
vector<int> tree[MAX];

void input();
void solution(int now); // dfs

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solution(1);

    cout << ans << endl;

    return 0;
}

void input(){
    int u, v;
    cin >> N;
    for (int i = 1; i <= N; i++){
        cin >> TownNum[i];
    }
    for (int i = 1; i < N; i++){
        cin >> u >> v;
        tree[u].emplace_back(v);
        tree[v].emplace_back(u);
    }
}

void solution(int now){
    visited[now] = true;

    dp[now][0] = 0;
    dp[now][1] = TownNum[now];

    for (int i = 0; i < tree[now].size(); i++){ // 왜 i = 0이 아니지 -> i = 0 맞음
        int nxt = tree[now][i];
        if (visited[nxt]) continue; // 인접 마을이 선택된 마을일 경우 . | 말단 노드일 경우 전부 continue되면서 하단 dp연산 x
        solution(nxt);

        dp[now][0] += max(dp[nxt][0], dp[nxt][1]);
        dp[now][1] += dp[nxt][0];
    }

    if (now == 1) ans = max(dp[now][0], dp[now][1]);
}