// 치킨 배달

#include <stdio.h>
#include <vector>
#include <iostream>

#define MAX 50
#define endl "\n"

using namespace std;

int answer, N, M, chicken_num;
int map[MAX][MAX];
bool _select[13];
vector<pair<int, int>> house, chicken, vec;

int min(int a, int b){ return (a > b) ? b : a; }
void solve();
void input();
void solution();
void select_chicken(int idx, int cnt);
int calculate_distance();

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
    
    solve();

    return 0;
}

void solve(){
    input();
    solution();
}

void input(){
    answer = 99999999;
    cin >> N >> M;

    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cin >> map[i][j];
            if (map[i][j] == 1) house.emplace_back(make_pair(i, j));
            else if (map[i][j] == 2) chicken.emplace_back(make_pair(i, j));
        }
    }
    chicken_num = chicken.size();
}

void solution(){
    select_chicken(0, 0);
    cout << answer << endl;
}

void select_chicken(int idx, int cnt){
    if (cnt == M){
        answer = min(answer, calculate_distance());
        return;
    }

    for (int i = idx; i < chicken_num; i++){
        if (_select[i] == true) continue;
        
        _select[i] = true;
        vec.emplace_back(chicken[i]);
        select_chicken(i, cnt + 1);
        _select[i] = false;
        vec.pop_back();
    }
}

int calculate_distance(){
    int sum = 0;
    for (int i = 0; i < house.size(); i++){
        int x = house[i].first, y = house[i].second;
        int d = 99999999;

        for (int j = 0; j < vec.size(); j++){
            int xx = vec[j].first;
            int yy = vec[j].second;
            int dist = abs(xx - x) + abs(yy - y);

            d = min(d, dist);
        }

        sum += d;
    }
    
    return sum;
}


/*
전개

main -> solve() ->
                    input()
                    solution() ->
                                    select_chicken() ->
                                                        calculate_distance()
                                                        select_chicken() #재귀함수

solution() : cunt << answer << endl;

5 3
0 0 1 0 0
0 0 2 0 1
0 1 2 0 0
0 0 1 0 0
0 0 0 0 2

chicken( {1, 2}, {2, 2}, {4, 4} )

select_chicken(0, 0)
    select{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    vec{{1, 2}}
select_chicken(0, 1)
    select{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    vec{{1, 2}, {2, 2}}
select_chicken(1, 2)
    select{1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    vec{{1, 2}, {2, 2}, {4, 4}}
select_chicken(2, 3)
    answer = min(answer, calculate_distance())
    return
select_chicken(1, 2)
    select{1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    vec{{1, 2}, {2, 2}}
    i >= chicken_num 
select_chicken(0, 1)
    select{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    vec{{1, 2}}
    select{1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    vec{{1, 2}, {}}
*/