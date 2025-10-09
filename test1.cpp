#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> calcu_distance(vector<pair<int, int>>& home_vec, vector<pair<int,int>>& chicken_vec){
    vector<int> distance;
    for (int i = 0; i < home_vec.size(); i++){ // i번째 집
        int d = 0;
        for (pair<int, int> p : chicken_vec){ // 모든 치킨 집까지의 거리 구하기
            int d_tmp = (max(home_vec[i].first, p.first) - min(home_vec[i].first, p.first)) + (max(home_vec[i].second, p.second) - min(home_vec[i].second, p.second));
            if (d == 0){
                d = d_tmp;
            }
            else if (d > d_tmp){
                d = d_tmp;
            }
        }
        distance.emplace_back(d);
    }    

    return distance;
}

int main(){
    int N, M; cin >> N >> M;
    int init_d = 0;
    vector<pair<int, int>> home_vec;
    vector<pair<int, int>> chicken_vec;
    vector<int> distance;

    int map[N][N];
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cin >> map[i][j];
            if (map[i][j] == 1) home_vec.emplace_back(make_pair(i, j));
            else if (map[i][j] == 2) chicken_vec.emplace_back(make_pair(i, j));
        }
    }
    vector<bool> isVisit(chicken_vec.size(), false);

    for (int i = 0; i < home_vec.size(); i++){ // i번째 집
        int d = 0, j = 0, idx = 0;
        for (pair<int, int> p : chicken_vec){ // 모든 치킨 집까지의 거리 구하기
            int d_tmp = (max(home_vec[i].first, p.first) - min(home_vec[i].first, p.first)) + (max(home_vec[i].second, p.second) - min(home_vec[i].second, p.second));
            if (d == 0){
                d = d_tmp;
                idx = j;
            }
            else if (d > d_tmp){
                d = d_tmp;
                idx = j;
            }
            j++;
        }
        distance.emplace_back(d);
        isVisit[idx] = true;
    }

    for (int i : distance) init_d += i;
    
    // k == M
    if (chicken_vec.size() == M){
        cout << init_d;
        return 0;
    }

    // 방문객 0인 치킨집 수 >= 폐업할 치킨집 수
    int false_count = 0;
    for (bool b : isVisit) if (!b) false_count++;
    if (false_count >= (chicken_vec.size() - M)){
        cout << init_d;
        return 0;
    }

    // normal ans
    

    

    // for (pair<int, int> p : home_vec) cout << p.second << " ";




}

/*
14:24


빈칸, 치킨집, 집

(x,y) 1<=

치킨거리 -> 가장 가까운 치킨 집

도시 치킨거리 -> 모든 집의 치킨거리 합

(a, b) - (c, d) => |a-c| + |b-d|


0 2 0 1 0
1 0 1 0 0
0 0 0 0 0
0 0 0 1 1
0 0 0 1 2

0 빈칸, 1 집, 2 치킨



치킨집 폐업하려함, 도시에서 수익을 가장 많이 낼 수 있는 치킨집의 수는 최대 M개
M개를 고르고 나머지 모두 폐업시킴 -> 어떻게 고르면 도시치킨거리가 최소?


5 3 (N = 5, M = 3)
0 0 1 0 0
0 0 2 0 1
0 1 2 0 0
0 0 1 0 0
0 0 0 0 2

M = 2
0 2 0 1 0
1 0 1 0 0
0 0 0 0 0
2 0 0 1 1
2 2 0 1 2

4 - 2 = 2
4개 중 2개 짤 -> 4C2 => 43/21 => 6가지 경우

M = 1
5개 중 4개 짤 -> 5C4 => 5C1 => 5가지 경우

M = 1
10개 중 9개 짤 -> 10C1 => 10가지 경우


2의 개수가 m보다
    크다 -> 차이만큼 없애야 함
        -> 2의 개수를 k, k 중 k-m개를 골라야 함.
            kCk-m => kCm가지 경우 중 d값이 최소인 경우
            1 <= m <= 13, m <= k <= 13 13C6, 13C7이 가장 큼 -> 13 * 2 * 11 * 1 * 3 * 2 / 1  1 1 1 = 26 * 11 * 3 * 2 = 26 * 66 = 1716가지


    같다 -> 현재 도시치킨거리 리턴 (작은 경우 없음)



5 2
0 2 0 1 0
1 0 1 0 0
0 0 0 0 0
0 0 0 1 1
0 0 0 1 2

2
2
2
2
1
1

5 1
1 2 0 0 0
1 2 0 0 0
1 2 0 0 0
1 2 0 0 0
1 2 0 0 0

d = 5
1
1
1
1
1

1
2
3
4
5 => 15

2
1
2
3
4 => 12

3
2
1
2
3 => 11

5 1
1 2 0 2 1
1 2 0 2 1
1 2 0 2 1
1 2 0 2 1
1 2 0 2 1

k > m
    1. 어떤 집도 오지 않는 모든 치킨집 폐업, 이후 치킨집 수와 m이 같으면 리턴 d
    2. 모든 경우 check>?



*/