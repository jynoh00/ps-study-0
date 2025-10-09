// 테트로미노

#include <iostream>

#define MAX 500
#define endl "\n"

using namespace std;

int N, M;
int map[MAX][MAX]; // 0,0 ~ N-1,M-1까지
int ans = -1;
bool isVisited[MAX][MAX];

int dx[] = {0, 0, 1, -1}; // 동 서 남 북
int dy[] = {1, -1, 0, 0};

int max(int a, int b){return a > b ? a : b; }
void input();
void solution(pair<int, int> p, int sum, int cnt);
void extra_solution(int x, int y);

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();

    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            solution(make_pair(i, j), map[i][j], 1);
            extra_solution(i, j);
        }
    }

    cout << ans << endl;

    return 0;
}

void input(){
    cin >> N >> M;
    for (int i = 0; i < N; i++){
        for (int j = 0; j < M; j++){
            cin >> map[i][j];
        }
    }
}

void solution(pair<int, int> p, int sum, int cnt){
    int x = p.first, y = p.second;

    if (cnt == 4){
        ans = max(ans, sum);
        return;
    }

    isVisited[x][y] = true;

    for (int d = 0; d < 4; d++){
        int nx = x + dx[d], ny = y + dy[d];
        if (nx >= 0 && ny >= 0 && nx < N && ny < M && isVisited[nx][ny] == false){ // 맵 안
            solution(make_pair(nx, ny), sum + map[nx][ny], cnt+1);
        }
    }

    isVisited[x][y] = false;
}

void extra_solution(int x, int y){ // ㅗ
    int center = map[x][y];
    int wings[4]; // 상하좌우
    int wing_cnt = 0;

    for (int d = 0; d < 4; d++){
        int nx = x + dx[d], ny = y + dy[d];
        if (nx >= 0 && ny >= 0 && nx < N && ny < M){
            wings[wing_cnt++] = map[nx][ny];
        }
    }

    if (wing_cnt < 3) return; // 구석 (모양 불가)

    int total = center;
    for (int i = 0; i < wing_cnt; i++) total += wings[i]; // 모든 날개 값 + 본인 값

    if (wing_cnt == 3){ // 벽면
        ans = max(ans, total);
    }else{ // wing_cnt == 4
        for (int i = 0; i < 4; i++){
            ans = max(ans, total-wings[i]);
        }
    }
}

// 일케하면 선형적으로만 4칸 확장 가능함. ㅗ 모양을 할 수가 없어
// ㅗ 모양 검사 추가 함수 생성

// void bfs(){

// }

/*

정사각형 4개 붙인걸 테트로미노

1       2

1111    11
        11

3       4           5

1       1           111
11      1            1
 1      11

5개

1번의 경우
첫 시작 위치에서 4가지

2번의 경우
첫 시작 위치에서 4가지

3번의 경우
첫 시작 위치에서 ㅈㄴ 많아

4번 ㅈㄴ 많아
5번 ㅈㄴ 많아 ㅅㅂ


개어려운데 이거

동일한 조건은 4개를 고르는거

걍 연속된 4개 고르면 저 중에 하나가 무조건 되지 않나?
-> ㅈㄴ 일리있어

걍 N*M개 중에 4개를 고르고 그 합이 가장 큰 경우 max()로
-> 조합(재귀)-max() 활용

N*M인 종이 위에 
테트로미노 1개를 놓으려 함

테트로미노 1개를 놓아서 안에 쓰인 정수의 합이 가장 큰 결과

1111

1
1
1
1

2개



*/