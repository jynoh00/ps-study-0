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