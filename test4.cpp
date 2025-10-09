// 연산자 끼워넣기
#include <iostream>
#include <stdio.h>
#include <string>

#define MAX 12

using namespace std;

int N;
int arr[11] = {0,};
string op_str = "";
int ans_max = -99999999, ans_min = 99999999;

int max(int a, int b){ return a >= b ? a : b; }
int min(int a, int b){ return a <= b ? a : b; }

void select_op(int idx, int op){
    char op_char;
    if (idx == 0) op_char = '+';
    if (idx == 1) op_char = '-';
    if (idx == 2) op_char = '*';
    if (idx == 3) op_char = '/';

    if (op == 0) return;
    for (int i = 0; i < op; i++) op_str += op_char;
}

void input(){
    cin >> N;
    for (int i = 0; i < N; i++) cin >> arr[i];
    for (int i = 0; i < 4; i++){
        int op; cin >> op;
        select_op(i, op);
    }
}

void calcu(){
    
}

void solution(){
    input();
    calcu();
}

int main(){
    cin.tie(NULL);
    cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    solution();

    return 0;
}



/*

N개 수열 A1 ~ AN

연산자 N-1개 (수열 사이에 넣을)

+ - * / 만 있음

1 2 3 4 5 6

+ 2개 - 1개 * 1개 / 1개
=> 60가지 수식 가능

1. 식 연산은 우선순위 무시, 앞에서부터 계산

2. 나눗셈은 정수 나눗셈으로 몫만

3. 음수를 양수로 나눌 때 C++14 기준을 따름 => 음수를 양수로 바꾸고 몫을 취하고 그 몫을 음수로

N개의 수, N-1개 연산자가 주어질 때 만들 수 있는 계산 결과의 최대, 최소 구하기


2 <= N <= 11
1 <= Ai <= 100

순서대로 + - * /의 개수

2
5 6
0 0 1 0

2개의 수 : 5, 6

+ - * / : 0 0 1 0

5 * 6만 됨 30

3
3 4 5
1 0 1 0

+ *

2! => 2가지 경우
7*5 35
12+5 17

6
1 2 3 4 5 6
2 1 1 1 => 5! / 2!


2 3 1 1 => 7! / 2! * 3!

7652 = 42*10 = 420가지



+ - * /

경우의 수 : 순열? 조합? => 순열



+ - * / 중 가장 큰 값 선택


3
3 4 5
1 0 1 0

A op B


*는 가장 큰 A, B
+는 다음
-는 다음
/는 마지막

*/