// 지름길
#include <iostream>
#include <stdio.h>
#include <vector>

#define MAX 12
#define MAX_NUM 99999999
#define endl "\n"

using namespace std;

int N, D;
int from, to, cost;
vector<int> map(10001, MAX_NUM); // 0 ~ 10000까지 인덱스를 MAX_NUM으로 초기화
vector<pair<int, int>> sc[10001]; // sc[to]안에 pair<int, int>들이 벡터로 존재

int min(int a, int b){ return a < b ? a : b; }
void input();
void solution();

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solution();

    cout << map[D] << endl;

    return 0;
}

void input(){
    cin >> N >> D;
    for (int i = 0; i < N; i++){
        cin >> from >> to >> cost;
        sc[to].emplace_back(make_pair(from, cost));
    }
}

void solution(){
    map[0] = 0; // 시작점
    for (int i = 1; i <= D; i++){ // 전체 i번째 길까지 가는 최단거리를 계산
        if (sc[i].size() == 0){ // 벡터 원소 존재 x (숏컷x)
            map[i] = map[i-1]+1; 
            continue;
        }

        for (pair<int, int> p : sc[i]){ // 숏컷 존재 -> 해당 i로 가는 (i = to) 전체 숏컷 분석
            map[i] = min(map[i], min(map[i-1]+1, map[p.first]+p.second));
        }
    }
}

