# 코딩 테스트 문제 풀이 및 주요 내용 정리
> [https://www.acmicpc.net/workbook/view/1152](https://www.acmicpc.net/workbook/view/1152)

본 레포지토리는 백준 온라인 저지 문제를 해결하면서 학습한 알고리즘과 핵심 개념을 정리하기 위한 공간으로,

- 문제 해결 과정에서 사용된 알고리즘
- 구현 시 유의해야 할 점
- 시간 복잡도 및 한계성
- 대안적 접근 방법

과 같은 내용을 위주로 회고하여 이후 복습과 참고 자료로 활용할 수 있도록 구성되었습니다. 풀이 과정에서 새롭게 알게 된 문법, 표준 라이브러리, 실수하기 쉬운 포인트 또한 함께 정리하여 CS 역량 강화 및 알고리즘 접근성 향상을 목표로 합니다.

![Language](https://img.shields.io/badge/Language-C++-blue)

## 주요 내용 정리

### 📌 목차

- [1. 재귀함수를 이용한 DFS 알고리즘](#1-재귀함수를-이용한-dfs-알고리즘)
- [2. DFS 완전 탐색의 한계와 DP를 통한 해결 과정](#2-dfs-완전-탐색의-한계와-dp를-통한-해결-과정)


### 1. 재귀함수를 이용한 DFS 알고리즘

`DFS(깊이 우선 탐색)`는 완전 탐색 알고리즘 중 하나로, 루트 노드에서 시작하여 다음 분기로 넘어가기 전에 `해당 분기 전체`를 완벽하게 탐색한다.

자기 자신을 호출하는 순환 알고리즘의 형태를 가진다. 특징으로는 `stack` 자료구조를 통해 주로 구현되며, 그래프를 탐색하며 방문한 노드의 기존 방문 여부를 반드시 검사해야 한다는 것이 있다.

```c++
template <class Type, class Container= deque <Type>>
class stack
```
```c++
void push(const Type& val);
void pop();

reference top();
const_reference top() const;

size_type size() const;

bool empty() const;
```
- C++ 표준 라이브러리, `<stack>` 헤더

자기 자신을 호출하는 순환 알고리즘이란 점에서 이를 재귀함수를 통해서 구현이 가능하다. 다음 `/solved/test20.cpp` 코드의 일부 함수를 토대로 이를 확인할 수 있다.

```c++
void solution(pair<int, int> p, int sum, int cnt){
    int x = p.first, y = p.second;

    if (cnt == 4){
        ans = max(ans, sum);
        return;
    }

    isVisited[x][y] = true;

    for (int d = 0; d < 4; d++){
        int nx = x + dx[d], ny = y + dy[d];
        if (nx >= 0 && ny >= 0 && nx < N && ny < M && isVisited[nx][ny] == false){
            solution(make_pair(nx, ny), sum + map[nx][ny], cnt+1);
        }
    }

    isVisited[x][y] = false;
}
```

`if` 조건문을 통한 종료 조건과 함께, `for`문을 순회하며 전체 노드를 탐색한다.<br>
이후 다음 노드의 위치 좌표가 담긴 `pair`쌍을 인자로 하며, 재귀함수의 종료 조건이 될 `cnt`값을 증가한 후, 결과값을 업데이트하여 함께 전달한다.

```c++
solution(make_pair(nx, ny), sum + map[nx][ny], cnt+1);
```

조건문 내부에서 기존 방문 여부를 확인하는 `isVisited` bool 타입 배열을 사용하여 중복 노드 방문을 방지하도록 하였다.

```c++
isVisited[nx][ny] == false
```

결과적으로 조건에 맞는 모든 경우의 수를 DFS 방식으로 탐색하여 최적의 값을 `ans` 변수에 저장하여 문제를 해결하였다.<br>
이러한 재귀함수를 구현할 때 주의 깊게 확인할 점은
- 인자로 `종료 조건`을 확실하게 전달하여야 하며
- 결과값에 해당하는 정보를 탐색의 분기마다 확인하여야 하기에 또한 인자로 `분기 결과값`을 전달해야한다.
- DFS 탐색의 특성상 `방문 여부` 역시 반드시 확인하여야 한다.

본 방식은 `브루트포스` 알고리즘으로 전체 경우의 수를 모두 확인하기에, 노드의 수가 많다면 `시간복잡도`가 커져 문제가 될 수 있다 생각한다. 시간복잡도를 고려해야 하는 경우 BFS(너비 우선 탐색) 방식 혹은 DFS 탐색에 백트래킹을 결합한 방식을 활용하는 것이 적합하다는 결론을 내었다.

<br>

### 2. DFS 완전 탐색의 한계와 DP를 통한 해결 과정

[1. 재귀함수를 이용한 DFS 알고리즘](#1-재귀함수를-이용한-dfs-알고리즘)에서 논했듯이 DFS 완전 탐색을 이용한 문제 해결은 방문할 노드의 수가 많아지면 시간적 한계에 부딪힌다. 아래 `/solved/test28.cpp` 코드의 재귀 DFS 코드를 통해 이를 확인할 수 있었다.

```c++
void solution(int selected_homes, int cost_sum, int before_idx, int after_idx, int home_one_idx){
    if (selected_homes == N){
        ans = min(ans, cost_sum);
        return;
    }

    int i = selected_homes;
    for (int j = 0; j < 3; j++){
        if (i == N-1) after_idx = home_one_idx;
        if (j == before_idx || j == after_idx) continue;
        if (i == 0) home_one_idx = j;

        solution(selected_homes+1, cost_sum+homes[i][j], j, after_idx, home_one_idx);
    }
}
```

- `재귀함수`를 사용한 DFS 풀이

해당 문제에서 방문하고자 하는 노드는 N개이며, N은 `2 <= N <= 1,000`의 범위를 입력값으로 한다.<br>
전체 집은 연결된 원순열 형태를 만족하기에 기존 방문 여부는 측정하지 않고 선택된 노드의 수를 계산하여 DFS의 무한 루프를 방지하였다.<br>

`solution` 함수의 시간복잡도를 살펴보면, <br>
- 첫 노드에 해당하는 집에서 3가지 색을 칠하는 경우의 수가 존재하며 (3가지 분기)
- 이후 N-1개의 집을 색칠하는 경우의 수는 2가지이다. (2가지 분기)

따라서 최대 탐색 경우의 수는 

```math
3*2^(N-1)
```

즉 시간복잡도는

```math
O(3*2^(N-1)) ~= O(2^N)
```


N이 최댓값인 `1,000`일 경우, 모든 경우의 수는 `3*2^999` ~= `2^1000` = `1.07*10^301`개가 된다.

전 우주 원자의 수로 추정되는 `10^80`보다도 훨씬 큰 탐색량이기에 DFS 풀이로는 문제를 해결하기에 시간적 한계가 생긴다.


```c++
...

// 전역
int dp[MAX][3];

...

void solution(){
    for (int first = 0; first < 3; first++){
        for (int j = 0; j < 3; j++){
            if (j == first) dp[0][j] = costs[0][j];
            else dp[0][j] = 1000000000;
        }

        for (int i = 1; i < N; i++){
            dp[i][0] = min(dp[i-1][1], dp[i-1][2]) + costs[i][0]; 
            dp[i][1] = min(dp[i-1][0], dp[i-1][2]) + costs[i][1]; 
            dp[i][2] = min(dp[i-1][0], dp[i-1][1]) + costs[i][2]; 
        }

        for (int last = 0; last < 3; last++){
            if (last == first) continue;
            ans = min(ans, dp[N-1][last]);
        }
    }
}
```

- `DP(Dynamic Programming, 동적계획법)` 점화식 활용 풀이

<br>

위 코드는 동일 문제를 DP를 활용하여 풀이한 `solution` 함수이다.

`dp[i][j]` 이차원 배열에서 `i`는 노드(집)의 번호를, `j`값은 노드에서 선택 가능한 3가지 경우의 수를 의미한다.<br>

DP를 통해 문제를 해결하기 위해 다음과 같은 조건을 생각하였다.

1. 특정 집 `i` 노드에 색을 `R, G, B` 중 1개를 선택하는 최소 비용을 구한다.
2. 비용을 구할 때, 이전 집 `i-1`의 선택 비용 중 다른 두 가지 비용의 최솟값을 구한다.
3. 선택한 색을 `i`에 칠하는 비용과 `2`번에서 구한 비용의 합이 `i`에서 특정 색을 칠하는 비용의 최솟값이 된다.

<br>

이를 점화식으로 표현해보면 아래와 같이 구할 수 있다.

```math
DP[i][x] = min(DP[i-1][y], DP[i-1][z]) + COST[i][x]
```

```math
DP[i][y] = min(DP[i-1][x], DP[i-1][z]) + COST[i][y]
```

```math
DP[i][z] = min(DP[i-1][x], DP[i-1][y]) + COST[i][z]
```

`x, y, z`는 3가지 색을 의미하며 이전 노드에서의 최솟값을 활용해 연산을 진행한다.

```c++
for (int i = 1; i < N; i++){
    dp[i][0] = min(dp[i-1][1], dp[i-1][2]) + costs[i][0]; 
    dp[i][1] = min(dp[i-1][0], dp[i-1][2]) + costs[i][1]; 
    dp[i][2] = min(dp[i-1][0], dp[i-1][1]) + costs[i][2]; 
}
```

<br>

추가로 초기값을 설정하기 위해, 최초 노드에서는 선택한 색만을 유효하게 두고 <br>
다른 2가지의 색들은 매우 큰 값으로 하여 `min` 연산 과정에서 선택될 수 없게 하였다.

```math
DP[0][p] = COST[0][p]
```

```math
DP[0][q] = INF
```

`q`는 임의의 색 `p`를 제외한 2가지의 색을 의미한다.

```c++
for (int first = 0; first < 3; first++){
        for (int j = 0; j < 3; j++){
            if (j == first) dp[0][j] = costs[0][j];
            else dp[0][j] = 1000000000;
        }
    
    ...
```

<br>

`N-1`번째 노드와 `0`번째 노드의 색을 비교하여 (동일 색을 선택한 경우 제외), 가능한 비용 중 최솟값이 구하고자 하는 정답이 된다. 

```math
ANS = min(ANS,DP[N-1][LAST])
```

```c++
for (int last = 0; last < 3; last++){
    if (last == first) continue;
    ans = min(ans, dp[N-1][last]);
}
```

<br>

결과적으로 `DP`를 활용한 `solution` 함수의 구조는 다음과 같다.
```c++
for (int first = 0; first < 3; first++) {     // 3번 반복
    ...
    for (int i = 1; i < N; i++) {             // N-1 ≈ N 번 반복
        dp[i][0] = ...
        dp[i][1] = ...
        dp[i][2] = ...
    }

    for (int last = 0; last < 3; last++) {    // 3번 반복
        ...
    }
}
```

가장 바깥 루프를 `3`번, 첫 노드의 값을 지정하는 경우의 수를 모두 확인하고

내부 DP 루프를 `N-1`번 갱신하는 과정을 거친다.

마지막으로 결과값을 검사하는 루프를 `3`번 거치며

```math
3*(N+3) = 3N+9
```
상수항, 상수연산을 무시하면 다음과 같은 시간복잡도를 가지게 된다. 
```math
O(N)
```

<br>

`N`이 주어질 수 있는 가장 큰 값인 `1,000`이더라도 전체 경우의 수는 `3,009`개이며<br>
앞서 DFS를 통한 해결 방식에서의 경우의 수인 `1.07*10^301`개 보다 압도적으로 적은 연산량으로 문제를 해결하였다.

동일 연산이 반복되거나, 기존 연산의 결과를 활용할 수 있을 때 `DP`를 활용한 문제 해결 과정이 보다 빠르고 효율적인 모습을 보임을 알 수 있었다.