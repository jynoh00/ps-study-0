#include <iostream>
#include <stdio.h>
#include <queue> // BFS-queue, DFS-stack

#define MAX 50
#define endl "\n"

using namespace std;

int N, L, R;
int map[MAX][MAX];
bool visited[MAX][MAX]; // 기본값 false
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int days = 0;

queue<pair<int, int>> q;
vector<pair<int, int>> v;

bool flag = true;
int sum = 0;

void input(){
    cin >> N >> L >> R;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            cin >> map[i][j];
        }
    }
}

void bfs(pair<int, int> start_node){
    q.push(start_node);
    visited[start_node.first][start_node.second] = true;

    while (!q.empty()){ // queue가 빌 때 까지 반복
        pair<int, int> tmp = q.front();
        q.pop(); // queue 선입선출 -> front 삭제
       
        for (int i = 0; i < 4; i++){
            int xx = tmp.first + dx[i];
            int yy = tmp.second + dy[i];

            if (xx >= 0 && yy >= 0 && xx < N && yy < N && !visited[xx][yy]){ // 범위안에 있으며 방문하지 않은 노드일 경우
                if (abs(map[xx][yy] - map[tmp.first][tmp.second]) >= L && abs(map[xx][yy] - map[tmp.first][tmp.second]) <= R){
                    q.push(make_pair(xx, yy));
                    visited[xx][yy] = true;

                    v.emplace_back(make_pair(xx, yy));
                    sum += map[xx][yy];
                }
            }
        }
    }
}

void visit_clear(){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            visited[i][j] = false;
        }
    }
}

void calcu(){
    while(flag){ // 연합이 생겨나면 true, 초기값 true <- day의 기준
        flag = false;
        for (int i = 0; i < N; i++){
            for (int j = 0; j < N; j++){
                if (!visited[i][j]){ // visited[i][j]가 false일 경우 : 방문하지 않은 노드
                    v.clear();
                    v.emplace_back(make_pair(i, j)); // 현재 노드 저장
                    sum = map[i][j]; // sum에 현재 노드 인구 수 저장
                    bfs(make_pair(i, j)); // 현재 노드로 bfs 순회
                }

                if (v.size() >= 2){ // bfs 순회 이후 연결된 다른 노드가 존재하는 경우, // visited[i][j]가 true이고 v가 2이상일 경우는 없음.
                    flag = true;
                    for (int i = 0; i < v.size(); i++){
                        map[v[i].first][v[i].second] = sum / v.size(); // 인구 조정
                    }
                }
            }
        }
        if (flag) days++;
        visit_clear();
    }
}

void solution(){
    input();
    calcu();

    cout << days << endl;
}

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    solution();

    return 0;
}

/*
N*N 땅
각 땅에는 나라 존재
A[r][c] = 인구 수
인접나라 국경선 존재 -> 국경선은 정사각형이다.

인구 이동

하루 사이클
    1. 국경선을 공유하는 (거리 차이 1인 나라는) 두 나라의 인구 차이가 L <= <= R이면 국경선 Open
    2. 1 조건을 전체 땅에 적용 모든 열 수 있는 국경선 open

    3. 이동할 수 있는 나라들은 연합이라 함
    4. 연합의 각 칸 인구수는 연합 인구수 / 연합의 칸 개수 (소수점 버림)
    5. 연합 헤체 모든 국경선 off


인구 이동이 며칠동안 이루어지나

MAX 50
1<=N<=50 (50*50), 1<=L<=R<=100
0 <= A[r][c] <= 100

ans <= 2000

2 20 50
50 30
20 40

그냥 구현 문제?


node

0 0 0 0
0 0 0 0
0 0 0 0

1 1 1 0
1 1 0 0
1 0 0 1


3 5 10
10 15 20
20 30 25
40 22 10

00 01 02
10 11 12
20 21 22

R-D 순 순차 확인

00-01 연합
00-10 연합
01-02 연합
    01-11 연합x
02-12 연합
10-11 연합
    10-20 연합x
11-12 연합
11-21 연합
    12-22 연합x
    20-21 연합x
    21-22 연합x

00-01-10-02-12-11-21

1 1 1
1 1 1
1 0 0

10 15 20
20 30 25
40 22 10


00-01
00-10
01-02
02-12
10-11
11-12
11-21


20*20
각 칸마다 Right, Down이 Open인지 pair (true, false)

2연합 -> 합치기 -> 대연합으로

굳이 다 합쳐서 연합 나눠야 결과가 나오나>??

20<=차이<=50

50 30
20 40

구현
그래프 이론
그래프 탐색
시뮬
BFS

*/