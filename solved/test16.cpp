// 카드2

#include <iostream>
#include <deque>

using namespace std;

int N;

void input();
void solution();

int main(){
    cin.tie(NULL); cout.tie(NULL);
    ios_base::sync_with_stdio(false);

    input();
    solution();

    return 0;
}

void input(){
    cin >> N;
}

void solution(){
    deque<int> dq;
    for (int i = 1; i <= N; i++) dq.push_front(i);

    while(dq.size() != 1){
        dq.pop_back();
        int tmp = dq.back();
        dq.pop_back();
        dq.push_front(tmp);
    }

    cout << dq[0] << endl;
}