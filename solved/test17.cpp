// 지름길

#include <iostream>

#define endl "\n"
#define MAX 987654321

using namespace std;

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    int N, D, from, to, dis;
    cin >> N >> D;
    vector<int> map(D+1, MAX);
    vector<pair<int, int>> sc[10001];
    
    for (int i = 0; i < N; i++){
        cin >> from >> to >> dis;
        sc[to].emplace_back(make_pair(from, dis));
    }
    
    map[0] = 0;
    for (int i = 1; i <= D; i++){
        if (sc[i].size() == 0) map[i] = map[i-1]+1; // 숏컷 존재 x -> 1추가
        else{
            for (pair<int, int> p : sc[i]){
                map[i] = min(map[i], min(map[i-1]+1, map[p.first]+p.second)); // min(그냥+1 , 숏컷[n개 중 1개] 활용)
            }
        }
    }
    
    cout << map[D] << endl;
}

/*
노드 연결해서
모든 노드 연결 경우의 수 구해야 함
그 중에 가장 작은 값 리턴

노드 연결 조건은 앞 원소 destination이 뒤 원소 source 보다 같거나 작아야 함.
재귀로 전체 조합 구하고 매번 min() 함수로 결과값 갱신 (결과값은 전역변수 부분에 선언할 것)


--

최단경로, 다익스트라 알고리즘 사용
기억이 안나는디요..

일단 내 풀이로 하고 이후 다익스트라 사용 코드 보고 분석ㅌ

*/