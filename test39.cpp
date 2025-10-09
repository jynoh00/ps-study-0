// 2*n 타일링2

#include <iostream>
#include <stdio.h>

#define endl "\n"
#define MAX 1001 // 0 1 ~ 1000

using namespace std;

int N;
int dp[MAX]; // 0 1~1000(N최댓값)

void input(){ cin >> N; }
void solution();

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solution();

    return 0;
}

void solution(){
    dp[1] = 1;
    dp[2] = 3;

    for (int i = 3; i <= N; i++) dp[i] = (dp[i-1] + dp[i-2]*2)%10007;

    cout << dp[N] << endl;
}

/*

2*2 => 3가지
2*3 => 2*2가짓수 * 2
2*4 => 2*2가짓수 * 2*2가짓수
2*5 => 2*2가짓수 * 2*2가짓수 * 3
2*6 => 2*2가짓수 * 2*2가짓수 * 2*2가짓수
2*7 => 2*2가짓수 * 2*2가짓수 * 2*2가짓수 * 4
2*8 => 2*2가짓수 * 2*2가짓수 * 2*2가짓수 * 2*2가짓수 = 81개

홀%2 -> 1줄 남음
    3*(홀/4)아님?
짝%2 -> 0줄 남음


1010101 => 4
0000000
0000000

*/