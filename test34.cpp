// 우수 마을 : 백트래킹 브루트포스 구조로 짰는데, N 최댓값이 10000이라 2^10000가지 경우의 수가 나옴. (선택 or 비선택)
#include <iostream>
#include <stdio.h>

#define endl "\n"
#define MAX 10000

using namespace std;

int N, ans = -1;
int towns[MAX]; // 주민 수
bool selected_towns[MAX]; // 선택된 타운들
vector<int> edges[MAX];

void input();
void solution(int town_idx, int sum);
int max(int a, int b){ return a > b ? a : b; }

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solution(0, 0);
    
    cout << ans << endl;

    return 0;
}

void input(){
    cin >> N;
    for (int i = 0; i < N; i++) cin >> towns[i];
    for (int i = 0; i < N-1; i++){
        int a_town, b_town;
        cin >> a_town >> b_town;
        edges[a_town-1].emplace_back(b_town-1);
        edges[b_town-1].emplace_back(a_town-1);
    }
}

void solution(int town_idx, int sum){
    if (town_idx == N){
        // 우수마을 모두 선정된 상태 -> 3번 조건 실행 불 만족 시 return
        for (int i = 0; i < N; i++){
            if (selected_towns[i] == false){ // 선택 안된 마을은 인접에 1개 이상 우수 마을이 있어야함.
                bool tmp_check = false;
                for (int j = 0; j < edges[i].size(); j++){
                    if (selected_towns[edges[i][j]] == true){
                        tmp_check = true;
                        break;
                    }
                }

                if (tmp_check == false) return;
            }else{ // 선택된 마을일 경우
                bool tmp_check = true;
                for (int j = 0; j < edges[i].size(); j++){
                    if (selected_towns[edges[i][j]] == true){
                        tmp_check = false;
                        break;
                    }
                }

                if (tmp_check == false) return;
            }
        }

        ans = max(ans, sum);
        return;
    }

    solution(town_idx+1, sum);

    // for (int i = town_idx; i < N; i++){
    //     // 선정
    selected_towns[town_idx] = true;
    solution(town_idx+1, sum+towns[town_idx]);
    selected_towns[town_idx] = false;
}

/*
N개의 마을 있음
1~N번

Tree 구조로 이루어짐

마을과 마을을 잇는 N-1개의 길이 있음

무방향 그래프

모든 마을은 연결되어있음
A, B 마을 코스트 1이면 인접

3가지조건: N개의 마을 중 몇개의 마을을 우수 마을로 선정
    1. 우수 마을로 선정된 마을의 주민 수 총합을 최대로 
    2. 우수 마을끼리 인접 불가
    3. 우수마을이 아닌 마을은 적어도 1개 이상의 우수마을과 인접하여야함.

2, 3번을 만족하는 우수 마을 선택 경우의 수 중 1번인 경우의 수가 정답

N: 10000
마을 주민수 <= 10000
for N-1 : edge 추가

*/