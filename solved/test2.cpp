// 시험 감독
#include <iostream>
#include <stdio.h>

#define MAX 1000000
#define endl "\n"

using namespace std;

int N, B, C;
int A[MAX];
long long ans = 0; // ans가 int값을 벗어날 수 있음 -> long long rotlqkf


void solution();
void input();
void calcu();

int main(){
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    solution();

    return 0;
}

void solution(){
    input();
    calcu();

    cout << ans << endl;
}

void input(){
    cin >> N;
    ans += N;
    for (int i = 0; i < N; i++){
        cin >> A[i];
    }
    cin >> B >> C;
}

void calcu(){
    for (int i = 0; i < N; i++){
        if ((A[i] - B) <= 0) continue;
        if (A[i] == 0) break;
        ans += (A[i] - B)%C == 0 ? (A[i]-B)/C : (A[i]-B)/C + 1;
    }
}


/*

N개의 시험장
i번 시험장 응시자의 수 Ai

감독관 1. 총감독, 2. 부감독
    1 -> 관리 응시자 수 B
    2 -> 관리 응시자 수 C

각 시험장 총감독 1명만, 부감독 여러명 가능
    -> 없어도 되나 부감독?

필요한 감독관 수(총감독 수 + 부감독 수)의 최솟값


1 <= N <= 1000000


총감독관 N명

A[i] - N <= 0 -> 부감독 필요 x
else 한 교실 필요 부감독 = (A[i] - B)%C + 1

*/