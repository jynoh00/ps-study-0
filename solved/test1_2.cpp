#include <iostream>
using namespace std;

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

}